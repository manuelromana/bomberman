#include "../headerFiles/game.h"
#include "../headerFiles/map.h"
#include "../headerFiles/player.h"

void player_init(stGame* game) {
  game->player->playerPositionRect.x = game->screenSize.x / 2;
  game->player->playerPositionRect.y = game->screenSize.y / 2;
  game->player->playerPositionRect.w = 64;
  game->player->playerPositionRect.h = 128;
  game->player->playerColisionRect.x = 10;
  game->player->playerColisionRect.y = 100;
  game->player->playerColisionRect.h = 32;
  game->player->playerColisionRect.w = 45;
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
      xInMap = (x + w + SPEED * game->Delta) / 64;
      yInMap = y / 64;
      yInMap2 = (y + h) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap, yInMap2) == 0) {
        game->player->playerX += SPEED * game->Delta;
      } else {
        game->player->playerX =
            xInMap * 64 - 1 - w - game->player->playerColisionRect.x;
      }
      game->player->playerDirection = 0;
      break;
    case SDLK_LEFT:
      xInMap = (x - SPEED * game->Delta) / 64;
      yInMap = y / 64;
      yInMap2 = (y + h) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap, yInMap2) == 0) {
        game->player->playerX -= SPEED * game->Delta;
      } else {
        game->player->playerX =
            xInMap * 64 + 65 - game->player->playerColisionRect.x;
      }
      game->player->playerDirection = 1;
      break;
    case SDLK_UP:
      xInMap = x / 64;
      yInMap = (y - SPEED * game->Delta) / 64;
      xInMap2 = (x + w) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap2, yInMap) == 0) {
        game->player->playerY -= SPEED * game->Delta;
      } else {
        game->player->playerY =
            yInMap * 64 + 65 - game->player->playerColisionRect.y;
      }
      game->player->playerDirection = 2;
      break;
    case SDLK_DOWN:
      xInMap = x / 64;
      yInMap = (y + h + SPEED * game->Delta) / 64;
      xInMap2 = (x + w) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap2, yInMap) == 0) {
        game->player->playerY += SPEED * game->Delta;
      } else {
        game->player->playerY =
            yInMap * 64 - 1 - h - game->player->playerColisionRect.y;
      }
      game->player->playerDirection = 3;
      break;
  }
}

int check_collision(stGame* game, int x, int y) {
  if (game->map->map[y][x] == 1) {
    return 1;
  } else {
    return 0;
  }
}