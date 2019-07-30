#include "../headerFiles/player.h"
#include "../headerFiles/game.h"
#include "../headerFiles/map.h"

stGame* player_init(stGame* game) {
    game->player->playerPositionRect.x = 60;
    game->player->playerPositionRect.y = 60;
    game->player->playerPositionRect.w = 64;
    game->player->playerPositionRect.h = 128;

    return game;
}
    
void character_move(SDL_Keycode direction,stGame* game) {
    switch (direction) {
            case SDLK_RIGHT:
                if(game->player->playerPositionRect.x < (game->screenSize.x - game->player->playerPositionRect.w))
                    game->player->playerPositionRect.x += 20;
                game->player->playerDirection = 0;
                break;
            case SDLK_LEFT:
                if(game->player->playerPositionRect.x > 0)
                    game->player->playerPositionRect.x -= 20;
                game->player->playerDirection = 1;
                break;
            case SDLK_UP:
                if(game->player->playerPositionRect.y > 0)
                    game->player->playerPositionRect.y -= 20;
                game->player->playerDirection = 2;
                break;
            case SDLK_DOWN: 
                if(game->player->playerPositionRect.y < (game->screenSize.y - game->player->playerPositionRect.h))
                    game->player->playerPositionRect.y += 20;
                game->player->playerDirection = 3;
                break;  
            case SDLK_SPACE:
                draw_bomb(game);
                break;
    }
}