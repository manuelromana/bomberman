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

    char choix[32];
    choix[0] = 0;
    char hostname[32];
    hostname[0] = 0;
    char portname[32];
    portname[0] = 0;
    char *current_text = 0;
    current_text = choix;

    int *step = malloc(sizeof(int));
    *step = 0;

    // char **choix = 0;
    // char **hostname = 0;
    // char **portname = 0;

    // *choix = malloc(sizeof(char) * 20);
    // memset(*choix, '\0', 1);
    // *hostname = malloc(sizeof(char) * 20);
    // memset(*hostname, '\0', 1);
    // *portname = malloc(sizeof(char));
    // memset(*portname, '\0', 1);
    // char **current_text = malloc(sizeof(char) * 20);
    // *current_text = *choix;
    // memset(*current_text, '\0', 1);
    // int *step = malloc(sizeof(int *));

    // *step = 0;

    while (*step != -1)
    {
        control_event(event, step, &current_text, hostname, portname, *my_socket);

        if (*step == 0)
        {
            game_draw_choix(game, choix);
        }
        if (*step == 1)
        {
            game_draw_hostname(game, hostname);
        }
        else if (*step == 2)
        {
            game_draw_port(game, portname);
        }
        else if (*step == 3)
        {
            if (*choix == '1')
            {
                load_server(my_socket, hostname, portname);
            }
            else if (*choix == '2')
            {
                load_client(my_socket, hostname, portname);
            }

            (*step)++;
        }
        else if (*step == 4)
        {
            game_draw_welcome(game);

            create_track_client(my_socket, max_client, clients_array);
        }

        SDL_Delay(10);
    }
    TTF_Quit();

    game_destroy_2(game);
    close(*my_socket);
    free(my_socket);
    free(step);

    return (EXIT_SUCCESS);
}
