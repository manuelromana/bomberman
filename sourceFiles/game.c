#include "../headerFiles/header.h"

stGame* game_init() {

    stGame* game = NULL;
    game = malloc(sizeof (stGame));

    game->screenSize.x = 640;
    game->screenSize.y = 480;
    game->pWindow = NULL;
    game->pRenderer = NULL;
    game->pTexPlayer = NULL;
    game->pTexBomb = NULL;
    game->playerPositionRect.x = game->screenSize.x / 2;
    game->playerPositionRect.y = game->screenSize.y / 2;
    game->playerPositionRect.w = 50;
    game->playerPositionRect.h = 60;

    game->pWindow = SDL_CreateWindow(
        "Bomberman",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        game->screenSize.x,                               // width, in pixels
        game->screenSize.y,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    if(game->pWindow) { 
        game->pRenderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);

        if (!game->pRenderer) {
        // In the case that the renderer could not be made...
        printf("Could not create renderer: %s\n", SDL_GetError());
        return NULL;
        }

    } else {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Surface* surfaceBomberman = IMG_Load("assets/bomberman.png");
    if (!surfaceBomberman) {
        fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
        game_destroy(game);
        return NULL;
    } else {
        game->pTexPlayer = SDL_CreateTextureFromSurface(game->pRenderer, surfaceBomberman);
        if (!game->pTexPlayer) {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            game_destroy(game);
            return NULL;
        }
        SDL_FreeSurface(surfaceBomberman);
    }

    return game;
}

void game_draw(stGame* game) {
    
    SDL_SetRenderDrawColor(game->pRenderer, 100, 0, 0, 255);
    SDL_RenderClear(game->pRenderer);

    SDL_Rect destinationPlayer = {game->playerPositionRect.x, game->playerPositionRect.y, game->playerPositionRect.w, game->playerPositionRect.h};
    SDL_RenderCopy(game->pRenderer, game->pTexPlayer, NULL, &destinationPlayer);
    
    SDL_RenderPresent(game->pRenderer);
}

int game_event(stGame *game) {
    int quit = 0;

    SDL_Event e;

    while(SDL_PollEvent( &e ) != 0)
    {
        //User requests quit
        if(e.type == SDL_QUIT) {
            quit = 1;
        } else if(e.type == SDL_KEYDOWN) {
            //Select surfaces based on key press
            switch(e.key.keysym.sym) {
                case SDLK_RIGHT:
                case SDLK_LEFT:
                case SDLK_UP:
                case SDLK_DOWN:
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

void character_move(SDL_Keycode direction, stGame *game) {
    switch (direction) {
            case SDLK_RIGHT:
                if(game->playerPositionRect.x < (game->screenSize.x - game->playerPositionRect.w))
                    game->playerPositionRect.x += 10;
                break;
            case SDLK_LEFT:
                if(game->playerPositionRect.x > 0)
                    game->playerPositionRect.x -= 10;
                break;
            case SDLK_UP:
                if(game->playerPositionRect.y > 0)
                    game->playerPositionRect.y -= 10;
                break;
            case SDLK_DOWN: 
                if(game->playerPositionRect.y < (game->screenSize.y - game->playerPositionRect.h))
                    game->playerPositionRect.y += 10;
                break;  
    }
}

void game_destroy(stGame *game){
    if (game){
        SDL_DestroyWindow(game->pWindow);
        SDL_DestroyRenderer(game->pRenderer);
        SDL_DestroyTexture(game->pTexPlayer);

        free(game);
    }
    // Clean up
    SDL_Quit();
}
