#include "../headerFiles/header.h"

int main(void)
{
    stGame *game = game_init_2();
    stInfos infos = {0};
    infos.current_text = infos.choix;
    SDL_Event event;
    int *my_socket = malloc(sizeof(int *));
    int *step = malloc(sizeof(int));
    
    if (!my_socket | !step)
        exit -1;
    
    *step = 0;
    memset(my_socket, '\0', 1);

    while (*step != -1) {
        control_event(event, step, &infos.current_text, infos.hostname, infos.portname, *my_socket);

        if (*step == 0) {
            game_draw_choix(game, infos.choix);
        }  else if (*step == 1) {
            game_draw_hostname(game, infos.hostname);
        } else if (*step == 2) {
            game_draw_port(game, infos.portname);
        } else if (*step == 3) {
            if (*infos.choix == '1')
                load_server(my_socket, infos.hostname, infos.portname);
            if (*infos.choix == '2')
                load_client(my_socket, infos.hostname, infos.portname);
            (*step)++;
        } else if (*step == 4) {
            game_draw_welcome(game);
            create_track_client(my_socket, infos.clients_array);
        }

        SDL_Delay(30);
    }
    TTF_Quit();

    game_destroy_2(game);
    close(*my_socket);
    free(my_socket);
    free(step);

    return (EXIT_SUCCESS);
}