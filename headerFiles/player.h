#ifndef PLAYER_H
#define PLAYER_H

#define PLAYERPOSITIONRECTW 64
#define PLAYERPOSITIONRECTH 128
#define PLAYERCOLISONX 10
#define PLAYERCOLISONY 100
#define PLAYERCOLISONH 32
#define PLAYERCOLISONW 45
#define PLPOSITIONX ( SCREENSIZEX / 2 )
#define PLPOSITIONY ( SCREENSIZEY / 2 )

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