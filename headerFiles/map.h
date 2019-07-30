#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define HAUTEURMAP 15
#define LARGEURMAP 19
 
typedef struct stMap {
    int map[HAUTEURMAP][LARGEURMAP];
    
    SDL_Texture *pTexBomb;
    SDL_Texture *pTexWall;
    SDL_Rect bombPositionRect;
    SDL_Rect wallPosition;
} stMap;

#endif