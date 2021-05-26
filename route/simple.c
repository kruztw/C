#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <net/if.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <sys/resource.h>
#include <libgen.h>

int sock, sock_arp;
char buf[8192];

static int get_route_table(int rtm_family);

static __be64 getmac(char *iface)
{
	struct ifreq ifr;
	__be64 mac = 0;
	int fd, i;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, iface, IFNAMSIZ - 1);
	if (ioctl(fd, SIOCGIFHWADDR, &ifr) < 0) {
		printf("ioctl failed leaving....\n");
		return -1;
	}
	for (i = 0; i < 6 ; i++)
		*((__u8 *)&mac + i) = (__u8)ifr.ifr_hwaddr.sa_data[i];
	close(fd);
	return mac;
}

static int recv_msg(struct sockaddr_nl sock_addr, int sock)
{
	struct nlmsghdr *nh;
	int len, nll = 0;
	char *buf_ptr;

	buf_ptr = buf;
	while (1) {
		len = recv(sock, buf_ptr, sizeof(buf) - nll, 0);
		if (len < 0)
			return len;

		nh = (struct nlmsghdr *)buf_ptr;

		if (nh->nlmsg_type == NLMSG_DONE)
			break;
		buf_ptr += len;
		nll += len;
		if ((sock_addr.nl_groups & RTMGRP_NEIGH) == RTMGRP_NEIGH)
			break;

		if ((sock_addr.nl_groups & RTMGRP_IPV4_ROUTE) == RTMGRP_IPV4_ROUTE)
			break;
	}
	return nll;
}

static void read_route(struct nlmsghdr *nh, int nll)
{
	char dsts[24], gws[24], ifs[16], dsts_len[24], metrics[24];
	struct rtattr *rt_attr;
	struct rtmsg *rt_msg;
	int rtm_family;
	int rtl;
	int i;
	struct route_table {
		int  dst_len, iface, metric;
		char *iface_name;
		__be32 dst, gw;
		__be64 mac;
	} route;

	memset(&route, 0, sizeof(route));
	printf("Destination\t\tGateway\t\tGenmask\t\tMetric\t\tIface\n");
	for (; NLMSG_OK(nh, nll); nh = NLMSG_NEXT(nh, nll)) {
		rt_msg = (struct rtmsg *)NLMSG_DATA(nh);
		rtm_family = rt_msg->rtm_family;
		if (rtm_family == AF_INET)
			if (rt_msg->rtm_table != RT_TABLE_MAIN)
				continue;
		rt_attr = (struct rtattr *)RTM_RTA(rt_msg);
		rtl = RTM_PAYLOAD(nh);

		for (; RTA_OK(rt_attr, rtl); rt_attr = RTA_NEXT(rt_attr, rtl)) {
			switch (rt_attr->rta_type) {
			case NDA_DST:
				sprintf(dsts, "%u", (*((__be32 *)RTA_DATA(rt_attr))));
				break;
			case RTA_GATEWAY:
				sprintf(gws, "%u", *((__be32 *)RTA_DATA(rt_attr)));
				break;
			case RTA_OIF:
				sprintf(ifs, "%u", *((int *)RTA_DATA(rt_attr)));
				break;
			case RTA_METRICS:
				sprintf(metrics, "%u", *((int *)RTA_DATA(rt_attr)));
			default:
				break;
			}
		}
		sprintf(dsts_len, "%d", rt_msg->rtm_dst_len);
		route.dst = atoi(dsts);
		route.dst_len = atoi(dsts_len);
		route.gw = atoi(gws);
		route.iface = atoi(ifs);
		route.metric = atoi(metrics);
		route.iface_name = alloca(sizeof(char *) * IFNAMSIZ);
		route.iface_name = if_indextoname(route.iface, route.iface_name);
		route.mac = getmac(route.iface_name);
		if (rtm_family == AF_INET) {
			printf("%3d.%d.%d.%d\t\t%3x\t\t%d\t\t%d\t\t%s\n",
	                       (route.dst >> 0 * 8) & 0xff,
			       (route.dst >> 1 * 8) & 0xff,
			       (route.dst >> 2 * 8) & 0xff,
			       (route.dst >> 3 * 8) & 0xff,
			       route.gw, route.dst_len,
			       route.metric,
			       route.iface_name);
				if (nh->nlmsg_type == RTM_DELROUTE) {
					printf("deleting entry\n");
					printf("prefix key=%d.%d.%d.%d/%d",
					       (route.dst >> 0 * 8) & 0xff,
					       (route.dst >> 1 * 8) & 0xff,
					       (route.dst >> 2 * 8) & 0xff,
					       (route.dst >> 3 * 8) & 0xff,
					       route.dst_len);
					get_route_table(AF_INET);
				}
		}
		memset(&route, 0, sizeof(route));
		memset(dsts, 0, sizeof(dsts));
		memset(dsts_len, 0, sizeof(dsts_len));
		memset(gws, 0, sizeof(gws));
		memset(ifs, 0, sizeof(ifs));
	}
}

static int get_route_table(int rtm_family)
{
	struct sockaddr_nl sa;
	struct nlmsghdr *nh;
	int sock, seq = 0;
	struct msghdr msg;
	struct iovec iov;
	int ret = 0;
	int nll;

	struct {
		struct nlmsghdr nl;
		struct rtmsg rt;
	} req;

	memset(&sa, 0, sizeof(sa));
	memset(&req, 0, sizeof(req));
	memset(&msg, 0, sizeof(msg));
	memset(buf, 0, sizeof(buf));

	sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	sa.nl_family = AF_NETLINK;
	bind(sock, (struct sockaddr *)&sa, sizeof(sa));

	req.nl.nlmsg_len = NLMSG_LENGTH(sizeof(struct rtmsg));
	req.nl.nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
	req.nl.nlmsg_type = RTM_GETROUTE;
	req.rt.rtm_family = rtm_family;
	req.rt.rtm_table = RT_TABLE_MAIN;
	req.nl.nlmsg_pid = 0;
	req.nl.nlmsg_seq = ++seq;

	iov.iov_base = (void *)&req.nl;
	iov.iov_len = req.nl.nlmsg_len;

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	ret = sendmsg(sock, &msg, 0);
	nll = recv_msg(sa, sock);
	nh = (struct nlmsghdr *)buf;
	read_route(nh, nll);
	close(sock);
	return ret;
}

int main(int ac, char **argv)
{
	get_route_table(AF_INET);
	return 0;
}
