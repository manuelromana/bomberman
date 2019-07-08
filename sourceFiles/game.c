#include "../headerFiles/header.h"

stGame* game_init() {

    stGame* game = NULL;
    game = malloc(sizeof (stGame));

    game->screenSize.x = 1216;
    game->screenSize.y = 960;
    game->pWindow = NULL;
    game->pRenderer = NULL;
    game->pTexPlayerFront = NULL;
    game->pTexPlayerBack = NULL;
    game->pTexBomb = NULL;
    game->playerPositionRect.x = game->screenSize.x / 2;
    game->playerPositionRect.y = game->screenSize.y / 2;
    game->playerPositionRect.w = 64;
    game->playerPositionRect.h = 128;
    game->bombPositionRect.x = 900;
    game->bombPositionRect.y = 900;
    game->playerDirection = 0;

    game->pWindow = SDL_CreateWindow(
        "Bomberman",                  // window title
        SDL_WINDOWPOS_UNDEFINED,      // initial x position
        SDL_WINDOWPOS_UNDEFINED,      // initial y position
        game->screenSize.x,           // width, in pixels
        game->screenSize.y,           // height, in pixels
        SDL_WINDOW_OPENGL             // flags - see below
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
        // SDL_FreeSurface(frontBomberman);
        // SDL_FreeSurface(backBomberman);
    }

    SDL_Surface* surfaceBombe = IMG_Load("assets/Bomb/Bomb_f01.png");
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
        // SDL_FreeSurface(surfaceBombe);
    }

    return game;
}

void game_draw(stGame* game) {

    SDL_SetRenderDrawColor(game->pRenderer, 0, 100, 0, 255);
    SDL_RenderClear(game->pRenderer);
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
    SDL_Rect destinationPlayer = {
        game->playerPositionRect.x,
        game->playerPositionRect.y,
        game->playerPositionRect.w,
        game->playerPositionRect.h
    };

    switch (game->playerDirection) {
        case 0 :
            SDL_RenderCopy(game->pRenderer, game->pTexPlayerRight, NULL, &destinationPlayer); 
            break;
        case 1 :
            SDL_RenderCopyEx(game->pRenderer,game->pTexPlayerLeft, NULL, &destinationPlayer, 0, NULL, flip);
            //SDL_RenderCopy(game->pRenderer, game->pTexPlayerLeft, NULL, &destinationPlayer); 
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
                case SDLK_SPACE:
                case SDLK_a:
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

        // game->pTexPlayer = SDL_CreateTextureFromSurface(game->pRenderer, frontBomberman);
        // game->pTexPlayer = SDL_CreateTextureFromSurface(game->pRenderer, backBomberman);
        // game->pTexPlayer = SDL_CreateTextureFromSurface(game->pRenderer, sideBomberman);


void character_move(SDL_Keycode direction, stGame *game) {

    switch (direction) {
            case SDLK_RIGHT:
                if(game->playerPositionRect.x < (game->screenSize.x - game->playerPositionRect.w))
                    game->playerPositionRect.x += 10;
                    game->playerDirection = 0;
                break;
            case SDLK_LEFT:
                if(game->playerPositionRect.x > 0)
                    game->playerPositionRect.x -= 10;
                game->playerDirection = 1;
                break;
            case SDLK_UP:
                if(game->playerPositionRect.y > 0)
                    game->playerPositionRect.y -= 10;
                game->playerDirection = 2;
                break;
            case SDLK_DOWN: 
                if(game->playerPositionRect.y < (game->screenSize.y - game->playerPositionRect.h))
                    game->playerPositionRect.y += 10;
                game->playerDirection = 3;
                break;  
            case SDLK_SPACE:
                /*if (!game->pTexBomb) {
                    printf("null");
                    SDL_Surface* surfaceBombe = IMG_Load("assets/Bomb/Bomb_f01.png");
                    game->pTexBomb = SDL_CreateTextureFromSurface(game->pRenderer, surfaceBombe);
                } */
                draw_bomb(game, 1);
                break;
            /*
            case SDLK_a: 
                SDL_DestroyTexture(game->pTexBomb);
                break; 
            */    
    }
}

void draw_bomb(stGame* game, int flagBomb) {

if (flagBomb == 1) {
        game->bombPositionRect.x = (game->playerPositionRect.x) + 10;
        game->bombPositionRect.y =  (game->playerPositionRect.y) + 80;
    }
}


void game_destroy(stGame *game){
    if (game){
        SDL_DestroyWindow(game->pWindow);
        SDL_DestroyRenderer(game->pRenderer);
        SDL_DestroyTexture(game->pTexPlayerFront);
        SDL_DestroyTexture(game->pTexPlayerBack);
        SDL_DestroyTexture(game->pTexBomb);
        free(game);
    }
    // Clean up
    SDL_Quit();
}