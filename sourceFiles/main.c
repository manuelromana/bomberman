#include "../headerFiles/menu.h"
#include "../headerFiles/game/game.h"

int main(void)
{
    stMenu *menu = menu_init_2();
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
            menu_draw_choix(menu, infos.choix);
        }  else if (*step == 1) {
            menu_draw_hostname(menu, infos.hostname);
        } else if (*step == 2) {
            menu_draw_port(menu, infos.portname);
        } else if (*step == 3) {
            if (*infos.choix == '1')
                load_server(my_socket, infos.hostname, infos.portname);
            if (*infos.choix == '2')
                load_client(my_socket, infos.hostname, infos.portname);
            (*step)++;
        } else if (*step == 4) {
            menu_destroy_2(menu);
            stGame *game = game_init();
            game_boucle(game);
            create_track_client(my_socket, infos.clients_array);
            game_destroy(game);
        }

        SDL_Delay(10);
    }
    TTF_Quit();

    close(*my_socket);
    free(my_socket);
    free(step);
    SDL_Quit();

    return (EXIT_SUCCESS);
}