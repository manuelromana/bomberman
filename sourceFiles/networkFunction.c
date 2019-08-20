#include "../headerFiles/network.h"

int load_server(int *my_socket, char *hostname, char *portname)
{
    struct sockaddr_in addr;
    *my_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (*my_socket < 0)
    {
        perror("socket()");
        return -1;
    }

    int portnum = atoi(portname);
    addr.sin_addr.s_addr = inet_addr(hostname);
    //atoi et inet_addr prennent des char * en paramètre
    addr.sin_port = htons(portnum);
    addr.sin_family = AF_INET;
    if (setsockopt(*my_socket, SOL_SOCKET, SO_REUSEADDR, &addr, sizeof(int)) == -1)
    {
        perror("setsockopt");
        pthread_exit(NULL);
    }

    if (bind(*my_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind()");
        return 1;
    }

    if (listen(*my_socket, 5) < 0)
    {
        perror("listen()");
        return 1;
    }
    printf("serv_sock = %i\n", *my_socket);

    puts("en attente d'accepation de nouveaux clients");
}