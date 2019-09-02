#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>

#define PATHBOMB "assets/Bomb/Bomb_f01.png"
#define PATHPLFR "assets/Bomberman/Front/Bman_F_f00.png"
#define PATHPLBCK "assets/Bomberman/Back/Bman_B_f00.png"
#define PATHPLSIDE "assets/Bomberman/Side/Bman_F_f00.png"
#define PATHWALL "assets/Blocks/SolidBlock.png"
#define PATHFLAME "assets/Flame/Flame_f00.png"
#define PATHEXPBCK "assets/Blocks/ExplodableBlock.png"

#define LEN(arr) ((int)(sizeof(arr) / sizeof(arr[0])))

typedef struct stTexture
{
  SDL_Surface *surface;
  SDL_Texture *texture;
  char *path;
} stTexture;

#endif