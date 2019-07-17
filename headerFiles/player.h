#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "game.h"


typedef struct stPlayerPosition {
    int playerDirection;

    SDL_Rect playerPositionRect;
} stPlayerPosition;

typedef struct stPlayer {
    SDL_Renderer* pRenderer;
    
    SDL_Texture* pTexPlayerFront;
    SDL_Texture* pTexPlayerBack;
    SDL_Texture* pTexPlayerRight;
    SDL_Texture* pTexPlayerLeft;

    struct stPlayerPosition* pPos1;
} stPlayer;

stPlayer* player_init();

/*
int game_event(stGame *game);
*/
void player_destroy(stPlayer* p1);
#endif