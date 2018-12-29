#include "common.h"
#include  "network.h"

#define TCP_SERVER_IPADDR "192.168.56.1"
#define TCP_SERVER_PORT   8000


static network_t g_tcp_client_network;

static void tcp_client_connect(uint8_t state)
{
    net_tcp_client_iface_t *iface = g_tcp_client_network.network_iface;
    if(state) {
        printf("connect\r\n");
        NETWORK_API(network_write)(&g_tcp_client_network, iface->fd, (uint8_t *)"connect", strlen("connect"), 0);
    } else {
        printf("disconnect\r\n");
    }
}

static void tcp_client_read(uint8_t *buf, uint32_t len)
{
    net_tcp_client_iface_t *iface = g_tcp_client_network.network_iface;
    NETWORK_API(network_write)(&g_tcp_client_network, iface->fd, (uint8_t *)"echo:", strlen("echo:"), 0);
    NETWORK_API(network_write)(&g_tcp_client_network, iface->fd, buf, len, 0);
}

void *tcp_client_demo(void *args)
{
    net_tcp_client_iface_t iface;
    memset(&iface, 0, sizeof(iface));
    iface.fd = -1;
    memcpy(iface.ip, TCP_SERVER_IPADDR, strlen(TCP_SERVER_IPADDR));
    iface.port = TCP_SERVER_PORT;
    iface.buf_len = 1024;
    iface.read_buf = malloc(iface.buf_len);
    iface.reconnect = 1;
    iface.reconn_int = 1000;
    iface.read_event = tcp_client_read;
    iface.connect_event = tcp_client_connect;
    g_tcp_client_network.type = NET_TCP_CLIENT_T;
    g_tcp_client_network.network_iface = &iface;

    NETWORK_API(network_init)(&g_tcp_client_network);
    while(1) {
        NETWORK_API(network_thread)(&g_tcp_client_network);
        usleep(1000);
    }
    free(iface.read_buf);
    return NULL;
}

