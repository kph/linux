/* Platina Systems XETH driver for the MK1 top of rack ethernet switch
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

#define PLATINA_MK1_STATS			\
	"mmu-multicast-tx-cos0-drop-bytes",	\
	"mmu-multicast-tx-cos0-drop-packets",	\
	"mmu-multicast-tx-cos1-drop-bytes",	\
	"mmu-multicast-tx-cos1-drop-packets",	\
	"mmu-multicast-tx-cos2-drop-bytes",	\
	"mmu-multicast-tx-cos2-drop-packets",	\
	"mmu-multicast-tx-cos3-drop-bytes",	\
	"mmu-multicast-tx-cos3-drop-packets",	\
	"mmu-multicast-tx-cos4-drop-bytes",	\
	"mmu-multicast-tx-cos4-drop-packets",	\
	"mmu-multicast-tx-cos5-drop-bytes",	\
	"mmu-multicast-tx-cos5-drop-packets",	\
	"mmu-multicast-tx-cos6-drop-bytes",	\
	"mmu-multicast-tx-cos6-drop-packets",	\
	"mmu-multicast-tx-cos7-drop-bytes",	\
	"mmu-multicast-tx-cos7-drop-packets",	\
	"mmu-multicast-tx-qm-drop-bytes",	\
	"mmu-multicast-tx-qm-drop-packets",	\
	"mmu-multicast-tx-sc-drop-bytes",	\
	"mmu-multicast-tx-sc-drop-packets",	\
	"mmu-rx-threshold-drop-bytes",		\
	"mmu-rx-threshold-drop-packets",	\
	"mmu-tx-cpu-cos-0-drop-bytes",		\
	"mmu-tx-cpu-cos-0-drop-packets",	\
	"mmu-tx-cpu-cos-10-drop-bytes",		\
	"mmu-tx-cpu-cos-10-drop-packets",	\
	"mmu-tx-cpu-cos-11-drop-bytes",		\
	"mmu-tx-cpu-cos-11-drop-packets",	\
	"mmu-tx-cpu-cos-12-drop-bytes",		\
	"mmu-tx-cpu-cos-12-drop-packets",	\
	"mmu-tx-cpu-cos-13-drop-bytes",		\
	"mmu-tx-cpu-cos-13-drop-packets",	\
	"mmu-tx-cpu-cos-14-drop-bytes",		\
	"mmu-tx-cpu-cos-14-drop-packets",	\
	"mmu-tx-cpu-cos-15-drop-bytes",		\
	"mmu-tx-cpu-cos-15-drop-packets",	\
	"mmu-tx-cpu-cos-16-drop-bytes",		\
	"mmu-tx-cpu-cos-16-drop-packets",	\
	"mmu-tx-cpu-cos-17-drop-bytes",		\
	"mmu-tx-cpu-cos-17-drop-packets",	\
	"mmu-tx-cpu-cos-18-drop-bytes",		\
	"mmu-tx-cpu-cos-18-drop-packets",	\
	"mmu-tx-cpu-cos-19-drop-bytes",		\
	"mmu-tx-cpu-cos-19-drop-packets",	\
	"mmu-tx-cpu-cos-1-drop-bytes",		\
	"mmu-tx-cpu-cos-1-drop-packets",	\
	"mmu-tx-cpu-cos-20-drop-bytes",		\
	"mmu-tx-cpu-cos-20-drop-packets",	\
	"mmu-tx-cpu-cos-21-drop-bytes",		\
	"mmu-tx-cpu-cos-21-drop-packets",	\
	"mmu-tx-cpu-cos-22-drop-bytes",		\
	"mmu-tx-cpu-cos-22-drop-packets",	\
	"mmu-tx-cpu-cos-23-drop-bytes",		\
	"mmu-tx-cpu-cos-23-drop-packets",	\
	"mmu-tx-cpu-cos-24-drop-bytes",		\
	"mmu-tx-cpu-cos-24-drop-packets",	\
	"mmu-tx-cpu-cos-25-drop-bytes",		\
	"mmu-tx-cpu-cos-25-drop-packets",	\
	"mmu-tx-cpu-cos-26-drop-bytes",		\
	"mmu-tx-cpu-cos-26-drop-packets",	\
	"mmu-tx-cpu-cos-27-drop-bytes",		\
	"mmu-tx-cpu-cos-27-drop-packets",	\
	"mmu-tx-cpu-cos-28-drop-bytes",		\
	"mmu-tx-cpu-cos-28-drop-packets",	\
	"mmu-tx-cpu-cos-29-drop-bytes",		\
	"mmu-tx-cpu-cos-29-drop-packets",	\
	"mmu-tx-cpu-cos-2-drop-bytes",		\
	"mmu-tx-cpu-cos-2-drop-packets",	\
	"mmu-tx-cpu-cos-30-drop-bytes",		\
	"mmu-tx-cpu-cos-30-drop-packets",	\
	"mmu-tx-cpu-cos-31-drop-bytes",		\
	"mmu-tx-cpu-cos-31-drop-packets",	\
	"mmu-tx-cpu-cos-32-drop-bytes",		\
	"mmu-tx-cpu-cos-32-drop-packets",	\
	"mmu-tx-cpu-cos-33-drop-bytes",		\
	"mmu-tx-cpu-cos-33-drop-packets",	\
	"mmu-tx-cpu-cos-34-drop-bytes",		\
	"mmu-tx-cpu-cos-34-drop-packets",	\
	"mmu-tx-cpu-cos-35-drop-bytes",		\
	"mmu-tx-cpu-cos-35-drop-packets",	\
	"mmu-tx-cpu-cos-36-drop-bytes",		\
	"mmu-tx-cpu-cos-36-drop-packets",	\
	"mmu-tx-cpu-cos-37-drop-bytes",		\
	"mmu-tx-cpu-cos-37-drop-packets",	\
	"mmu-tx-cpu-cos-38-drop-bytes",		\
	"mmu-tx-cpu-cos-38-drop-packets",	\
	"mmu-tx-cpu-cos-39-drop-bytes",		\
	"mmu-tx-cpu-cos-39-drop-packets",	\
	"mmu-tx-cpu-cos-3-drop-bytes",		\
	"mmu-tx-cpu-cos-3-drop-packets",	\
	"mmu-tx-cpu-cos-40-drop-bytes",		\
	"mmu-tx-cpu-cos-40-drop-packets",	\
	"mmu-tx-cpu-cos-41-drop-bytes",		\
	"mmu-tx-cpu-cos-41-drop-packets",	\
	"mmu-tx-cpu-cos-42-drop-bytes",		\
	"mmu-tx-cpu-cos-42-drop-packets",	\
	"mmu-tx-cpu-cos-43-drop-bytes",		\
	"mmu-tx-cpu-cos-43-drop-packets",	\
	"mmu-tx-cpu-cos-44-drop-bytes",		\
	"mmu-tx-cpu-cos-44-drop-packets",	\
	"mmu-tx-cpu-cos-45-drop-bytes",		\
	"mmu-tx-cpu-cos-45-drop-packets",	\
	"mmu-tx-cpu-cos-46-drop-bytes",		\
	"mmu-tx-cpu-cos-46-drop-packets",	\
	"mmu-tx-cpu-cos-47-drop-bytes",		\
	"mmu-tx-cpu-cos-47-drop-packets",	\
	"mmu-tx-cpu-cos-4-drop-bytes",		\
	"mmu-tx-cpu-cos-4-drop-packets",	\
	"mmu-tx-cpu-cos-5-drop-bytes",		\
	"mmu-tx-cpu-cos-5-drop-packets",	\
	"mmu-tx-cpu-cos-6-drop-bytes",		\
	"mmu-tx-cpu-cos-6-drop-packets",	\
	"mmu-tx-cpu-cos-7-drop-bytes",		\
	"mmu-tx-cpu-cos-7-drop-packets",	\
	"mmu-tx-cpu-cos-8-drop-bytes",		\
	"mmu-tx-cpu-cos-8-drop-packets",	\
	"mmu-tx-cpu-cos-9-drop-bytes",		\
	"mmu-tx-cpu-cos-9-drop-packets",	\
	"mmu-unicast-tx-cos0-drop-bytes",	\
	"mmu-unicast-tx-cos0-drop-packets",	\
	"mmu-unicast-tx-cos1-drop-bytes",	\
	"mmu-unicast-tx-cos1-drop-packets",	\
	"mmu-unicast-tx-cos2-drop-bytes",	\
	"mmu-unicast-tx-cos2-drop-packets",	\
	"mmu-unicast-tx-cos3-drop-bytes",	\
	"mmu-unicast-tx-cos3-drop-packets",	\
	"mmu-unicast-tx-cos4-drop-bytes",	\
	"mmu-unicast-tx-cos4-drop-packets",	\
	"mmu-unicast-tx-cos5-drop-bytes",	\
	"mmu-unicast-tx-cos5-drop-packets",	\
	"mmu-unicast-tx-cos6-drop-bytes",	\
	"mmu-unicast-tx-cos6-drop-packets",	\
	"mmu-unicast-tx-cos7-drop-bytes",	\
	"mmu-unicast-tx-cos7-drop-packets",	\
	"mmu-unicast-tx-qm-drop-bytes",		\
	"mmu-unicast-tx-qm-drop-packets",	\
	"mmu-unicast-tx-sc-drop-bytes",		\
	"mmu-unicast-tx-sc-drop-packets",	\
	"mmu-wred-queue-cos0-drop-packets",	\
	"mmu-wred-queue-cos1-drop-packets",	\
	"mmu-wred-queue-cos2-drop-packets",	\
	"mmu-wred-queue-cos3-drop-packets",	\
	"mmu-wred-queue-cos4-drop-packets",	\
	"mmu-wred-queue-cos5-drop-packets",	\
	"mmu-wred-queue-cos6-drop-packets",	\
	"mmu-wred-queue-cos7-drop-packets",	\
	"mmu-wred-queue-qm-drop-packets",	\
	"mmu-wred-queue-sc-drop-packets",	\
	"port-rx-1024-to-1518-byte-packets",	\
	"port-rx-128-to-255-byte-packets",	\
	"port-rx-1519-to-1522-byte-vlan-packets",	\
	"port-rx-1519-to-2047-byte-packets",	\
	"port-rx-1tag-vlan-packets",		\
	"port-rx-2048-to-4096-byte-packets",	\
	"port-rx-256-to-511-byte-packets",	\
	"port-rx-2tag-vlan-packets",		\
	"port-rx-4096-to-9216-byte-packets",	\
	"port-rx-512-to-1023-byte-packets",	\
	"port-rx-64-byte-packets",		\
	"port-rx-65-to-127-byte-packets",	\
	"port-rx-802-3-length-error-packets",	\
	"port-rx-9217-to-16383-byte-packets",	\
	"port-rx-alignment-error-packets",	\
	"port-rx-broadcast-packets",		\
	"port-rx-bytes",			\
	"port-rx-code-error-packets",		\
	"port-rx-control-packets",		\
	"port-rx-crc-error-packets",		\
	"port-rx-eee-lpi-duration",		\
	"port-rx-eee-lpi-events",		\
	"port-rx-false-carrier-events",		\
	"port-rx-flow-control-packets",		\
	"port-rx-fragment-packets",		\
	"port-rx-good-packets",			\
	"port-rx-jabber-packets",		\
	"port-rx-mac-sec-crc-matched-packets",	\
	"port-rx-mtu-check-error-packets",	\
	"port-rx-multicast-packets",		\
	"port-rx-oversize-packets",		\
	"port-rx-packets",			\
	"port-rx-pfc-packets",			\
	"port-rx-pfc-priority-0",		\
	"port-rx-pfc-priority-1",		\
	"port-rx-pfc-priority-2",		\
	"port-rx-pfc-priority-3",		\
	"port-rx-pfc-priority-4",		\
	"port-rx-pfc-priority-5",		\
	"port-rx-pfc-priority-6",		\
	"port-rx-pfc-priority-7",		\
	"port-rx-promiscuous-packets",		\
	"port-rx-runt-bytes",			\
	"port-rx-runt-packets",			\
	"port-rx-src-address-not-unicast-packets",	\
	"port-rx-truncated-packets",		\
	"port-rx-undersize-packets",		\
	"port-rx-unicast-packets",		\
	"port-rx-unsupported-dst-address-control-packets",	\
	"port-rx-unsupported-opcode-control-packets",	\
	"port-rx-xon-to-xoff-priority-0",	\
	"port-rx-xon-to-xoff-priority-1",	\
	"port-rx-xon-to-xoff-priority-2",	\
	"port-rx-xon-to-xoff-priority-3",	\
	"port-rx-xon-to-xoff-priority-4",	\
	"port-rx-xon-to-xoff-priority-5",	\
	"port-rx-xon-to-xoff-priority-6",	\
	"port-rx-xon-to-xoff-priority-7",	\
	"port-tx-1024-to-1518-byte-packets",	\
	"port-tx-128-to-255-byte-packets",	\
	"port-tx-1519-to-1522-byte-vlan-packets",	\
	"port-tx-1519-to-2047-byte-packets",	\
	"port-tx-1tag-vlan-packets",		\
	"port-tx-2048-to-4096-byte-packets",	\
	"port-tx-256-to-511-byte-packets",	\
	"port-tx-2tag-vlan-packets",		\
	"port-tx-4096-to-9216-byte-packets",	\
	"port-tx-512-to-1023-byte-packets",	\
	"port-tx-64-byte-packets",		\
	"port-tx-65-to-127-byte-packets",	\
	"port-tx-9217-to-16383-byte-packets",	\
	"port-tx-broadcast-packets",		\
	"port-tx-bytes",			\
	"port-tx-control-packets",		\
	"port-tx-eee-lpi-duration",		\
	"port-tx-eee-lpi-events",		\
	"port-tx-excessive-collision-packets",	\
	"port-tx-fcs-errors",			\
	"port-tx-fifo-underrun-packets",	\
	"port-tx-flow-control-packets",		\
	"port-tx-fragments",			\
	"port-tx-good-packets",			\
	"port-tx-jabber-packets",		\
	"port-tx-late-collision-packets",	\
	"port-tx-multicast-packets",		\
	"port-tx-multiple-collision-packets",	\
	"port-tx-multiple-deferral-packets",	\
	"port-tx-oversize",			\
	"port-tx-packets",			\
	"port-tx-pfc-packets",			\
	"port-tx-pfc-priority-0-packets",	\
	"port-tx-pfc-priority-1-packets",	\
	"port-tx-pfc-priority-2-packets",	\
	"port-tx-pfc-priority-3-packets",	\
	"port-tx-pfc-priority-4-packets",	\
	"port-tx-pfc-priority-5-packets",	\
	"port-tx-pfc-priority-6-packets",	\
	"port-tx-pfc-priority-7-packets",	\
	"port-tx-runt-packets",			\
	"port-tx-single-collision-packets",	\
	"port-tx-single-deferral-packets",	\
	"port-tx-system-error-packets",		\
	"port-tx-total-collisions",		\
	"port-tx-unicast-packets",		\
	"punts",				\
	"rx-bytes",				\
	"rx-packets",				\
	"rx-pipe-debug-6",			\
	"rx-pipe-debug-7",			\
	"rx-pipe-debug-8",			\
	"rx-pipe-dst-discard-drops",		\
	"rx-pipe-ecn-counter",			\
	"rx-pipe-hi-gig-broadcast-packets",	\
	"rx-pipe-hi-gig-control-packets",	\
	"rx-pipe-hi-gig-l2-multicast-packets",	\
	"rx-pipe-hi-gig-l3-multicast-packets",	\
	"rx-pipe-hi-gig-unknown-opcode-packets",	\
	"rx-pipe-ibp-discard-cbp-full-drops",	\
	"rx-pipe-ip4-header-errors",		\
	"rx-pipe-ip4-l3-drops",			\
	"rx-pipe-ip4-l3-packets",		\
	"rx-pipe-ip4-routed-multicast-packets",	\
	"rx-pipe-ip6-header-errors",		\
	"rx-pipe-ip6-l3-drops",			\
	"rx-pipe-ip6-l3-packets",		\
	"rx-pipe-ip6-routed-multicast-packets",	\
	"rx-pipe-l3-interface-bytes",		\
	"rx-pipe-l3-interface-packets",		\
	"rx-pipe-multicast-drops",		\
	"rx-pipe-niv-forwarding-error-drops",	\
	"rx-pipe-niv-frame-error-drops",	\
	"rx-pipe-port-table-bytes",		\
	"rx-pipe-port-table-packets",		\
	"rx-pipe-rxf-drops",			\
	"rx-pipe-spanning-tree-state-not-forwarding-drops",	\
	"rx-pipe-trill-non-trill-drops",	\
	"rx-pipe-trill-packets",		\
	"rx-pipe-trill-trill-drops",		\
	"rx-pipe-tunnel-error-packets",		\
	"rx-pipe-tunnel-packets",		\
	"rx-pipe-unicast-packets",		\
	"rx-pipe-unknown-vlan-drops",		\
	"rx-pipe-vlan-tagged-packets",		\
	"rx-pipe-zero-port-bitmap-drops",	\
	"tx-bytes",				\
	"tx-packets",				\
	"tx-pipe-cpu-0x10-bytes",		\
	"tx-pipe-cpu-0x10-packets",		\
	"tx-pipe-cpu-0x11-bytes",		\
	"tx-pipe-cpu-0x11-packets",		\
	"tx-pipe-cpu-0x12-bytes",		\
	"tx-pipe-cpu-0x12-packets",		\
	"tx-pipe-cpu-0x13-bytes",		\
	"tx-pipe-cpu-0x13-packets",		\
	"tx-pipe-cpu-0x14-bytes",		\
	"tx-pipe-cpu-0x14-packets",		\
	"tx-pipe-cpu-0x15-bytes",		\
	"tx-pipe-cpu-0x15-packets",		\
	"tx-pipe-cpu-0x16-bytes",		\
	"tx-pipe-cpu-0x16-packets",		\
	"tx-pipe-cpu-0x17-bytes",		\
	"tx-pipe-cpu-0x17-packets",		\
	"tx-pipe-cpu-0x18-bytes",		\
	"tx-pipe-cpu-0x18-packets",		\
	"tx-pipe-cpu-0x19-bytes",		\
	"tx-pipe-cpu-0x19-packets",		\
	"tx-pipe-cpu-0x1a-bytes",		\
	"tx-pipe-cpu-0x1a-packets",		\
	"tx-pipe-cpu-0x1b-bytes",		\
	"tx-pipe-cpu-0x1b-packets",		\
	"tx-pipe-cpu-0x1c-bytes",		\
	"tx-pipe-cpu-0x1c-packets",		\
	"tx-pipe-cpu-0x1d-bytes",		\
	"tx-pipe-cpu-0x1d-packets",		\
	"tx-pipe-cpu-0x1e-bytes",		\
	"tx-pipe-cpu-0x1e-packets",		\
	"tx-pipe-cpu-0x1f-bytes",		\
	"tx-pipe-cpu-0x1f-packets",		\
	"tx-pipe-cpu-0x20-bytes",		\
	"tx-pipe-cpu-0x20-packets",		\
	"tx-pipe-cpu-0x21-bytes",		\
	"tx-pipe-cpu-0x21-packets",		\
	"tx-pipe-cpu-0x22-bytes",		\
	"tx-pipe-cpu-0x22-packets",		\
	"tx-pipe-cpu-0x23-bytes",		\
	"tx-pipe-cpu-0x23-packets",		\
	"tx-pipe-cpu-0x24-bytes",		\
	"tx-pipe-cpu-0x24-packets",		\
	"tx-pipe-cpu-0x25-bytes",		\
	"tx-pipe-cpu-0x25-packets",		\
	"tx-pipe-cpu-0x26-bytes",		\
	"tx-pipe-cpu-0x26-packets",		\
	"tx-pipe-cpu-0x27-bytes",		\
	"tx-pipe-cpu-0x27-packets",		\
	"tx-pipe-cpu-0x28-bytes",		\
	"tx-pipe-cpu-0x28-packets",		\
	"tx-pipe-cpu-0x29-bytes",		\
	"tx-pipe-cpu-0x29-packets",		\
	"tx-pipe-cpu-0x2a-bytes",		\
	"tx-pipe-cpu-0x2a-packets",		\
	"tx-pipe-cpu-0x2b-bytes",		\
	"tx-pipe-cpu-0x2b-packets",		\
	"tx-pipe-cpu-0x2c-bytes",		\
	"tx-pipe-cpu-0x2c-packets",		\
	"tx-pipe-cpu-0x2d-bytes",		\
	"tx-pipe-cpu-0x2d-packets",		\
	"tx-pipe-cpu-0x2e-bytes",		\
	"tx-pipe-cpu-0x2e-packets",		\
	"tx-pipe-cpu-0x2f-bytes",		\
	"tx-pipe-cpu-0x2f-packets",		\
	"tx-pipe-cpu-0x4-bytes",		\
	"tx-pipe-cpu-0x4-packets",		\
	"tx-pipe-cpu-0x5-bytes",		\
	"tx-pipe-cpu-0x5-packets",		\
	"tx-pipe-cpu-0x6-bytes",		\
	"tx-pipe-cpu-0x6-packets",		\
	"tx-pipe-cpu-0x7-bytes",		\
	"tx-pipe-cpu-0x7-packets",		\
	"tx-pipe-cpu-0x8-bytes",		\
	"tx-pipe-cpu-0x8-packets",		\
	"tx-pipe-cpu-0x9-bytes",		\
	"tx-pipe-cpu-0x9-packets",		\
	"tx-pipe-cpu-0xa-bytes",		\
	"tx-pipe-cpu-0xa-packets",		\
	"tx-pipe-cpu-0xb-bytes",		\
	"tx-pipe-cpu-0xb-packets",		\
	"tx-pipe-cpu-0xc-bytes",		\
	"tx-pipe-cpu-0xc-packets",		\
	"tx-pipe-cpu-0xd-bytes",		\
	"tx-pipe-cpu-0xd-packets",		\
	"tx-pipe-cpu-0xe-bytes",		\
	"tx-pipe-cpu-0xe-packets",		\
	"tx-pipe-cpu-0xf-bytes",		\
	"tx-pipe-cpu-0xf-packets",		\
	"tx-pipe-cpu-error-bytes",		\
	"tx-pipe-cpu-error-packets",		\
	"tx-pipe-cpu-punt-1tag-bytes",		\
	"tx-pipe-cpu-punt-1tag-packets",	\
	"tx-pipe-cpu-punt-bytes",		\
	"tx-pipe-cpu-punt-packets",		\
	"tx-pipe-cpu-vlan-redirect-bytes",	\
	"tx-pipe-cpu-vlan-redirect-packets",	\
	"tx-pipe-debug-a",			\
	"tx-pipe-debug-b",			\
	"tx-pipe-ecn-errors",			\
	"tx-pipe-invalid-vlan-drops",		\
	"tx-pipe-ip4-unicast-aged-and-dropped-packets",	\
	"tx-pipe-ip4-unicast-packets",		\
	"tx-pipe-ip-length-check-drops",	\
	"tx-pipe-multicast-queue-cos0-bytes",	\
	"tx-pipe-multicast-queue-cos0-packets",	\
	"tx-pipe-multicast-queue-cos1-bytes",	\
	"tx-pipe-multicast-queue-cos1-packets",	\
	"tx-pipe-multicast-queue-cos2-bytes",	\
	"tx-pipe-multicast-queue-cos2-packets",	\
	"tx-pipe-multicast-queue-cos3-bytes",	\
	"tx-pipe-multicast-queue-cos3-packets",	\
	"tx-pipe-multicast-queue-cos4-bytes",	\
	"tx-pipe-multicast-queue-cos4-packets",	\
	"tx-pipe-multicast-queue-cos5-bytes",	\
	"tx-pipe-multicast-queue-cos5-packets",	\
	"tx-pipe-multicast-queue-cos6-bytes",	\
	"tx-pipe-multicast-queue-cos6-packets",	\
	"tx-pipe-multicast-queue-cos7-bytes",	\
	"tx-pipe-multicast-queue-cos7-packets",	\
	"tx-pipe-multicast-queue-qm-bytes",	\
	"tx-pipe-multicast-queue-qm-packets",	\
	"tx-pipe-multicast-queue-sc-bytes",	\
	"tx-pipe-multicast-queue-sc-packets",	\
	"tx-pipe-packet-aged-drops",		\
	"tx-pipe-packets-dropped",		\
	"tx-pipe-port-table-bytes",		\
	"tx-pipe-port-table-packets",		\
	"tx-pipe-purge-cell-error-drops",	\
	"tx-pipe-spanning-tree-state-not-forwarding-drops",	\
	"tx-pipe-trill-access-port-drops",	\
	"tx-pipe-trill-non-trill-drops",	\
	"tx-pipe-trill-packets",		\
	"tx-pipe-tunnel-error-packets",		\
	"tx-pipe-tunnel-packets",		\
	"tx-pipe-unicast-queue-cos0-bytes",	\
	"tx-pipe-unicast-queue-cos0-packets",	\
	"tx-pipe-unicast-queue-cos1-bytes",	\
	"tx-pipe-unicast-queue-cos1-packets",	\
	"tx-pipe-unicast-queue-cos2-bytes",	\
	"tx-pipe-unicast-queue-cos2-packets",	\
	"tx-pipe-unicast-queue-cos3-bytes",	\
	"tx-pipe-unicast-queue-cos3-packets",	\
	"tx-pipe-unicast-queue-cos4-bytes",	\
	"tx-pipe-unicast-queue-cos4-packets",	\
	"tx-pipe-unicast-queue-cos5-bytes",	\
	"tx-pipe-unicast-queue-cos5-packets",	\
	"tx-pipe-unicast-queue-cos6-bytes",	\
	"tx-pipe-unicast-queue-cos6-packets",	\
	"tx-pipe-unicast-queue-cos7-bytes",	\
	"tx-pipe-unicast-queue-cos7-packets",	\
	"tx-pipe-unicast-queue-qm-bytes",	\
	"tx-pipe-unicast-queue-qm-packets",	\
	"tx-pipe-unicast-queue-sc-bytes",	\
	"tx-pipe-unicast-queue-sc-packets",	\
	"tx-pipe-vlan-tagged-packets",		\
	NULL,
