#include "../../headerFiles/game/gameMulti.h"
#include "../../headerFiles/game/map.h"

void object_init(stGame *game) { game->object->bombs = NULL; }

void draw_bomb(stGame *game) {
  bomb *CurrentBomb = game->object->bombs;
  while (CurrentBomb != NULL) {
    game->object->bombPositionRect.x = CurrentBomb->x;
    game->object->bombPositionRect.y = CurrentBomb->y;
    game->object->bombPositionRect.w = PLAYERPOSITIONRECTW;
    game->object->bombPositionRect.h = PLAYERPOSITIONRECTW;
    SDL_RenderCopy(game->pRenderer, game->texture[4]->texture, NULL,
                   &game->object->bombPositionRect);
    CurrentBomb = CurrentBomb->next;
  }
}

void create_bomb(stGame *game, stPlayer *player) {
  bomb *newBomb;
  newBomb = (bomb *)malloc(sizeof(bomb));
  newBomb->power = BOMB_POWER;
  if (newBomb == NULL) {
    exit(EXIT_FAILURE);
  }
  if (position_bomb(game, newBomb, player)) {
    newBomb->startTime = game->presentTime;
    add_NewBomb(game, newBomb);
  }
  else {
    free(newBomb);
  }
}

void add_NewBomb(stGame *game, bomb *newBomb) {
  newBomb->next = NULL;
  newBomb->prev = NULL;
  if (game->object->bombs == NULL) {
    game->object->bombs = newBomb;
    return;
  }
  bomb *CurrentBomb = game->object->bombs;
  while (CurrentBomb->next != NULL) {
    CurrentBomb = CurrentBomb->next;
  }
  CurrentBomb->next = newBomb;
  newBomb->prev = CurrentBomb;
}

void destroy_bomb(stGame *game, bomb *endBomb) {
  game->object->bombs = endBomb->next;
  if (game->object->bombs != NULL)
    game->object->bombs->prev = NULL;
  game->map->map[endBomb->tileY][endBomb->tileX] = 0;
  free(endBomb);
}

int position_bomb(stGame *game, bomb *newBomb, stPlayer *player) {
  newBomb->tileX = player->playerX + player->playerColisionRect.x;
  newBomb->tileX += player->playerColisionRect.w / 2;
  newBomb->tileX /= CASE_SIZE;
  newBomb->x = newBomb->tileX * CASE_SIZE;
  newBomb->tileY = player->playerY + player->playerColisionRect.y;
  newBomb->tileY += player->playerColisionRect.h / 2;
  newBomb->tileY /= CASE_SIZE;
  newBomb->y = newBomb->tileY * CASE_SIZE;
  if (game->map->map[newBomb->tileY][newBomb->tileX] == 0) {
    game->map->map[newBomb->tileY][newBomb->tileX] = 2;
    return 1;
  }
  else {
    return 0;
  }
}

void draw_explosion(stGame *game) {
  explosion *currentExplosion = game->object->explosion;
  while (currentExplosion != NULL) {
    if (game->presentTime > currentExplosion->startTime) {
      game->object->flamePositionRect.x = currentExplosion->x;
      game->object->flamePositionRect.y = currentExplosion->y;
      game->object->flamePositionRect.w = CASE_SIZE;
      game->object->flamePositionRect.h = CASE_SIZE;
      SDL_RenderCopy(game->pRenderer, game->texture[5]->texture, NULL,
                     &game->object->flamePositionRect);
    }
    currentExplosion = currentExplosion->next;
  }
}

void create_explosion(stGame *game, bomb *bomb) {
  explosion *newExplosion;
  newExplosion = (explosion *)malloc(sizeof(explosion));
  if (newExplosion == NULL) {
    exit(EXIT_FAILURE);
  }
  position_explosion(bomb, newExplosion);
  newExplosion->startTime = game->presentTime;
  add_newExplosion(game, newExplosion);
  create_children_explosion(game, bomb);
}

void create_children_explosion(stGame *game, bomb *bomb) {
  for (int i = 1; i <= bomb->power; i++) {
    int tileY = bomb->tileY - i;
    if (create_child_explosion(game, bomb->tileX, tileY,
                               game->presentTime + EXPLOSION_SPREAD_TIME * i) ==
        -1) {
      break;
    }
  }
  for (int i = 1; i <= bomb->power; i++) {
    int tileY = bomb->tileY + i;
    if (create_child_explosion(game, bomb->tileX, tileY,
                               game->presentTime + EXPLOSION_SPREAD_TIME * i) ==
        -1) {
      break;
    }
  }
  for (int i = 1; i <= bomb->power; i++) {
    int tileX = bomb->tileX - i;
    if (create_child_explosion(game, tileX, bomb->tileY,
                               game->presentTime + EXPLOSION_SPREAD_TIME * i) ==
        -1) {
      break;
    }
  }
  for (int i = 1; i <= bomb->power; i++) {
    int tileX = bomb->tileX + i;
    if (create_child_explosion(game, tileX, bomb->tileY,
                               game->presentTime + EXPLOSION_SPREAD_TIME * i) ==
        -1) {
      break;
    }
  }
}

