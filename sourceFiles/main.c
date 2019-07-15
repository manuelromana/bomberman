#include "../headerFiles/header.h"

int main(int argc, char *argv[])
{
    //initialiser la ttf pour les textes
    // TTF_Init();
    // if (TTF_Init() == -1)
    // {
    //     fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    //     exit(EXIT_FAILURE);
    // }

    //initialiser le jeu
    stGame *game = game_init_2();
    int quit = 0;

    while (quit != -1)
    {
        game_draw_2(game);
        quit = game_event_2(game);
        SDL_Delay(30);
    }
    //Arrêt de TTf
    TTF_Quit();
    //Destruction
    game_destroy_2(game);

    return (EXIT_SUCCESS);
}