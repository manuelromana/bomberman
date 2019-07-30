#include "../headerFiles/player.h"
#include "../headerFiles/game.h"
#include "../headerFiles/map.h"

stPlayer* player_init(stGame* game) {
    stPlayer* player = {0};
    player = malloc(sizeof (player));

    SDL_Surface* frontBomberman = IMG_Load("assets/Bomberman/Front/Bman_F_f00.png");
    SDL_Surface* backBomberman = IMG_Load("assets/Bomberman/Back/Bman_B_f00.png");
    SDL_Surface* rightSideBomberman = IMG_Load("assets/Bomberman/Side/Bman_F_f00.png");
    SDL_Surface* leftSideBomberman = IMG_Load("assets/Bomberman/Side/Bman_F_f00.png");

    if (!frontBomberman || !backBomberman) {
        fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
        player_destroy(player);
        return NULL;
    } else {
        player->pTexPlayerFront = SDL_CreateTextureFromSurface(game->pRenderer, frontBomberman);
        player->pTexPlayerBack = SDL_CreateTextureFromSurface(game->pRenderer, backBomberman);
        player->pTexPlayerRight = SDL_CreateTextureFromSurface(game->pRenderer, rightSideBomberman);
        player->pTexPlayerLeft = SDL_CreateTextureFromSurface(game->pRenderer, leftSideBomberman);
        if (!player->pTexPlayerFront || !player->pTexPlayerBack) {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            player_destroy(player);
            return NULL;
        }
    }
    
    player->playerPositionRect.x = 60;
    player->playerPositionRect.y = 60;
    player->playerPositionRect.w = 64;
    player->playerPositionRect.h = 128;
}
    
void character_move(SDL_Keycode direction,stGame* game) {
    switch (direction) {
            case SDLK_RIGHT:
                if(game->player.playerPositionRect.x < (game->screenSize.x - game->player.playerPositionRect.w))
                    game->player.playerPositionRect.x += 20;
                game->player.playerDirection = 0;
                break;
            case SDLK_LEFT:
                if(game->player.playerPositionRect.x > 0)
                    game->player.playerPositionRect.x -= 20;
                game->player.playerDirection = 1;
                break;
            case SDLK_UP:
                if(game->player.playerPositionRect.y > 0)
                    game->player.playerPositionRect.y -= 20;
                game->player.playerDirection = 2;
                break;
            case SDLK_DOWN: 
                if(game->player.playerPositionRect.y < (game->screenSize.y - game->player.playerPositionRect.h))
                    game->player.playerPositionRect.y += 20;
                game->player.playerDirection = 3;
                break;  
            case SDLK_SPACE:
                draw_bomb(game);
                break;
    }
}


void player_destroy(stPlayer* player) {
    if (player) {
        SDL_DestroyTexture(player->pTexPlayerFront);
        SDL_DestroyTexture(player->pTexPlayerBack);
        SDL_DestroyTexture(player->pTexPlayerLeft);
        SDL_DestroyTexture(player->pTexPlayerRight);
        
        free(player);
    }
}