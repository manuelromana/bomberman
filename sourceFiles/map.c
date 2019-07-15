#include "../headerFiles/header.h"

void draw_map(stGame* game) {

    if (SDL_QueryTexture(game->pTexWall, NULL, NULL, &game->wallPosition.w, &game->wallPosition.h) != 0) {
        fprintf(stderr, "Impossible d'afficher la texture");
    }

for (int y = 0;  y < HAUTEURMAP; y++ ) {
    for (int x = 0; x < LARGEURMAP; x++) {
        if (game->map[y][x] == 1) {
            game->wallPosition.x = x*64;
            game->wallPosition.y = y*64;
            SDL_RenderCopy(game->pRenderer, game->pTexWall, NULL, &game->wallPosition);
        }
    }
        
    }
}

void load_map(stGame* game) {

SDL_Surface* SolidBlock = IMG_Load("assets/Blocks/SolidBlock.png");
    if (!SolidBlock) {
        fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
        game_destroy(game);
        return NULL;
    } else {
        game->pTexWall = SDL_CreateTextureFromSurface(game->pRenderer, SolidBlock);
        if (!game->pTexWall) {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            game_destroy(game);
            return NULL;
        }
    }
    
}