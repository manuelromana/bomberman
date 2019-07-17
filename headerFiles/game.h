#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "player.h"
#include "map.h"

typedef struct stGame {
    SDL_Point screenSize;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

    struct stPlayerPosition* pPos1;

    struct stPlayer* player;

    struct stMap* map;
} stGame;

stGame* game_init();
void draw_bomb(stGame* game);

void game_draw(stGame* game, stPlayer* player, stMap* map);
int game_event(stGame *game);
void game_destroy(stGame *game);

void character_move(SDL_Keycode direction, stPlayer *player,stGame* game);

stPlayerPosition* playerPosition_init(stPlayer* p1, stGame* game);

void load_surface(SDL_Surface* surface, stGame *game);

#endif