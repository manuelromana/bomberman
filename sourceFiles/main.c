#include "../headerFiles/game.h"

int main(int argc, char *argv[])
{

    //initialiser le jeu
    stGame *game = game_init_2();
    int quit = 0;
<<<<<<< HEAD
    
    while(quit != 1) {
        game_draw(game);
        quit = game_event(game);
=======
    char test[20];
    for (int i = 0; i < 20; i++)
    {
        test[i] = '\0';
    }

    while (quit != -1)
    {

        game_draw_2(game, test);
        quit = game_event_2(test);
>>>>>>> 355992318ef981401873e1b6fcbc88b2b2689555
        SDL_Delay(30);
    }
    //Arrêt de TTf
    TTF_Quit();
    //Destruction

    game_destroy_2(game);

    return (EXIT_SUCCESS);
}