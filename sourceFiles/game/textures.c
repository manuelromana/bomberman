#include "../../headerFiles/game/game.h"

void textures_init(stGame *game) {
  for (int i = 0; i < TEXTURESSIZE; i++) {
    game->texture[i] = NULL;
    game->texture[i] = malloc(sizeof(stTexture *));
  }

  char *paths[] = {PATHPLFR, PATHPLBCK, PATHPLSIDE,
                   PATHWALL, PATHBOMB,  PATHFLAME};
  int arrayLength = LEN(paths);

  sdl_load(game, paths, arrayLength);
}

void sdl_load(stGame *game, char *paths[], int arrayLength) {
  for (int i = 0; i < arrayLength; i++) {
    game->texture[i]->path = paths[i];
    game->texture[i]->surface = IMG_Load(paths[i]);
    if (!game->texture[i]->surface) {
      fprintf(stderr, "Erreur au chargement de l'image : %s,%s\n", paths[i],
              IMG_GetError());
      game_destroy(game);
    } else {
      game->texture[i]->texture = SDL_CreateTextureFromSurface(
          game->pRenderer, game->texture[i]->surface);
      if (!game->texture[i]->texture) {
        fprintf(stderr, "Erreur au chargement de la texture : %s,%s\n",
                paths[i], SDL_GetError());
        game_destroy(game);
      }
      SDL_FreeSurface(game->texture[i]->surface);
    }
  }
}

void textures_destroy(stGame *game) {
  for (int i = 0; i < TEXTURESSIZE; i++) {
    SDL_DestroyTexture(game->texture[i]->texture);
    free(game->texture[i]);
  }
}