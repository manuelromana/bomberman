#include "../headerFiles/game.h"
#include "../headerFiles/map.h"
#include "../headerFiles/player.h"

void player_init(stGame* game) {
  game->players[0].isDead = 0;
  game->players[0].playerPositionRect.x = PLPOSITIONX;
  game->players[0].playerPositionRect.y = PLPOSITIONY;
  game->players[0].playerPositionRect.w = PLAYERPOSITIONRECTW;
  game->players[0].playerPositionRect.h = PLAYERPOSITIONRECTH;
  game->players[0].playerColisionRect.x = PLAYERCOLISONX;
  game->players[0].playerColisionRect.y = PLAYERCOLISONY;
  game->players[0].playerColisionRect.h = PLAYERCOLISONH;
  game->players[0].playerColisionRect.w = PLAYERCOLISONW;
  game->players[0].playerX = game->players[0].playerPositionRect.x;
  game->players[0].playerY = game->players[0].playerPositionRect.y;

  game->players[1].isDead = 0;
  game->players[1].playerPositionRect.x = PL2POSITIONX;
  game->players[1].playerPositionRect.y = PL2POSITIONY;
  game->players[1].playerPositionRect.w = PLAYERPOSITIONRECTW;
  game->players[1].playerPositionRect.h = PLAYERPOSITIONRECTH;
  game->players[1].playerColisionRect.x = PLAYERCOLISONX;
  game->players[1].playerColisionRect.y = PLAYERCOLISONY;
  game->players[1].playerColisionRect.h = PLAYERCOLISONH;
  game->players[1].playerColisionRect.w = PLAYERCOLISONW;
  game->players[1].playerX = game->players[1].playerPositionRect.x;
  game->players[1].playerY = game->players[1].playerPositionRect.y;
}
void character_move(enum enDirection direction, stGame* game,
                    stPlayer* player) {
  double x = player->playerColisionRect.x + player->playerX;
  double y = player->playerColisionRect.y + player->playerY;
  int h = player->playerColisionRect.h;
  int w = player->playerColisionRect.w;
  int xInMap, yInMap, yInMap2, xInMap2;
  switch (direction) {
    case RIGHT:
      xInMap = (x + w + SPEED * game->delta) / 64;
      yInMap = y / 64;
      yInMap2 = (y + h) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap, yInMap2) == 0) {
        player->playerX += SPEED * game->delta;
      } else {
        player->playerX = xInMap * 64 - 1 - w - player->playerColisionRect.x;
      }
      player->playerDirection = 0;
      break;
    case LEFT:
      xInMap = (x - SPEED * game->delta) / 64;
      yInMap = y / 64;
      yInMap2 = (y + h) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap, yInMap2) == 0) {
        player->playerX -= SPEED * game->delta;
      } else {
        player->playerX = xInMap * 64 + 65 - player->playerColisionRect.x;
      }
      player->playerDirection = 1;
      break;
    case UP:
      xInMap = x / 64;
      yInMap = (y - SPEED * game->delta) / 64;
      xInMap2 = (x + w) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap2, yInMap) == 0) {
        player->playerY -= SPEED * game->delta;
      } else {
        player->playerY = yInMap * 64 + 65 - player->playerColisionRect.y;
      }
      player->playerDirection = 2;
      break;
    case DOWN:
      xInMap = x / 64;
      yInMap = (y + h + SPEED * game->delta) / 64;
      xInMap2 = (x + w) / 64;
      if (check_collision(game, xInMap, yInMap) == 0 &&
          check_collision(game, xInMap2, yInMap) == 0) {
        player->playerY += SPEED * game->delta;
      } else {
        player->playerY = yInMap * 64 - 1 - h - player->playerColisionRect.y;
      }
      player->playerDirection = 3;
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

void character_sort(int nPlayer, stPlayer* player) {
  int i, j;
  stPlayer t;
  for (i = 0; i < nPlayer; i++) {
    for (j = i + 1; j < nPlayer; j++) {
      if (player[j].playerY < player[i].playerY) {
        t = player[i];
        player[i] = player[j];
        player[j] = t;
      }
    }
  }
}