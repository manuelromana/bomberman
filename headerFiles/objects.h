#ifndef OBJECTS_H
#define OBJECTS_H

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
  bomb *bombs;
} stBomb;

#endif