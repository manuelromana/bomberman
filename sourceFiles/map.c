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
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

stMap* map_init(stGame *game) {
    stMap* map = {0};
    map = malloc(sizeof (map));

    for (int x = 0; x < LARGEURMAP; x++) {
        for (int y = 0; y < HAUTEURMAP; y++) {
            map->map[y][x] = map->map[y][x];
        }
    }
    
    map->bombPositionRect.x = 900;
    map->bombPositionRect.y = 900;
    map->wallPosition.x = 0;
    map->wallPosition.y = 0;
    map->wallPosition.w = 64;
    map->wallPosition.h = 128;

    SDL_Surface* surfaceBombe = IMG_Load("assets/Bomb/Bomb_f03.png");
    if (!surfaceBombe) {
        fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
        map_destroy(map);
        return NULL;
    } else {
        map->pTexBomb = SDL_CreateTextureFromSurface(game->pRenderer, surfaceBombe);
        if (!map->pTexBomb) {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            map_destroy(map);
            return NULL;
        }
    }
}

void draw_map(stMap* map,stGame *game) {

    if (SDL_QueryTexture(map->pTexWall, NULL, NULL, &map->wallPosition.w, &map->wallPosition.h) != 0) {
        fprintf(stderr, "Impossible d'afficher la texture");
    }

    for (int y = 0;  y < HAUTEURMAP; y++ ) {
        for (int x = 0; x < LARGEURMAP; x++) {
            if (map->map[y][x] == 1) {
                map->wallPosition.x = x*64;
                map->wallPosition.y = y*64;
                SDL_RenderCopy(game->pRenderer, map->pTexWall, NULL, &map->wallPosition);
            }
        }
    }
}

void load_map(stMap* map, stGame* game) {
    SDL_Surface* SolidBlock = IMG_Load("assets/Blocks/SolidBlock.png");

    if (!SolidBlock) {
        fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
        map_destroy(map);
    } else {
       map->pTexWall = SDL_CreateTextureFromSurface(game->pRenderer, SolidBlock);
        if (!map->pTexWall) {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            map_destroy(map);
        }
    }
}

void map_destroy(stMap* map) {
    if(map) {
        SDL_DestroyTexture(map->pTexBomb);
        SDL_DestroyTexture(map->pTexWall);
        free(map);
    }
}