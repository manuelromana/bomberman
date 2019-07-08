#include "../headerFiles/header.h"

void character_move(SDL_Keycode direction, stGame *game) {
    switch (direction) {
            case SDLK_RIGHT:
                if(game->playerPositionRect.x < (game->screenSize.x - game->playerPositionRect.w))
                    game->playerPositionRect.x += 10;
                    game->playerDirection = 0;
                break;
            case SDLK_LEFT:
                if(game->playerPositionRect.x > 0)
                    game->playerPositionRect.x -= 10;
                game->playerDirection = 1;
                break;
            case SDLK_UP:
                if(game->playerPositionRect.y > 0)
                    game->playerPositionRect.y -= 10;
                game->playerDirection = 2;
                break;
            case SDLK_DOWN: 
                if(game->playerPositionRect.y < (game->screenSize.y - game->playerPositionRect.h))
                    game->playerPositionRect.y += 10;
                game->playerDirection = 3;
                break;  
            case SDLK_SPACE:
                draw_bomb(game, 1);
                break;
    }
}