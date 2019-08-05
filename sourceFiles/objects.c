#include "../headerFiles/game.h"
#include "../headerFiles/map.h"

void bomb_init(stGame *game) {
  SDL_Surface *surfaceBombe = IMG_Load("assets/Bomb/Bomb_f03.png");
  if (!surfaceBombe) {
    fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
    game_destroy(game);
  } else {
    game->bomb->pTexBomb =
        SDL_CreateTextureFromSurface(game->pRenderer, surfaceBombe);
        SDL_FreeSurface(surfaceBombe);
    if (!game->bomb->pTexBomb) {
      fprintf(stderr, "Erreur au chargement de la texture ?? %s\n",
              SDL_GetError());
      game_destroy(game);
    }
  }
  game->bomb->bombs = NULL;
}

void draw_bomb(stGame *game) {
  bomb *CurrentBomb = game->bomb->bombs;
  while (CurrentBomb != NULL) {
    game->bomb->bombPositionRect.x = CurrentBomb->x;
    game->bomb->bombPositionRect.y = CurrentBomb->y;
    game->bomb->bombPositionRect.w = PLAYERPOSITIONRECTW;
    game->bomb->bombPositionRect.h = PLAYERPOSITIONRECTW;
    SDL_RenderCopy(game->pRenderer, game->bomb->pTexBomb, NULL,
                   &game->bomb->bombPositionRect);
    CurrentBomb = CurrentBomb->next;
  }
}

void create_bomb(stGame *game) {
  bomb *newBomb;
  newBomb = (bomb *)malloc(sizeof(bomb));
  if (newBomb == NULL) {
    exit(EXIT_FAILURE);
  }
  if (position_bomb(game, newBomb)) {
    newBomb->startTime = SDL_GetTicks();
    add_NewBomb(game, newBomb);
  } else {
    free(newBomb);
  }
}

void add_NewBomb(stGame *game, bomb *newBomb) {
  newBomb->next = NULL;
  newBomb->prev = NULL;
  if (game->bomb->bombs == NULL) {
    game->bomb->bombs = newBomb;
    return;
  }
  bomb *CurrentBomb = game->bomb->bombs;

  while (CurrentBomb->next != NULL) {
    CurrentBomb = CurrentBomb->next;
  }
  CurrentBomb->next = newBomb;
  newBomb->prev = CurrentBomb;
}

void destroy_bomb(stGame *game, bomb *endBomb) {
  game->bomb->bombs = endBomb->next;
  if (game->bomb->bombs != NULL) game->bomb->bombs->prev = NULL;
  game->map->map[endBomb->tileY][endBomb->tileX] = 0;
  free(endBomb);
}

int position_bomb(stGame *game, bomb *newBomb) {
  newBomb->tileX = game->player->playerX + game->player->playerColisionRect.x;
  newBomb->tileX += game->player->playerColisionRect.w / 2;
  newBomb->tileX /= 64;
  newBomb->x = newBomb->tileX * 64;

  newBomb->tileY = game->player->playerY + game->player->playerColisionRect.y;
  newBomb->tileY += game->player->playerColisionRect.h / 2;
  newBomb->tileY /= 64;
  newBomb->y = newBomb->tileY * 64;

  if (game->map->map[newBomb->tileY][newBomb->tileX] == 0) {
    game->map->map[newBomb->tileY][newBomb->tileX] = 2;
    return 1;
  } else {
    return 0;
  }
}