#include "../../headerFiles/game/game.h"

// 0 = Empty; 1 = Wall; 2 = Bomb; 3 = ExploWall
int map[HAUTEURMAP][LARGEURMAP] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 1},
    {1, 0, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 0, 1},
    {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
    {1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1},
    {1, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1},
    {1, 3, 1, 3, 1, 3, 1, 3, 1, 0, 1, 3, 1, 3, 1, 3, 1, 3, 1},
    {1, 3, 3, 3, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 3, 3, 3, 1},
    {1, 3, 1, 3, 1, 3, 1, 3, 1, 0, 1, 3, 1, 3, 1, 3, 1, 3, 1},
    {1, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1},
    {1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1},
    {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
    {1, 0, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 0, 1},
    {1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void map_init(stGame* game) {
  for (int x = 0; x < LARGEURMAP; x++) {
    for (int y = 0; y < HAUTEURMAP; y++) {
      game->map->map[y][x] = map[y][x];
    }
  }

  game->map->wallPosition.w = WALLPOSITIONW;
  game->map->wallPosition.h = WALLPOSITIONH;
  game->map->exploWallPosition.w = WALLPOSITIONW;
  game->map->exploWallPosition.h = WALLPOSITIONW;
}

void draw_map(stGame* game) {
  if (SDL_QueryTexture(game->texture[3]->texture, NULL, NULL,
                       &game->map->wallPosition.w,
                       &game->map->wallPosition.h) != 0) {
    fprintf(stderr, "Impossible d'afficher la texture !");
  }
  if (SDL_QueryTexture(game->texture[6]->texture, NULL, NULL,
                       &game->map->exploWallPosition.w,
                       &game->map->exploWallPosition.h) != 0) {
    fprintf(stderr, "Impossible d'afficher la texture !");
  }
  for (int y = 0; y < HAUTEURMAP; y++) {
    for (int x = 0; x < LARGEURMAP; x++) {
      if (game->map->map[y][x] == 1) {
        game->map->wallPosition.x = x * WALLPOSITIONW;
        game->map->wallPosition.y = y * WALLPOSITIONW;
        SDL_RenderCopy(game->pRenderer, game->texture[3]->texture, NULL,
                       &game->map->wallPosition);
      }
      if (game->map->map[y][x] == 3) {
        game->map->exploWallPosition.x = x * WALLPOSITIONW;
        game->map->exploWallPosition.y = y * WALLPOSITIONW;
        SDL_RenderCopy(game->pRenderer, game->texture[6]->texture, NULL,
                       &game->map->exploWallPosition);
      }
    }
  }
}