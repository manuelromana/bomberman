#ifndef OBJECTS_H
#define OBJECTS_H

#define EXPLOSION_SPREAD_TIME 100

typedef struct bomb bomb;
struct bomb {
  int x;
  int y;
  int tileX;
  int tileY;
  int startTime;
  int power;
  struct bomb *next;
  struct bomb *prev;
};

typedef struct explosion explosion;
struct explosion {
  int x;
  int y;
  int tileX;
  int tileY;
  int startTime;
  struct explosion *next;
  struct explosion *prev;
};

typedef struct stObject {
  SDL_Rect bombPositionRect;
  SDL_Rect flamePositionRect;
  bomb *bombs;
  explosion *explosion;
} stObject;

#endif