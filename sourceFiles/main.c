#include "../headerFiles/header.h"

int main(int argc, char *argv[])
{

    //initialiser le jeu
    stGame *game = game_init_2();
    int quit = 0;
    char test[20];
    for (int i = 0; i < 20; i++)
    {
        test[i] = '\0';
    }

    while (quit != -1)
    {

        game_draw_2(game, test);
        quit = game_event_2(test);
        SDL_Delay(30);
    }
    //Arrêt de TTf
    TTF_Quit();
    //Destruction

    game_destroy_2(game);

    return (EXIT_SUCCESS);
}