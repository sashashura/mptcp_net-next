// SPDX-License-Identifier: GPL-2.0+

#include <net/pkt_cls.h>

#include "lan966x_main.h"

static int lan966x_tc_setup_qdisc_mqprio(struct lan966x_port *port,
					 struct tc_mqprio_qopt_offload *mqprio)
{
	u8 num_tc = mqprio->qopt.num_tc;

	mqprio->qopt.hw = TC_MQPRIO_HW_OFFLOAD_TCS;

	return num_tc ? lan966x_mqprio_add(port, num_tc) :
			lan966x_mqprio_del(port);
}

static int lan966x_tc_setup_qdisc_taprio(struct lan966x_port *port,
					 struct tc_taprio_qopt_offload *taprio)
{
	return taprio->enable ? lan966x_taprio_add(port, taprio) :
				lan966x_taprio_del(port);
}

int lan966x_tc_setup(struct net_device *dev, enum tc_setup_type type,
		     void *type_data)
{
	struct lan966x_port *port = netdev_priv(dev);

	switch (type) {
	case TC_SETUP_QDISC_MQPRIO:
		return lan966x_tc_setup_qdisc_mqprio(port, type_data);
	case TC_SETUP_QDISC_TAPRIO:
		return lan966x_tc_setup_qdisc_taprio(port, type_data);
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}
