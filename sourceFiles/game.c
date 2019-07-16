#include "../headerFiles/game.h"

stGame* game_init() {
    stGame* game = NULL;
    game = malloc(sizeof (stGame));

    game->screenSize.x = 1216;
    game->screenSize.y = 960;
    game->pWindow = NULL;
    game->pRenderer = NULL;
    game->pWindow = SDL_CreateWindow(
        "Bomberman",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        game->screenSize.x,
        game->screenSize.y,
        SDL_WINDOW_OPENGL
    );

    if(game->pWindow) { 
        game->pRenderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);

        if (!game->pRenderer) {
            printf("Could not create renderer: %s\n", SDL_GetError());
            return NULL;
        }

    } else {
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }

    return game;
}

void game_draw(stGame* game) {
    SDL_SetRenderDrawColor(game->pRenderer, 10, 50, 10, 255);
    SDL_RenderClear(game->pRenderer);
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
    SDL_Rect destinationPlayer = {
        game->p1->pPos1->playerPositionRect.x,
        game->p1->pPos1->playerPositionRect.y,
        game->p1->pPos1->playerPositionRect.w,
        game->p1->pPos1->playerPositionRect.h
    };

    load_map(game);
    draw_map(game);

    switch (game->p1->pPos1->playerDirection) {
        case 0 :
            SDL_RenderCopy(game->pRenderer, game->p1->pTexPlayerRight, NULL, &destinationPlayer); 
            break;
        case 1 :
            SDL_RenderCopyEx(game->pRenderer,game->p1->pTexPlayerLeft, NULL, &destinationPlayer, 0, NULL, flip);
            break;
        case 2 :
            SDL_RenderCopy(game->pRenderer, game->p1->pTexPlayerBack, NULL, &destinationPlayer); 
            break;
        case 3 :
            SDL_RenderCopy(game->pRenderer, game->p1->pTexPlayerFront, NULL, &destinationPlayer); 
            break;
    }

    SDL_Rect destinationBombe = { game->map->bombPositionRect.x, game->map->bombPositionRect.y,48,48};
    SDL_RenderCopy(game->pRenderer, game->map->pTexBomb, NULL, &destinationBombe);
    
    SDL_RenderPresent(game->pRenderer);
}

void game_destroy(stGame *game) {
    if (game) {
        SDL_DestroyWindow(game->pWindow);
        SDL_DestroyRenderer(game->pRenderer);

        free(game);
    }
    /*    if(p1){
        SDL_DestroyTexture(p1->pTexPlayerFront);
        SDL_DestroyTexture(p1->pTexPlayerBack);
        SDL_DestroyTexture(p1->pTexPlayerLeft);
        SDL_DestroyTexture(p1->pTexPlayerRight);
        free(p1->pPos1);
        free(p1);
    }
    if(map) {
        SDL_DestroyTexture(map->pTexBomb);
        free(map);
    }*/
    SDL_Quit();
}
