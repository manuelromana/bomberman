#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

typedef struct stPlayer {
  SDL_Texture *pTexPlayerFront;
  SDL_Texture *pTexPlayerBack;
  SDL_Texture *pTexPlayerRight;
  SDL_Texture *pTexPlayerLeft;

  SDL_Rect playerColisionRect;
  SDL_Rect playerPositionRect;
  int playerDirection;
  double playerX, playerY;
} stPlayer;

#endif