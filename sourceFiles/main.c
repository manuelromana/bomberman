#include "../headerFiles/header.h"

int main(int argc, char* argv[]) {
    stGame* game = game_init();
    int quit = 0;
    
    while(quit != 1) {
        game_draw(game, 0);

        quit = game_event(game);

        SDL_Delay(30);
    }
        
    //Destruction
    game_destroy(game);

    return (EXIT_SUCCESS);
}   