#include <linux/bpf.h>
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

char buf[8192];


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


static void read_arp(struct nlmsghdr *nh, int nll)
{
	struct rtattr *rt_attr;
	char dsts[24], mac[24];
	struct ndmsg *rt_msg;
	int rtl, ndm_family;

	struct arp_table {
		__be64 mac;
		__be32 dst;
	} arp_entry;
	struct direct_map {
		struct arp_table arp;
		int ifindex;
		__be64 mac;
	} direct_entry;

	printf("Address             HwAddress\n");
	for (; NLMSG_OK(nh, nll); nh = NLMSG_NEXT(nh, nll)) {
		rt_msg = (struct ndmsg *)NLMSG_DATA(nh);
		rt_attr = (struct rtattr *)RTM_RTA(rt_msg);
		ndm_family = rt_msg->ndm_family;
		rtl = RTM_PAYLOAD(nh);
		for (; RTA_OK(rt_attr, rtl); rt_attr = RTA_NEXT(rt_attr, rtl)) {
			switch (rt_attr->rta_type) {
			case NDA_DST:
				sprintf(dsts, "%u", *((__be32 *)RTA_DATA(rt_attr)));
				break;
			case NDA_LLADDR:
				sprintf(mac, "%lld", *((__be64 *)RTA_DATA(rt_attr)));
				break;
			}
		}
		arp_entry.dst = atoi(dsts);
		arp_entry.mac = atol(mac);
		printf("%.16x    %.16llx\n", arp_entry.dst, arp_entry.mac);
		memset(&arp_entry, 0, sizeof(arp_entry));
		memset(dsts, 0, sizeof(dsts));
                memset(mac, 0, sizeof(mac));
	}
}

static int get_arp_table(int rtm_family)
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
		struct ndmsg rt;
	} req;

	memset(&sa, 0, sizeof(sa));
	memset(&req, 0, sizeof(req));
	memset(&msg, 0, sizeof(msg));
	memset(buf, 0, sizeof(buf));

	sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	sa.nl_family = AF_NETLINK;

	req.nl.nlmsg_len = NLMSG_LENGTH(sizeof(struct rtmsg));
	req.nl.nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
	req.nl.nlmsg_type = RTM_GETNEIGH;
	req.rt.ndm_state = NUD_REACHABLE;
	req.rt.ndm_family = rtm_family;
	req.nl.nlmsg_pid = 0;
	req.nl.nlmsg_seq = ++seq;

	iov.iov_base = (void *)&req.nl;
	iov.iov_len = req.nl.nlmsg_len;

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	sendmsg(sock, &msg, 0);
	nll = recv_msg(sa, sock);
	nh = (struct nlmsghdr *)buf;
	read_arp(nh, nll);
	close(sock);
	return ret;
}

int main(int ac, char **argv)
{
    get_arp_table(AF_INET);
    return 0;
}
