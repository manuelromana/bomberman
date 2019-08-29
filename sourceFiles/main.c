#include "../headerFiles/menu.h"
#include "../headerFiles/game/game.h"

int main(void)
{
    stMenu *menu = menu_init_2();
    stGame *game = game_network_init(menu->pWindow, menu->pRenderer);
    stInfos infos = {0};
    infos.current_text = infos.choix;
    strcpy(infos.hostname, "127.0.0.1");
    strcpy(infos.portname, "1234");
    SDL_Event event;
    int *my_socket = malloc(sizeof(int *));
    int *step = malloc(sizeof(int));

    unsigned int lastFps = 0;
    unsigned int fps = 0;

    if (!my_socket | !step)
        exit - 1;

    *step = 0;
    memset(my_socket, '\0', 1);

    while (*step != -1)
    {
        if (*step < 4)
        {
            control_event(event, step, &infos.current_text, infos.hostname, infos.portname, *my_socket);
        }

        if (*step == 0)
        {
            menu_draw_choix(menu, infos.choix);
        }
        else if (*step == 1)
        {
            menu_draw_hostname(menu, infos.hostname);
        }
        else if (*step == 2)
        {
            menu_draw_port(menu, infos.portname);
        }
        else if (*step == 3)
        {
            if (*infos.choix == '1')
                load_server(my_socket, infos.hostname, infos.portname);
            if (*infos.choix == '2')
                load_client(my_socket, infos.hostname, infos.portname);
            (*step)++;
        }
        else if (*step == 4)
        {

            create_track_client(my_socket, infos.clients_array);
            game->presentTime = SDL_GetTicks();
            draw_player_test(game);
            game_network_event(step, game);
            fps++;
            if (game->presentTime - lastFps > 1000)
            {
                printf("FPS : %d\n", fps);
                fps = 0;
                lastFps = game->presentTime;
            }
        }

        SDL_Delay(15);
    }
    TTF_Quit();
    menu_destroy_2(menu);
    game_destroy(game);
    close(*my_socket);
    free(my_socket);
    free(step);
    SDL_Quit();

    return (EXIT_SUCCESS);
}