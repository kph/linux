/* XETH side-band channel protocol.
 * Copyright(c) 2018 Platina Systems, Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * The full GNU General Public License is included in this distribution in
 * the file called "COPYING".
 *
 * Contact Information:
 * sw@platina.com
 * Platina Systems, 3180 Del La Cruz Blvd, Santa Clara, CA 95054
 */

#ifndef __XETH_UAPI_H
#define __XETH_UAPI_H

#define XETH_SIZEOF_JUMBO_FRAME		9728

enum xeth_msg_kind {
	XETH_MSG_KIND_BREAK,
	XETH_MSG_KIND_LINK_STAT,
	XETH_MSG_KIND_ETHTOOL_STAT,
	XETH_MSG_KIND_ETHTOOL_FLAGS,
	XETH_MSG_KIND_ETHTOOL_SETTINGS,
	XETH_MSG_KIND_DUMP_IFINFO,
	XETH_MSG_KIND_CARRIER,
	XETH_MSG_KIND_SPEED,
	XETH_MSG_KIND_IFINFO,
	XETH_MSG_KIND_IFA,
	XETH_MSG_KIND_DUMP_FIBINFO,
	XETH_MSG_KIND_FIBENTRY,
	XETH_MSG_KIND_IFDEL,
	XETH_MSG_KIND_NEIGH_UPDATE,
	XETH_MSG_KIND_IFVID,
	XETH_MSG_KIND_CHANGE_UPPER,
};

#define xeth_msg_named(name)	xeth_msg_##name

#define xeth_msg_def(name, ...)						\
struct xeth_msg_named(name) {						\
	u64	z64;							\
	u32	z32;							\
	u16	z16;							\
	u8	z8;							\
	u8	kind;							\
	__VA_ARGS__;							\
}

struct xeth_msg {
	u64	z64;
	u32	z32;
	u16	z16;
	u8	z8;
	u8	kind;
};

xeth_msg_def(break);

enum xeth_msg_carrier_flag {
	XETH_CARRIER_OFF,
	XETH_CARRIER_ON,
};

xeth_msg_def(carrier,
	s32	ifindex;
	u8	flag;
	u8	pad[3];
);

xeth_msg_def(change_upper,
	s32	upper;
	s32	lower;
	u8	linking;
	u8	pad[7];
);

xeth_msg_def(dump_fibinfo);
xeth_msg_def(dump_ifinfo);

xeth_msg_def(ethtool_flags,
	s32	ifindex;
	u32	flags;
);

xeth_msg_def(ethtool_settings,
	s32	ifindex;
	u32	speed;
	u8	duplex;
	u8	port;
	u8	phy_address;
	u8	autoneg;
	u8	mdio_support;
	u8	eth_tp_mdix;
	u8	eth_tp_mdix_ctrl;
	s8	link_mode_masks_nwords;
	u32	link_modes_supported[2];
	u32	link_modes_advertising[2];
	u32	link_modes_lp_advertising[2];
);

struct xeth_next_hop {
	s32	ifindex;
	s32	weight;
	u32	flags;
	__be32	gw;
	u8	scope;
	u8	pad[7];
};

xeth_msg_def(fibentry,
	u64	net;
	__be32	address;
	__be32	mask;
	u8	event;
	u8	nhs;
	u8	tos;
	u8	type;
	u32	tb_id;
	struct xeth_next_hop nh[];
);

xeth_msg_def(ifa,
	s32	ifindex;
	u32	event;
	__be32	address;
	__be32	mask;
);

enum xeth_msg_ifinfo_devtype {
	XETH_DEVTYPE_XETH_PORT = 0,
	XETH_DEVTYPE_LINUX_UNKNOWN = 128,
	XETH_DEVTYPE_LINUX_VLAN,
	XETH_DEVTYPE_LINUX_VLAN_BRIDGE_PORT,
	XETH_DEVTYPE_LINUX_BRIDGE,
};

enum xeth_msg_ifinfo_reason {
	XETH_IFINFO_REASON_NEW,
	XETH_IFINFO_REASON_DEL,
	XETH_IFINFO_REASON_UP,
	XETH_IFINFO_REASON_DOWN,
	XETH_IFINFO_REASON_DUMP,
	XETH_IFINFO_REASON_REG,
	XETH_IFINFO_REASON_UNREG,
};

xeth_msg_def(ifinfo,
	u8	ifname[IFNAMSIZ];
	u64	net;
	s32	ifindex;
	s32	iflinkindex;
	u32	flags;
	u16	id;
	u8 	addr[ETH_ALEN];
	s16	portindex;
	s8	subportindex;
	u8	devtype;
	s16	portid;
	u8	reason;
	u8	pad[5];
);

xeth_msg_def(neigh_update,
	u64	net;
	s32	ifindex;
	u8	family;
	u8	len;
	u8	pad0[2];
	u8	dst[16];
	u8 	lladdr[ETH_ALEN];
	u8	pad[8-ETH_ALEN];
);

xeth_msg_def(speed,
	s32	ifindex;
	u32	mbps;
);

xeth_msg_def(stat,
	s32	ifindex;
	u8	pad[4];
	u64	index;
	u64	count;
);

static inline bool xeth_is_msg(struct xeth_msg *p)
{
	return	p->z64 == 0 && p->z32 == 0 && p->z16 == 0 && p->z8 == 0;
}

static inline void xeth_msg_set(void *data, u8 kind)
{
	struct xeth_msg *msg = data;
	msg->z64 = 0;
	msg->z32 = 0;
	msg->z16 = 0;
	msg->z8 = 0;
	msg->kind = kind;
}

#endif /* __XETH_UAPI_H */
