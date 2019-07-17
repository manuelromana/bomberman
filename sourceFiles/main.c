#include "../headerFiles/game.h"
#include "../headerFiles/map.h"
#include "../headerFiles/player.h"

int main(int argc, char *argv[])
{
    //initialiser le jeu
    stGame *game = game_init();
    stMap *map = map_init();
    stPlayer *player = player_init();

    int quit = 0;
    
    while(quit != 1) {
        game_draw(game, player, map);
        quit = game_event(game);
        SDL_Delay(30);
    }
    //Arrêt de TTf
    //Destruction

    game_destroy(game);

    return (EXIT_SUCCESS);
}