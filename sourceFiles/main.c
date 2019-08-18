#include "../headerFiles/header.h"

int main(void)
{

    stGame *game = game_init_2();
    SDL_Event event;

    int server_socket;
    int portnum;
    struct sockaddr_in addr;
    int sd = 0;
    int max_sd;
    int new_socket;
    int clients_array[4];

    for (int i = 0; i < 4; i++)
    {
        clients_array[i] = 0;
    }

    int max_client = 4;

    socklen_t client_addr_size = sizeof(addr);
    fd_set read_fs;

    char **hostname = malloc(sizeof(char *));
    char **portname = malloc(sizeof(char *));
    *hostname = malloc(sizeof(char *));
    memset(*hostname, '\0', 1);
    *portname = malloc(sizeof(char *));
    memset(*portname, '\0', 1);
    char **current_text = malloc(sizeof(char *));
    *current_text = *hostname;
    memset(*current_text, '\0', 1);
    int *step = malloc(sizeof(int *));
    *step = 0;

    while (*step != -1)
    {
        control_event(event, step, current_text, portname, server_socket);

        if (*step == 0)
        {
            game_draw_hostname(game, *hostname);
        }
        else if (*step == 1)
        {
            game_draw_port(game, *portname);
        }
        else if (*step == 2)
        {

            // mysocket = socket(AF_INET, SOCK_STREAM, 0);
            // if (mysocket < 0)
            // {
            //     perror("socket()");
            //     break;
            // }
            // printf("%s %s\n", *hostname, *portname);
            // portno = atoi(*portname);
            // addr.sin_addr.s_addr = inet_addr(*hostname);
            // addr.sin_port = htons(portno);
            // addr.sin_family = AF_INET;

            // if (connect(mysocket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
            // {
            //     perror("connect()");
            //     break;
            // }
            // //lecture et affichage du message de bienvenu du client dans la console
            // memset(message, '\0', 128);
            // read(mysocket, message, 128);
            // printf("%s\n", message);

            //server
            server_socket = socket(AF_INET, SOCK_STREAM, 0);
            if (server_socket < 0)
            {
                perror("socket()");
                return -1;
            }

            portnum = atoi(*portname);
            addr.sin_addr.s_addr = inet_addr(*hostname);
            addr.sin_port = htons(portnum);
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
            printf("serv_sock = %i", server_socket);

            puts("en attente d'accepation de nouveaux clients");

            (*step)++;
        }
        else if (*step == 3)
        {
            game_draw_welcome(game);

            // //initialisation du fd set qui va permettre de surveiller l'activité sur les socket avec select, c'est la première initialisation donc il n'y a que le socket du server
            // FD_ZERO(&read_fs);
            // FD_SET(server_socket, &read_fs);
            // max_sd = server_socket;
            // //max sd sert pour le select il abesoin du max socket + 1

            // //on rentre les client dans le fd set pour rentrer dans la surveillance en changeant le max

            // for (int i = 0; i < max_client; i++)
            // {
            //     sd = clients_array[i];

            //     if (sd > 0)
            //         FD_SET(sd, &read_fs);

            //     if (sd > max_sd)
            //         max_sd = sd;
            // }
            // //surveillance des clients qui se connectent
            // select(max_sd + 1, &read_fs, NULL, NULL, NULL);

            // if (FD_ISSET(server_socket, &read_fs))
            // {
            //     //accept attribut à new_socket un nouvel integer
            //     if ((new_socket = accept(server_socket, (struct sockaddr *)&addr, &client_addr_size)) < 0)
            //     {
            //         perror("accept");
            //         return 1;
            //     }

            //     printf("detect client new_s: %i\n", new_socket);
            //     if (new_socket >= 8)
            //     {
            //         puts("nombre client max atteint");
            //     }

            //     for (int i = 0; i < max_client; i++)
            //     {
            //         if (clients_array[i] == 0)
            //         {
            //             clients_array[i] = new_socket;

            //             printf("add new client :%i", new_socket);
            //             if (send(new_socket, "hello\n", 6, MSG_NOSIGNAL) < 0)
            //             {
            //                 puts("send failed");
            //                 return 1;
            //             }

            //             break;
            //         }
            //     }
            // }

            // for (int i = 0; i < max_client; i++)
            // {
            //     sd = clients_array[i];

            //     if (FD_ISSET(sd, &read_fs))
            //     {
            //         if (read_client(sd) == -1)
            //         {
            //             puts("client disconnected");
            //             close(sd);
            //             clients_array[i] = 0;
            //         }
            //         //dans les autres cas read client se lance quand même
            //     }
            // }
        }

        SDL_Delay(30);
    }
    TTF_Quit();

    game_destroy_2(game);
    close(server_socket);

    return (EXIT_SUCCESS);
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
