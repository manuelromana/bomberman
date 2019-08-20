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

int create_track_client(int *my_socket, int max_client, int clients_array[])
{
    fd_set read_fs;
    struct timeval timeout;
    int sd = 0;
    int max_sd;
    int new_socket = 0;
    struct sockaddr_in addr;
    socklen_t client_addr_size = sizeof(addr);
    FD_ZERO(&read_fs);
    FD_SET(*my_socket, &read_fs);
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    max_sd = *my_socket;
    // //max sd sert pour le select il abesoin du max socket + 1
    // //on rentre les client dans le fd set pour rentrer dans la surveillance en changeant le max

    for (int i = 0; i < max_client; i++)
    {
        sd = clients_array[i];

        if (sd > 0)
            FD_SET(sd, &read_fs);

        if (sd > max_sd)
            max_sd = sd;
    }
    // //surveillance des clients qui se connectent
    select(max_sd + 1, &read_fs, NULL, NULL, &timeout);

    if (FD_ISSET(*my_socket, &read_fs))
    {
        //accept attribut à new_socket un nouvel integer
        if ((new_socket = accept(*my_socket, (struct sockaddr *)&addr, &client_addr_size)) < 0)
        {
            perror("connect:"); //attention le server ne peut pas se connecter à lui même
            return 1;
        }

        printf("detect client new_s: %i\n", new_socket);
        if (new_socket >= (*my_socket + 4))
        {
            puts("nombre client max atteint");
        }

        for (int i = 0; i < max_client; i++)
        {
            if (clients_array[i] == 0)
            {
                clients_array[i] = new_socket;

                printf("add new client :%i", new_socket);
                if (send(new_socket, "hello\n", 6, MSG_NOSIGNAL) < 0)
                {
                    puts("send failed");
                    return 1;
                }

                break;
            }
        }
    }

    for (int i = 0; i < max_client; i++)
    {
        sd = clients_array[i];

        if (FD_ISSET(sd, &read_fs))
        {
            if (read_client(sd) == -1)
            {
                puts("client disconnected");
                close(sd);
                clients_array[i] = 0;
            }
            //dans les autres cas read client se lance quand même
        }
    }
    puts("loop");
}

int read_client(int client)
{
    int n = 0;
    char buff[128];

    if (client == -1) //normalement il n'a pas de cas ou sd = -1
        return 1;

    memset(buff, '\0', 128);
    while ((n = recv(client, buff, 128, 0)) >= 0)
    {
        if (n == 0)
            return -1;

        printf("received in server %s", buff);

        if (buff[n - 1] == '\n')
        {
            memset(buff, '\0', 128);
            break;
        }
    }

    return n;
}
