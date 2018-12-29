#include "common.h"
#include "network.h"

void *udp_demo(void *args);
void *tcp_client_demo(void *args);
void *tcp_server_demo(void *args);

int main(int argc, char *argv[])
{
    pthread_t udp_pthread;
    pthread_t tcp_client_pthread;
    pthread_t tcp_server_pthread;
    pthread_create(&udp_pthread, NULL, udp_demo, NULL);
    pthread_create(&tcp_client_pthread, NULL, tcp_client_demo, NULL);
    pthread_create(&tcp_server_pthread, NULL, tcp_server_demo, NULL);

    pthread_join(udp_pthread, NULL);
    pthread_join(tcp_client_pthread, NULL);
    pthread_join(tcp_server_pthread, NULL);
    return 0;
}

