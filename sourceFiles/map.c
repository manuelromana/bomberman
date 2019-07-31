#include "../headerFiles/game.h"

int map[HAUTEURMAP][LARGEURMAP] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

stGame* map_init(stGame* game) {
  for (int x = 0; x < LARGEURMAP; x++) {
    for (int y = 0; y < HAUTEURMAP; y++) {
      game->map->map[y][x] = map[y][x];
    }
  }

  game->map->bombPositionRect.x = 900;
  game->map->bombPositionRect.y = 900;
  game->map->wallPosition.x = 0;
  game->map->wallPosition.y = 0;
  game->map->wallPosition.w = 64;
  game->map->wallPosition.h = 128;

  return game;
}

void draw_map(stGame* game) {
  if (SDL_QueryTexture(game->map->pTexWall, NULL, NULL,
                       &game->map->wallPosition.w,
                       &game->map->wallPosition.h) != 0) {
    fprintf(stderr, "Impossible d'afficher la texture !");
  }
  for (int y = 0; y < HAUTEURMAP; y++) {
    for (int x = 0; x < LARGEURMAP; x++) {
      if (game->map->map[y][x] == 1) {
        game->map->wallPosition.x = x * 64;
        game->map->wallPosition.y = y * 64;
        SDL_RenderCopy(game->pRenderer, game->map->pTexWall, NULL,
                       &game->map->wallPosition);
      }
    }
  }
}

void load_map(stGame* game) {
  SDL_Surface* SolidBlock = IMG_Load("assets/Blocks/SolidBlock.png");

  if (!SolidBlock) {
    fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
    game_destroy(game);
  } else {
    game->map->pTexWall =
        SDL_CreateTextureFromSurface(game->pRenderer, SolidBlock);
    if (!game->map->pTexWall) {
      fprintf(stderr, "Erreur au chargement de la texture : %s\n",
              SDL_GetError());
      game_destroy(game);
    }
  }
}