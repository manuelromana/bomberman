#include "../headerFiles/game.h"

int main(int argc, char *argv[])
{
    stGame *game = game_init();

    int quit = 0;
    
    while(quit != 1) {
        game_draw(game);
        quit = game_event(game);
        SDL_Delay(30);
    }

    game_destroy(game);

    SDL_Quit();
    return (EXIT_SUCCESS);
}