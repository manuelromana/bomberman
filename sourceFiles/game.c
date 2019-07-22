#include "../headerFiles/header.h"

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

stGame* game_init() {
    stGame* game = {0};
    game = malloc(sizeof (stGame));

    for (int x = 0; x < LARGEURMAP; x++) {
        for (int y = 0; y < HAUTEURMAP; y++) {
            game->map[y][x] = map[y][x];
        }
    }

    game->screenSize.x = SCREENSIZEX;
    game->screenSize.y = SCREENSIZEY;
    game->playerPositionRect.x = PLPOSITIONX;
    game->playerPositionRect.y = PLPOSITIONY;
    game->playerPositionRect.w = PLAYERPOSITIONRECTW;
    game->playerPositionRect.h = PLAYERPOSITIONRECTH;
    game->bombPositionRect.x = BOMBPOSITION;
    game->bombPositionRect.y = BOMBPOSITION;
    game->wallPosition.w = WALLPOSITION;
    game->wallPosition.h = WALLPOSITION;

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

    SDL_Surface* frontBomberman = IMG_Load("assets/Bomberman/Front/Bman_F_f00.png");
    SDL_Surface* backBomberman = IMG_Load("assets/Bomberman/Back/Bman_B_f00.png");
    SDL_Surface* RightSideBomberman = IMG_Load("assets/Bomberman/Side/Bman_F_f00.png");
    SDL_Surface* LeftSideBomberman = IMG_Load("assets/Bomberman/Side/Bman_F_f00.png");
   
    if (!frontBomberman || !backBomberman) {
        fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
        game_destroy(game);
        return NULL;
    } else {
        game->pTexPlayerFront = SDL_CreateTextureFromSurface(game->pRenderer, frontBomberman);
        game->pTexPlayerBack = SDL_CreateTextureFromSurface(game->pRenderer, backBomberman);
        game->pTexPlayerRight = SDL_CreateTextureFromSurface(game->pRenderer, RightSideBomberman);
        game->pTexPlayerLeft = SDL_CreateTextureFromSurface(game->pRenderer, LeftSideBomberman);
        if (!game->pTexPlayerFront || !game->pTexPlayerBack) {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            game_destroy(game);
            return NULL;
        }
    }

    SDL_Surface* surfaceBombe = IMG_Load("assets/Bomb/Bomb_f03.png");
    if (!surfaceBombe) {
        fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
        game_destroy(game);
        return NULL;
    } else {
        game->pTexBomb = SDL_CreateTextureFromSurface(game->pRenderer, surfaceBombe);
        if (!game->pTexBomb) {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            game_destroy(game);
            return NULL;
        }
    }
    return game;
}

void game_draw(stGame* game) {
    SDL_SetRenderDrawColor(game->pRenderer, 10, 50, 10, 255);
    SDL_RenderClear(game->pRenderer);
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
    SDL_Rect destinationPlayer = {
        game->playerPositionRect.x,
        game->playerPositionRect.y,
        game->playerPositionRect.w,
        game->playerPositionRect.h
    };

    load_map(game);
    draw_map(game);

    switch (game->playerDirection) {
        case 0 :
            SDL_RenderCopy(game->pRenderer, game->pTexPlayerRight, NULL, &destinationPlayer); 
            break;
        case 1 :
            SDL_RenderCopyEx(game->pRenderer,game->pTexPlayerLeft, NULL, &destinationPlayer, 0, NULL, flip);
            break;
        case 2 :
            SDL_RenderCopy(game->pRenderer, game->pTexPlayerBack, NULL, &destinationPlayer); 
            break;
        case 3 :
            SDL_RenderCopy(game->pRenderer, game->pTexPlayerFront, NULL, &destinationPlayer); 
            break;
    }


    SDL_Rect destinationBombe = { game->bombPositionRect.x, game->bombPositionRect.y,48,48};
    SDL_RenderCopy(game->pRenderer, game->pTexBomb, NULL, &destinationBombe);
    
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
        SDL_DestroyTexture(game->pTexPlayerFront);
        SDL_DestroyTexture(game->pTexPlayerBack);
        SDL_DestroyTexture(game->pTexBomb);
        free(game);
    }

    SDL_Quit();
}