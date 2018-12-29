#include "common.h"
#include "network.h"

#define UDP_DEMO_LOCAL_PORT  20000
#define UDP_SERVER_IPADDR "192.168.56.1"
#define UDP_SERVER_PORT 8080

static network_t  g_udp_network;

void udp_read(uint8_t *buf, uint32_t len)
{
    net_udp_iface_t *iface = g_udp_network.network_iface;
    NETWORK_API(network_write)(&g_udp_network, iface->fd, (uint8_t *)"echo:", strlen("echo:"), 0);
    NETWORK_API(network_write)(&g_udp_network, iface->fd, buf, len, 0);
}

void *udp_demo(void *args)
{  
    net_udp_iface_t iface;
    iface.fd = -1;
    iface.lport = UDP_DEMO_LOCAL_PORT;
    memset(iface.ip, 0, NET_IP_ADDR_LEN);
    memcpy(iface.ip, UDP_SERVER_IPADDR, strlen(UDP_SERVER_IPADDR));
    iface.addr = 0;
    iface.rport = UDP_SERVER_PORT;
    iface.buf_len = 1024;
    iface.read_buf = malloc(iface.buf_len);
    iface.read_event = udp_read;
    memset(&(iface.from), 0, sizeof(iface.from));
    iface.fromlen = 0;
    memset(&(iface.to), 0, sizeof(iface.to));
    iface.tolen = 0;
    g_udp_network.type = NET_UDP_T;
    g_udp_network.network_iface = &iface;
    
    NETWORK_API(network_init)(&g_udp_network);
    while(1) {
        NETWORK_API(network_thread)(&g_udp_network);
        usleep(1000);
    }
    free(iface.read_buf);
    return NULL;
}

