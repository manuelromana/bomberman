
#include "../headerFiles/game/game.h"

int main(void)
{

    stGame *game = game_init();
    stMenu *menu = menu_init(game->pWindow, game->pRenderer);
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
            menu_event(event, step, &infos.current_text, infos.hostname, infos.portname, *my_socket);
        }

        if (*step == 0)
        {
            //menu_draw_choix(menu, infos.choix);
            menu_draw(menu);
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
            {

                puts("loadserver");
                load_server(my_socket, infos.hostname, infos.portname);
            }
            if (*infos.choix == '2')
            {

                load_client(my_socket, infos.hostname, infos.portname);
            }
            (*step)++;
        }
        else if (*step == 4)
        {

            if (*infos.choix == '1')
            {
                create_track_client(my_socket, infos.clients_array);
            }

            game->presentTime = SDL_GetTicks();
            game->delta = game->presentTime - game->lastTime;
            game->lastTime = game->presentTime;
            game_draw(game);

            if (*infos.choix == '1')
            {
                int quit = game_event(game);
                if (quit == 1)
                {
                    *step = -1;
                }
            }
            else if (*infos.choix == '2')
            {
                game_client_event(step, *my_socket);
                read_server(*my_socket);
            }

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