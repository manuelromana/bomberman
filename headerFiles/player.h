#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "game.h"

extern stGame game;

typedef struct {
    int playerDirection;

    SDL_Rect playerPositionRect;
} playerPosition;

typedef struct {
    SDL_Texture* pTexPlayerFront;
    SDL_Texture* pTexPlayerBack;
    SDL_Texture* pTexPlayerRight;
    SDL_Texture* pTexPlayerLeft;

    playerPosition* pPos1;
} player;

playerPosition* playerPosition_init(stGame* game, player* p1);
player* player_init(stGame* game);
/*
int game_event(stGame *game);
void character_move(SDL_Keycode direction, stGame *game);
*/
void player_destroy(player* p1);
#endif