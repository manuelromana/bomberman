#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "player.h"
#include "map.h"

typedef struct {
    SDL_Point screenSize;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

    struct {
        int playerDirection;
        SDL_Rect playerPositionRect;
    } playerPosition;

    struct {
        SDL_Texture* pTexPlayerFront;
        SDL_Texture* pTexPlayerBack;
        SDL_Texture* pTexPlayerRight;
        SDL_Texture* pTexPlayerLeft;

        playerPosition* pPos1;
    } player;

    struct stMap* map;
} stGame;

stGame* game_init();

void game_draw(stGame* game);
void game_destroy(stGame *game);


int game_event(stGame *game);
void character_move(SDL_Keycode direction, stGame *game);


void load_surface(SDL_Surface* surface, stGame *game);

void draw_bomb(stGame* game);
void draw_map(stGame* game);
void load_map(stGame* game);

#endif