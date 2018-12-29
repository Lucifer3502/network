#include "common.h"
#include "network.h"

#define TCP_SERVER_LOCAL_PORT  8080
#define TCP_SERVER_CLI_MAX_NUM 3

static network_t g_tcp_server_network;

static void tcp_server_connect_cb(int32_t fd, uint8_t state)
{
    //eg_tcp_server_iface_t *iface = network.network_iface;
    if(state) {
        printf("connect, fd = %d\r\n", fd);
        NETWORK_API(network_write)(&g_tcp_server_network, fd, (uint8_t *)"connect", strlen("connect"), 0);
    } else {
        printf("disconnect, fd = %d\r\n", fd);
    }
}

static void tcp_server_read(int32_t fd, uint8_t *buf, uint32_t len)
{
    //eg_tcp_client_iface_t *iface = network.network_iface;
    NETWORK_API(network_write)(&g_tcp_server_network, fd, (uint8_t *)"echo:", strlen("echo:"), 0);
    NETWORK_API(network_write)(&g_tcp_server_network, fd, buf, len, 0);
}

void *tcp_server_demo(void *args)
{
    net_tcp_server_iface_t iface;
    iface.fd = -1;
    iface.port = TCP_SERVER_LOCAL_PORT;
    iface.cli_num = TCP_SERVER_CLI_MAX_NUM;
    iface.buf_len = 1024;
    iface.read_buf = malloc(iface.buf_len);
    iface.connect_event = tcp_server_connect_cb;
    iface.read_event = tcp_server_read;
    g_tcp_server_network.type = NET_TCP_SERVER_T;
    g_tcp_server_network.network_iface = &iface;

    NETWORK_API(network_init)(&g_tcp_server_network);
    while(1) {
        NETWORK_API(network_thread)(&g_tcp_server_network);
        usleep(1000);
    }
    free(iface.read_buf);
    return NULL;
}

