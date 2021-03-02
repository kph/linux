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
#include <linux/property.h>
#include <linux/acpi.h>
#include <../drivers/gpio/gpiolib.h>
#include <linux/gpio/consumer.h>

extern struct xeth_platform xeth_platina_mk1_platform;

static const struct of_device_id xeth_platform_of_match[] = {
	{
		.compatible = "platina,mk1",
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

static void gpiod_debug(const char *label, struct gpio_descs *descs)
{
	int i;
	struct gpio_desc *desc;

	for (i = 0; i < descs->ndescs; i++) {
		desc = descs->desc[i];
		printk(KERN_EMERG "%s: desc label=%s index %d name=%s id %d",
		       __func__, desc->label, i, desc->name, desc_to_gpio(desc));
	}
}

static int xeth_platform_probe(struct platform_device *pd)
{
	struct net_device *mux;
	int err, port, subport;
	u32 base_port = 1;
	struct gpio_descs *absent_gpios, *int_gpios, *lpmode_gpios, *reset_gpios;
	
	err = device_property_read_u32(&pd->dev, "base-port", &base_port);
	if (err < 0)
		return err;

	absent_gpios = gpiod_get_array(&pd->dev, "absent", 0);
	if (IS_ERR(absent_gpios)) {
		err = PTR_ERR(absent_gpios);
		goto out_absent;
	}

	int_gpios = gpiod_get_array(&pd->dev, "int", 0);
	if (IS_ERR(int_gpios)) {
		err = PTR_ERR(int_gpios);
		goto out_int;
	}
	
	lpmode_gpios = gpiod_get_array(&pd->dev, "lpmode", 0);
	if (IS_ERR(lpmode_gpios)) {
		err = PTR_ERR(lpmode_gpios);
		goto out_lpmode;
	}
	
	reset_gpios = gpiod_get_array(&pd->dev, "reset", 0);
	if (IS_ERR(reset_gpios)) {
		err = PTR_ERR(reset_gpios);
		goto out_reset;
	}

	err = xeth_platform_init(&xeth_platina_mk1_platform, pd, base_port);
	if (err) {
		goto out_platform_init;
	}

	mux = xeth_mux(&xeth_platina_mk1_platform);
	if (IS_ERR(mux)) {
		err = PTR_ERR(mux);
		goto out_mux;
	}

	err = device_create_file(&pd->dev, &xeth_platform_provision_attr);
	if (err) {
		goto out_device_create_file;
	}
	
	gpiod_debug("absent", absent_gpios);
	gpiod_debug("int", int_gpios);
	gpiod_debug("lpmode", lpmode_gpios);
	gpiod_debug("reset", reset_gpios);

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

out_device_create_file:
	xeth_mux_uninit(mux);
out_mux:
	xeth_platform_uninit(&xeth_platina_mk1_platform);
out_platform_init:
	gpiod_put_array(reset_gpios);
out_reset:
	gpiod_put_array(lpmode_gpios);
out_lpmode:
	gpiod_put_array(int_gpios);
out_int:
	gpiod_put_array(absent_gpios);
out_absent:
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