int create_child_explosion(stGame *game, int tileX, int tileY,
                           unsigned int timer) {
  if (tileY < 0 || tileX < 0 || tileY >= HAUTEURMAP || tileX == LARGEURMAP) {
    return -1;
  }
  if (game->map->map[tileY][tileX] == 1) {
    return -1;
  }
  if (game->map->map[tileY][tileX] == 3) {
    game->map->map[tileY][tileX] = 0;
  }
  explosion *newExplosion;
  newExplosion = (explosion *)malloc(sizeof(explosion));
  if (newExplosion == NULL) {
    exit(EXIT_FAILURE);
  }
  newExplosion->tileX = tileX;
  newExplosion->tileY = tileY;
  newExplosion->x = tileX * CASE_SIZE;
  newExplosion->y = tileY * CASE_SIZE;
  newExplosion->startTime = timer;
  add_newExplosion(game, newExplosion);

  return 0;
}

void add_newExplosion(stGame *game, explosion *newExplosion) {
  newExplosion->next = NULL;
  newExplosion->prev = NULL;
  if (game->object->explosion == NULL) {
    game->object->explosion = newExplosion;
    return;
  }
  explosion *CurrentExplosion = game->object->explosion;
  while (CurrentExplosion->next != NULL) {
    CurrentExplosion = CurrentExplosion->next;
  }
  CurrentExplosion->next = newExplosion;
  newExplosion->prev = CurrentExplosion;
}

void destroy_explosion(stGame *game, explosion *delExplosion) {
  explosion *curentExplosion;
  curentExplosion = game->object->explosion;

  if (delExplosion->prev == NULL) {
    game->object->explosion = delExplosion->next;
    if (game->object->explosion != NULL) {
      game->object->explosion->prev = NULL;
    }
    free(delExplosion);
    return;
  }
  delExplosion->prev->next = delExplosion->next;
  if (delExplosion->next != NULL) {
    delExplosion->next->prev = delExplosion->prev;
  }
  free(delExplosion);
}

int position_explosion(bomb *bomb, explosion *newExplosion) {
  newExplosion->tileX = bomb->tileX;
  newExplosion->tileY = bomb->tileY;
  newExplosion->x = bomb->tileX * CASE_SIZE;
  newExplosion->y = bomb->tileY * CASE_SIZE;
}

void player_flame_colision(stGame *game, stPlayer *player) {
  explosion *currentExplosion;
  int playerTileYLT = (player->playerY + player->playerColisionRect.y) / 64;
  int playerTileXLT = (player->playerX + player->playerColisionRect.x) / 64;
  int playerTileYLB = (player->playerY + player->playerColisionRect.y +
                       player->playerColisionRect.h) /
                      64;
  int playerTileXLB = (player->playerX + player->playerColisionRect.x) / 64;
  int playerTileYRT = (player->playerY + player->playerColisionRect.y) / 64;
  int playerTileXRT = (player->playerX + player->playerColisionRect.x +
                       player->playerColisionRect.w) /
                      64;
  int playerTileYRB = (player->playerY + player->playerColisionRect.y +
                       player->playerColisionRect.h) /
                      64;
  int playerTileXRB = (player->playerX + player->playerColisionRect.x +
                       player->playerColisionRect.w) /
                      64;
  currentExplosion = game->object->explosion;
  while (currentExplosion != NULL) {
    if ((playerTileYLT == currentExplosion->tileY &&
         playerTileXLT == currentExplosion->tileX) ||
        (playerTileYLB == currentExplosion->tileY &&
         playerTileXLB == currentExplosion->tileX) ||
        (playerTileYRT == currentExplosion->tileY &&
         playerTileXRT == currentExplosion->tileX) ||
        (playerTileYRB == currentExplosion->tileY &&
         playerTileXRB == currentExplosion->tileX)) {
      printf("Dead you are little FreeMan\n");
      player->isDead = 1;
      break;
    }
    currentExplosion = currentExplosion->next;
  }
}