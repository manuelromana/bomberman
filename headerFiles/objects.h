#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

typedef struct bomb bomb;
struct bomb {
  int x;
  int y;
  int tileX;
  int tileY;
  int startTime;
  struct bomb *next;
  struct bomb *prev;
};

typedef struct stBomb {
  SDL_Rect bombPositionRect;
  SDL_Texture *pTexBomb;
  bomb *bombs;
} stBomb;

#endif