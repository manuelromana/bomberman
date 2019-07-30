#include "../headerFiles/game.h"

stGame* game_init() {
    stGame* game = {0};
    game = malloc(sizeof (stGame));

    game->screenSize.x = 1216;
    game->screenSize.y = 960;
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

void game_draw(stGame* game, stPlayer* player, stMap* map) {
    SDL_SetRenderDrawColor(game->pRenderer, 10, 50, 10, 255);
    SDL_RenderClear(game->pRenderer);
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
    SDL_Rect destinationPlayer = {
        player->playerPositionRect.x,
        player->playerPositionRect.y,
        player->playerPositionRect.w,
        player->playerPositionRect.h
    };

    
 draw_map(map, game);
 load_map( map, game);

    switch (player->playerDirection) {
        case 0 :
            SDL_RenderCopy(game->pRenderer, player->pTexPlayerRight, NULL, &destinationPlayer); 
            break;
        case 1 :
            SDL_RenderCopyEx(game->pRenderer, player->pTexPlayerLeft, NULL, &destinationPlayer, 0, NULL, flip);
            break;
        case 2 :
            SDL_RenderCopy(game->pRenderer, player->pTexPlayerBack, NULL, &destinationPlayer); 
            break;
        case 3 :
            SDL_RenderCopy(game->pRenderer, player->pTexPlayerFront, NULL, &destinationPlayer); 
            break;
    }

    SDL_Rect destinationBombe = { map->bombPositionRect.x, map->bombPositionRect.y,48,48};
    SDL_RenderCopy(game->pRenderer, map->pTexBomb, NULL, &destinationBombe);
    
    SDL_RenderPresent(game->pRenderer);
}

int game_event(stGame *game) {
    int quit = 0;
    SDL_Event e;

    while(SDL_PollEvent( &e ) != 0) {
        if(e.type == SDL_QUIT) {
            quit = 1;
        } else if(e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
                case SDLK_RIGHT:
                case SDLK_LEFT:
                case SDLK_UP:
                case SDLK_DOWN:
                case SDLK_SPACE:
                    character_move(e.key.keysym.sym, game);
                    break; 
                case SDLK_ESCAPE :   
                    quit = 1;
                    break; 
            }
        }
    }
    return quit;
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
