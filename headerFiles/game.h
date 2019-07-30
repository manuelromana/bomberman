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

    stPlayer player;
    stMap map;
} stGame;

stGame* game_init();
stPlayer* player_init(stGame* game);
stMap* map_init(stGame* game);
void draw_map(stMap* map, stGame* game);
void load_map(stMap* map, stGame* game);

void draw_bomb(stGame* game);

int game_event(stGame *game);
void game_destroy(stGame *game);


void game_draw(stGame* game, stPlayer* player, stMap* map);
void character_move(SDL_Keycode direction,stGame* game);

#endif