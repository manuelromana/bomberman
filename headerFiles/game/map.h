#ifndef MAP_H
#define MAP_H

#define HAUTEURMAP 15
#define LARGEURMAP 19
#define WALLPOSITIONW 64
#define WALLPOSITIONH 128

typedef struct stMap {
  int map[HAUTEURMAP][LARGEURMAP];

  SDL_Texture *pTexExplosionWall;
  SDL_Rect wallPosition;
  SDL_Rect exploWallPosition;

} stMap;

#endif