#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "game.h"

#define HAUTEURMAP 15
#define LARGEURMAP 19
 
typedef struct {
    int map[HAUTEURMAP][LARGEURMAP];
    
    SDL_Renderer* pRenderer;
    SDL_Texture* pTexBomb;
    SDL_Texture* pTexWall;
    SDL_Rect bombPositionRect;
    SDL_Rect wallPosition;

} stMap;

stMap* map_init();
void draw_map(stMap* map);
void load_map(stMap* map);

/* 
void load_surface(SDL_Surface* surface, stGame *game);

*/
void map_destroy(stMap* map);
#endif