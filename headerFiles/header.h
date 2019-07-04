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
    SDL_Texture* pTexPlayerFront;
    SDL_Texture* pTexPlayerBack;
    SDL_Texture* pTexPlayerRight;
    SDL_Texture* pTexPlayerLeft;
    SDL_Texture* pTexBomb;

    int playerDirection;


    SDL_Rect playerPositionRect;
    SDL_Rect bombPositionRect;
} stGame;




stGame* game_init();
void game_destroy(stGame* game);
void game_draw(stGame* game);
int game_event(stGame *game);
void character_move(SDL_Keycode direction, stGame *game);

#endif