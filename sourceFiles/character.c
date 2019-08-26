#include "../headerFiles/game.h"
#include "../headerFiles/map.h"
#include "../headerFiles/player.h"

void player_init(stGame* game) {
  game->player->playerPositionRect.x = PLPOSITIONX;
  game->player->playerPositionRect.y = PLPOSITIONY;
  game->player->playerPositionRect.w = PLAYERPOSITIONRECTW;
  game->player->playerPositionRect.h = PLAYERPOSITIONRECTH;
  game->player->playerColisionRect.x = PLAYERCOLISONX;
  game->player->playerColisionRect.y = PLAYERCOLISONY;
  game->player->playerColisionRect.h = PLAYERCOLISONH;
  game->player->playerColisionRect.w = PLAYERCOLISONW;
  game->player->playerX = game->player->playerPositionRect.x;
  game->player->playerY = game->player->playerPositionRect.y;
}

void character_move(SDL_Keycode direction, stGame* game) {
  double x = game->player->playerColisionRect.x + game->player->playerX;
  double y = game->player->playerColisionRect.y + game->player->playerY;
  int h = game->player->playerColisionRect.h;
  int w = game->player->playerColisionRect.w;
  int xInMap, yInMap, yInMap2, xInMap2;
  switch (direction) {
    case SDLK_RIGHT:
      xInMap = (x + w + SPEED * game->delta) / 64;
      yInMap = y / 64;
      yInMap2 = (y + h) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap, yInMap2) == 0) {
        game->player->playerX += SPEED * game->delta;
      } else {
        game->player->playerX =
            xInMap * 64 - 1 - w - game->player->playerColisionRect.x;
      }
      game->player->playerDirection = 0;
      break;
    case SDLK_LEFT:
      xInMap = (x - SPEED * game->delta) / 64;
      yInMap = y / 64;
      yInMap2 = (y + h) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap, yInMap2) == 0) {
        game->player->playerX -= SPEED * game->delta;
      } else {
        game->player->playerX =
            xInMap * 64 + 65 - game->player->playerColisionRect.x;
      }
      game->player->playerDirection = 1;
      break;
    case SDLK_UP:
      xInMap = x / 64;
      yInMap = (y - SPEED * game->delta) / 64;
      xInMap2 = (x + w) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap2, yInMap) == 0) {
        game->player->playerY -= SPEED * game->delta;
      } else {
        game->player->playerY =
            yInMap * 64 + 65 - game->player->playerColisionRect.y;
      }
      game->player->playerDirection = 2;
      break;
    case SDLK_DOWN:
      xInMap = x / 64;
      yInMap = (y + h + SPEED * game->delta) / 64;
      xInMap2 = (x + w) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap2, yInMap) == 0) {
        game->player->playerY += SPEED * game->delta;
      } else {
        game->player->playerY =
            yInMap * 64 - 1 - h - game->player->playerColisionRect.y;
      }
      game->player->playerDirection = 3;
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