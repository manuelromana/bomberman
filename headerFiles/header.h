#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

typedef struct {
    //Fenêtre
    SDL_Point screenSize;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

    //Textures
    SDL_Texture* pTexPlayer;
    SDL_Texture* pTexBomb;

    SDL_Rect playerPositionRect;
} stGame;


stGame* game_init();
void game_destroy(stGame* game);
void game_draw(stGame* game);
int game_event(stGame *game);
void character_move(SDL_Keycode direction, stGame *game);


#endif