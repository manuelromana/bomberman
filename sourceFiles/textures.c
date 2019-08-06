#include "../headerFiles/game.h"

void sdl_load(stGame *game, char *paths[], int arrayLength) {
    for (int i = 0; i < arrayLength; i++) {
        game->texture[i]->path = paths[i];
        game->texture[i]->surface = IMG_Load(paths[i]);
        if (!game->texture[i]->surface) {
            fprintf(stderr, "Erreur au chargement de l'image : %s,%s\n", paths[i], IMG_GetError());
            game_destroy(game);
        } else {
            game->texture[i]->texture = SDL_CreateTextureFromSurface(game->pRenderer, game->texture[i]->surface);
            if (!game->texture[i]->texture) {
                fprintf(stderr, "Erreur au chargement de la texture : %s,%s\n", paths[i], SDL_GetError());
                game_destroy(game);
            }
            SDL_FreeSurface(game->texture[i]->surface);
        }
    }
}

void sdl_destroy();