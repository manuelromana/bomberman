#include "../headerFiles/player.h"
#include "../headerFiles/game.h"

player* player_init(stGame* game) {
    player* p1 = NULL;
    p1 = malloc(sizeof (p1));

    game->p1->pTexPlayerFront = NULL;
    game->p1->pTexPlayerBack = NULL;
    game->p1->pTexPlayerRight = NULL;
    game->p1->pTexPlayerLeft = NULL;

    SDL_Surface* frontBomberman = IMG_Load("assets/Bomberman/Front/Bman_F_f00.png");
    SDL_Surface* backBomberman = IMG_Load("assets/Bomberman/Back/Bman_B_f00.png");
    SDL_Surface* rightSideBomberman = IMG_Load("assets/Bomberman/Side/Bman_F_f00.png");
    SDL_Surface* leftSideBomberman = IMG_Load("assets/Bomberman/Side/Bman_F_f00.png");

    if (!frontBomberman || !backBomberman) {
        fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
        player_destroy(p1);
        return NULL;
    } else {
        game->p1->pTexPlayerFront = SDL_CreateTextureFromSurface(game->pRenderer, frontBomberman);
        game->p1->pTexPlayerBack = SDL_CreateTextureFromSurface(game->pRenderer, backBomberman);
        game->p1->pTexPlayerRight = SDL_CreateTextureFromSurface(game->pRenderer, rightSideBomberman);
        game->p1->pTexPlayerLeft = SDL_CreateTextureFromSurface(game->pRenderer, leftSideBomberman);
        if (!game->p1->pTexPlayerFront || !game->p1->pTexPlayerBack) {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            player_destroy(p1);
            return NULL;
        }
    }
}

playerPosition* playerPosition_init(stGame* game, player* p1) {
    playerPosition* pPos1 = NULL;
    pPos1 = malloc(sizeof (pPos1));

    game->p1->pPos1->playerDirection = 0;
    game->p1->pPos1->playerPositionRect.x = game->screenSize.x / 2;
    game->p1->pPos1->playerPositionRect.y = game->screenSize.y / 2;
    game->p1->pPos1->playerPositionRect.w = 64;
    game->p1->pPos1->playerPositionRect.h = 128;

}
    
int game_event(stGame *game) {
    int quit = 0;
    SDL_Event e;

    while(SDL_PollEvent( &e ) != 0) {
        if(e.type == SDL_QUIT) {
            quit = 1;
        } else if(e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
                case SDLK_RIGHT:
                case SDLK_LEFT:
                case SDLK_UP:
                case SDLK_DOWN:
                case SDLK_SPACE:
                    character_move(e.key.keysym.sym, game);
                    break; 
                case SDLK_ESCAPE :   
                    quit = 1;
                    break; 
            }
        }
    }
    return quit;
}

void character_move(SDL_Keycode direction, stGame *game) {
    switch (direction) {
            case SDLK_RIGHT:
                if(game->p1->pPos1->playerPositionRect.x < (game->screenSize.x - game->p1->pPos1->playerPositionRect.w))
                    game->p1->pPos1->playerPositionRect.x += 20;
                game->p1->pPos1->playerDirection = 0;
                break;
            case SDLK_LEFT:
                if(game->p1->pPos1->playerPositionRect.x > 0)
                    game->p1->pPos1->playerPositionRect.x -= 20;
                game->p1->pPos1->playerDirection = 1;
                break;
            case SDLK_UP:
                if(game->p1->pPos1->playerPositionRect.y > 0)
                    game->p1->pPos1->playerPositionRect.y -= 20;
                game->p1->pPos1->playerDirection = 2;
                break;
            case SDLK_DOWN: 
                if(game->p1->pPos1->playerPositionRect.y < (game->screenSize.y - game->p1->pPos1->playerPositionRect.h))
                    game->p1->pPos1->playerPositionRect.y += 20;
                game->p1->pPos1->playerDirection = 3;
                break;  
            case SDLK_SPACE:
                draw_bomb(game);
                break;
    }
}


void player_destroy(player* p1) {
    if (p1) {
        SDL_DestroyTexture(p1->pTexPlayerFront);
        SDL_DestroyTexture(p1->pTexPlayerBack);
        SDL_DestroyTexture(p1->pTexPlayerLeft);
        SDL_DestroyTexture(p1->pTexPlayerRight);
        
        free(p1);
    }
}