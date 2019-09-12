#include "../../headerFiles/network/network.h"

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
    printf("%s %d\n", hostname, portnum);
    addr.sin_addr.s_addr = inet_addr(hostname);
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
    puts("en attente d'acceptation de nouveaux clients");
}

int create_track_client(int *my_socket, int clients_array[])
{
    struct timeval timeout = {0};
    stTrackClient trackClient = {0};
    fd_set read_fs;
    struct sockaddr_in addr;
    socklen_t client_addr_size = sizeof(addr);
    FD_ZERO(&read_fs);
    FD_SET(*my_socket, &read_fs);
    timeout.tv_sec = 0;
    trackClient.max_sd = *my_socket;

    for (int i = 0; i < MAXCLIENT; i++)
    {
        trackClient.sd = clients_array[i];

        if (trackClient.sd > 0)
            FD_SET(trackClient.sd, &read_fs);

        if (trackClient.sd > trackClient.max_sd)
            trackClient.max_sd = trackClient.sd;
    }

    select(trackClient.max_sd + 1, &read_fs, NULL, NULL, &timeout);

    if (FD_ISSET(*my_socket, &read_fs))
    {
        if (trackClient.new_socket >= (*my_socket + 4))
        {
            puts("nombre client max atteint");
            return 1;
        }

        if ((trackClient.new_socket = accept(*my_socket, (struct sockaddr *)&addr, &client_addr_size)) < 0)
        {

            perror("connect:");
            puts("server socket");
            return 1;
        }

        printf("detect client new_s: %i\n", trackClient.new_socket);

        for (int i = 0; i < MAXCLIENT; i++)
        {
            if (clients_array[i] == 0)
            {
                clients_array[i] = trackClient.new_socket;

                printf("add new client :%i", trackClient.new_socket);
                if (send(trackClient.new_socket, "hello\n", 6, MSG_NOSIGNAL) < 0)
                {
                    puts("send failed");
                    puts("toto");

                    return 1;
                }

                break;
            }
        }
    }

    for (int i = 0; i < MAXCLIENT; i++)
    {
        trackClient.sd = clients_array[i];

        if (FD_ISSET(trackClient.sd, &read_fs))
        {
            if (read_client(trackClient.sd) == -1)
            {
                puts("client disconnected");
                close(trackClient.sd);
                clients_array[i] = 0;
            }
        }
    }

    return 1;
}

int read_client(int client)
{
    int n = 0;
    char buff[128];

    if (client == -1)
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

int load_client(int *mysocket, char *hostname, char *portname)
{
    struct sockaddr_in addr;
    char message[128];
    *mysocket = socket(AF_INET, SOCK_STREAM, 0);
    if (*mysocket < 0)
    {
        perror("socket()");
        return 1;
    }
    printf("%s %s\n", hostname, portname);
    int portno = atoi(portname);
    addr.sin_addr.s_addr = inet_addr(hostname);
    addr.sin_port = htons(portno);
    addr.sin_family = AF_INET;

    if (connect(*mysocket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect()");
        return 1;
    }
    //lecture et affichage du message de bienvenu du client dans la console
    memset(message, '\0', 128);
    read(*mysocket, message, 128);
    printf("%s\n", message);
}

void send_key(SDL_Keycode keydown, int mysocket)
{
    switch (keydown)
    {
    case SDLK_UP:
        if (send(mysocket, "up\n", 3, MSG_NOSIGNAL) < 0)
        {
            puts("send failed");
            close(mysocket);
        }
        break;
    case SDLK_DOWN:
        if (send(mysocket, "Down\n", 5, MSG_NOSIGNAL) < 0)
        {
            puts("send failed");
            close(mysocket);
        }
        break;
    case SDLK_RIGHT:
        if (send(mysocket, "Right\n", 6, MSG_NOSIGNAL) < 0)
        {
            puts("send failed");
            close(mysocket);
        }
        break;
    case SDLK_LEFT:
        if (send(mysocket, "Left\n", 5, MSG_NOSIGNAL) < 0)
        {
            puts("send failed");
            close(mysocket);
        }
        break;
    case SDLK_SPACE:
        if (send(mysocket, "Action\n", 7, MSG_NOSIGNAL) < 0)
        {
            puts("send failed");
            close(mysocket);
        }
        break;
    }
}

void game_client_event(int *step, int serverSocket)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case (SDL_QUIT):
            *step = -1;
        case (SDL_KEYDOWN):
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_RIGHT:
            case SDLK_LEFT:
            case SDLK_SPACE:
                send_key(event.key.keysym.sym, serverSocket);
                break;
            }
        }
    }
}