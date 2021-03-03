/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright(c) 2018-2020 Platina Systems, Inc.
 *
 * Contact Information:
 * sw@platina.com
 * Platina Systems, 3180 Del La Cruz Blvd, Santa Clara, CA 95054
 */

#include "xeth_platform.h"
#include "xeth_mux.h"
#include "xeth_port.h"
#include "xeth_qsfp.h"
#include <linux/module.h>
#include <linux/mod_devicetable.h>
//#include <linux/property.h>
//#include <linux/of_device.h>
#include <linux/acpi.h>

/* Driver Data indices */
enum xeth_platform_dd {
	xeth_platform_dd_platina_mk1,
	xeth_platform_dd_platina_mk1alpha,
};

extern struct xeth_platform xeth_platina_mk1_platform;

struct xeth_variant {
	u32 base_port;
};

static const struct xeth_variant xeth_variant_platina_mk1 = {
	.base_port = 1,
};

static const struct xeth_variant xeth_variant_platina_mk1alpha = {
	.base_port = 0,
};

static const struct of_device_id xeth_platform_of_match[] = {
	{
		.compatible = "platina,mk1",
		.data = &xeth_variant_platina_mk1,
	},
	{
		.compatible = "platina,mk1alpha",
		.data = &xeth_variant_platina_mk1alpha,
	},
	{},
};

MODULE_DEVICE_TABLE(of, xeth_platform_of_match);

int xeth_platform_provision[512], xeth_platform_provisioned;
module_param_array_named(provision, xeth_platform_provision, int,
			 &xeth_platform_provisioned, 0644);
MODULE_PARM_DESC(provision, " 1 (default), 2, or 4 subports per port");

ssize_t xeth_platform_subports(size_t port)
{
	return port < ARRAY_SIZE(xeth_platform_provision) ?
		xeth_platform_provision[port] : -EINVAL;
}

static inline ssize_t
xeth_platform_show_port_provision(struct device *dev,
				  struct device_attribute *attr,
				  char *buf)
{
	int port;
	for (port = 0;
	     port < ARRAY_SIZE(xeth_platform_provision) &&
	     xeth_platform_provision[port];
	     port++)
		buf[port] = xeth_platform_provision[port] + '0';
	return port;
}

static struct device_attribute xeth_platform_provision_attr = {
	.attr.name = "provision",
	.attr.mode = VERIFY_OCTAL_PERMISSIONS(0444),
	.show = xeth_platform_show_port_provision,
};

static int __xeth_platform_probe(struct platform_device *pd)
{
	const struct xeth_variant *variant;
	struct net_device *mux;
	int err, port, subport;
	u32 base_port;

	variant = device_get_match_data(&pd->dev);

	printk(KERN_EMERG "%s: pd=%px init_name=%s\n",
	       __func__, pd, pd->dev.init_name);

//	platform = of_device_get_match_data(&pd->dev);
	if (device_property_match_string(&pd->dev, "compatible", "platina,mk1")) {
		printk(KERN_EMERG "%s: pd->name %s is compatible\n", __func__,
		       pd->name);
	} else {
		printk(KERN_EMERG "%s: pd->name %s is not compatible\n", __func__,
		       pd->name);
		return -EINVAL;
	}
	if (variant) {
		printk(KERN_EMERG "%s: %s variant %px platform_mk1 %px alpha %px\n",
		       __func__, pd->name,
		       variant, &xeth_variant_platina_mk1,
		       &xeth_variant_platina_mk1alpha);
		//variant = NULL;
	}

	if (!variant) {
		pr_err("%s: no match %s\n", __func__, pd->name);
		return -EINVAL;
	}

	if (device_property_read_u32(&pd->dev, "base-port", &base_port)) {
		base_port = variant->base_port;
	}

	err = xeth_platform_init(&xeth_platina_mk1_platform, pd, base_port);
	if (err) {
		return err;
	}

	mux = xeth_mux(&xeth_platina_mk1_platform);
	if (IS_ERR(mux)) {
		xeth_platform_uninit(&xeth_platina_mk1_platform);
		return PTR_ERR(mux);
	}

	err = device_create_file(&pd->dev, &xeth_platform_provision_attr);
	if (err) {
		xeth_mux_uninit(mux);
		xeth_platform_uninit(&xeth_platina_mk1_platform);
		return err;
	}
	
	platform_set_drvdata(pd, mux);

	for (port = 0; port < xeth_platform_ports(&xeth_platina_mk1_platform);
	     port++)
		switch (xeth_platform_provision[port]) {
		case 1:
			xeth_port(mux, port, -1);
			break;
		case 2:
		case 4:
			for (subport = 0;
			     subport < xeth_platform_provision[port];
			     subport++)
				xeth_port(mux, port, subport);
			break;
		default:
			xeth_platform_provision[port] = 1;
			xeth_port(mux, port, -1);
		}

	return 0;
}

static int xeth_platform_probe(struct platform_device *pd) {
	int err;

	err = __xeth_platform_probe(pd);
	printk(KERN_EMERG"%s: pd=%px pd->name=%s err=%d\n", __func__,
	       pd, pd->name, err);
	return err;
}

static int xeth_platform_remove(struct platform_device *pd)
{
	struct net_device *mux;
	LIST_HEAD(q);

	mux = platform_get_drvdata(pd);
	if (!mux)
		return 0;
	platform_set_drvdata(pd, NULL);

	device_remove_file(&pd->dev, &xeth_platform_provision_attr);
	xeth_platform_uninit(xeth_mux_platform(mux));

	rtnl_lock();
	xeth_mux_lnko.dellink(mux, &q);
	unregister_netdevice_many(&q);
	rtnl_unlock();
	rcu_barrier();

	return 0;
}

struct platform_driver xeth_platform_driver = {
	.driver		= {
		.name = KBUILD_MODNAME,
		.of_match_table = xeth_platform_of_match,
	},
	.probe		= xeth_platform_probe,
	.remove		= xeth_platform_remove,
};
