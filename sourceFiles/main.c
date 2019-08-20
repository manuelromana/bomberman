#include "../headerFiles/header.h"

int main(void)
{

    stGame *game = game_init_2();
    SDL_Event event;

    int *my_socket = malloc(sizeof(int *));
    memset(my_socket, '\0', 1);

    int max_client = 4;
    int clients_array[4];

    for (int i = 0; i < max_client; i++)
    {
        clients_array[i] = 0;
    }

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
        control_event(event, step, current_text, portname, *my_socket);

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

            load_server(my_socket, *hostname, *portname);
            (*step)++;
        }
        else if (*step == 3)
        {
            game_draw_welcome(game);

            create_track_client(my_socket, max_client, clients_array);
        }

        SDL_Delay(30);
    }
    TTF_Quit();

    game_destroy_2(game);
    close(*my_socket);
    free(my_socket);
    free(hostname);
    free(portname);
    free(*hostname);
    free(*portname);
    free(current_text);
    free(step);

    return (EXIT_SUCCESS);
}
