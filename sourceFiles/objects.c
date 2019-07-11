#include "../headerFiles/header.h"

void draw_bomb(stGame* game) {
    game->map->bombPositionRect.x = (game->p1->pPos1->playerPositionRect.x) + 10;
    game->map->bombPositionRect.y =  (game->p1->pPos1->playerPositionRect.y) + 80;
}
/* 
void load_surface(SDL_Surface* surface, stGame *game) {
    SDL_Surface* SolidBlock = IMG_Load("assets/Blocks/SolidBlock.png");
    
    if (!surface) {
        fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
        game_destroy(game);
    } else {
        game->map->pTexWall = SDL_CreateTextureFromSurface(game->pRenderer, SolidBlock);
        if (!game->map->pTexWall) {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            game_destroy(game);
        }
    }
}
*/