#include "../headerFiles/game.h"
#include "../headerFiles/map.h"
#include "../headerFiles/player.h"

void player_init(stGame* game) {
  for (int i = 0; i < 2; i++) {
    game->players[i].playerPositionRect.x = PLPOSITIONX;
    game->players[i].playerPositionRect.y = PLPOSITIONY;
    game->players[i].playerPositionRect.w = PLAYERPOSITIONRECTW;
    game->players[i].playerPositionRect.h = PLAYERPOSITIONRECTH;
    game->players[i].playerColisionRect.x = PLAYERCOLISONX;
    game->players[i].playerColisionRect.y = PLAYERCOLISONY;
    game->players[i].playerColisionRect.h = PLAYERCOLISONH;
    game->players[i].playerColisionRect.w = PLAYERCOLISONW;
    game->players[i].playerX = game->players[i].playerPositionRect.x;
    game->players[i].playerY = game->players[i].playerPositionRect.y;
  }
}
void character_move(SDL_Keycode direction, stGame* game) {
  double x = game->players[0].playerColisionRect.x + game->players[0].playerX;
  double y = game->players[0].playerColisionRect.y + game->players[0].playerY;
  int h = game->players[0].playerColisionRect.h;
  int w = game->players[0].playerColisionRect.w;
  int xInMap, yInMap, yInMap2, xInMap2;
  switch (direction) {
    case SDLK_RIGHT:
      xInMap = (x + w + SPEED * game->delta) / 64;
      yInMap = y / 64;
      yInMap2 = (y + h) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap, yInMap2) == 0) {
        game->players[0].playerX += SPEED * game->delta;
      } else {
        game->players[0].playerX =
            xInMap * 64 - 1 - w - game->players[0].playerColisionRect.x;
      }
      game->players[0].playerDirection = 0;
      break;
    case SDLK_LEFT:
      xInMap = (x - SPEED * game->delta) / 64;
      yInMap = y / 64;
      yInMap2 = (y + h) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap, yInMap2) == 0) {
        game->players[0].playerX -= SPEED * game->delta;
      } else {
        game->players[0].playerX =
            xInMap * 64 + 65 - game->players[0].playerColisionRect.x;
      }
      game->players[0].playerDirection = 1;
      break;
    case SDLK_UP:
      xInMap = x / 64;
      yInMap = (y - SPEED * game->delta) / 64;
      xInMap2 = (x + w) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap2, yInMap) == 0) {
        game->players[0].playerY -= SPEED * game->delta;
      } else {
        game->players[0].playerY =
            yInMap * 64 + 65 - game->players[0].playerColisionRect.y;
      }
      game->players[0].playerDirection = 2;
      break;
    case SDLK_DOWN:
      xInMap = x / 64;
      yInMap = (y + h + SPEED * game->delta) / 64;
      xInMap2 = (x + w) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap2, yInMap) == 0) {
        game->players[0].playerY += SPEED * game->delta;
      } else {
        game->players[0].playerY =
            yInMap * 64 - 1 - h - game->players[0].playerColisionRect.y;
      }
      game->players[0].playerDirection = 3;
      break;
  }
}

int check_collision(stGame* game, int x, int y) {
  if (game->map->map[y][x] == 1 || game->map->map[y][x] == 3) {
    return 1;
  } else {
    return 0;
  }
}