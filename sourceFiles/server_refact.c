#include "../headerFiles/header.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "le format de la commande doit être : %s hostAdresse port\n", argv[0]);
        return (0);
    }

    int server_socket;
    struct sockaddr_in addr;
    int max_sd;
    int new_socket;
    int clients_array[4];
    int i = 0;

    for (int i = 0; i < 4; i++)
    {
        clients_array[i] = 0;
    }

    int max_client = 4;

    socklen_t client_addr_size = sizeof(addr);
    fd_set read_fs;
    struct timeval timeout;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("socket()");
        return -1;
    }

    int portno;
    portno = atoi(argv[2]);
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(portno);
    addr.sin_family = AF_INET;

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &addr, sizeof(int)) == -1)
    {
        perror("setsockopt");
        pthread_exit(NULL);
    }

    if (bind(server_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind()");
        return 1;
    }

    if (listen(server_socket, 5) < 0)
    {
        perror("listen()");
        return 1;
    }

    puts("en attente d'accepation de nouveaux clients");
    int sd = 0;

    while (1)
    {
        //initialisation du fd set qui va permettre de surveiller l'activité sur les socket avec select, c'est la première initialisation donc il n'y a que le socket du server
        FD_ZERO(&read_fs);
        FD_SET(server_socket, &read_fs);
        max_sd = server_socket;
        //max sd sert pour le select il abesoin du max socket + 1

        //on rentre les client dans le fd set pour rentrer dans la surveillance en changeant le max

        for (int i = 0; i < max_client; i++)
        {
            sd = clients_array[i];

            if (sd > 0)
                FD_SET(sd, &read_fs);

            if (sd > max_sd)
                max_sd = sd;
        }
        //surveillance des clients qui se connectent
        select(max_sd + 1, &read_fs, NULL, NULL, NULL);

        if (FD_ISSET(server_socket, &read_fs))
        {
            //accept attribut à new_socket un nouvel integer
            if ((new_socket = accept(server_socket, (struct sockaddr *)&addr, &client_addr_size)) < 0)
            {
                perror("accept");
                return 1;
            }
            puts("detect client");
            if (new_socket >= 8)
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

        for (i = 0; i < max_client; i++)
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

        puts("looping");
    }
    close(server_socket);
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