#ifndef PLAYER_H
#define PLAYER_H

#define PLAYERPOSITIONRECTW 64
#define PLAYERPOSITIONRECTH 128
#define PLAYERCOLISONX 10
#define PLAYERCOLISONY 100
#define PLAYERCOLISONH 32
#define PLAYERCOLISONW 45
#define PLPOSITIONX 64
#define PLPOSITIONY 1

#define PL2POSITIONX 1088
#define PL2POSITIONY 768

typedef struct stPlayer {
  SDL_Rect playerColisionRect;
  SDL_Rect playerPositionRect;

  int playerDirection;
  double playerX, playerY;
  int isDead;
} stPlayer;

#endif