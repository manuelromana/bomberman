#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define HAUTEURMAP 15
#define LARGEURMAP 19
#define WALLPOSITIONW 64
#define WALLPOSITIONH 128

typedef struct stMap {
  int map[HAUTEURMAP][LARGEURMAP];

  SDL_Texture *pTexBomb;
  SDL_Texture *pTexWall;
  SDL_Rect wallPosition;
} stMap;

#endif