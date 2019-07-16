#include "../headerFiles/game.h"

<<<<<<< HEAD
stGame* game_init() {
    stGame* game = NULL;
    game = malloc(sizeof (stGame));
=======
stGame *game_init()
{

    stGame *game = NULL;
    game = malloc(sizeof(stGame));
>>>>>>> 355992318ef981401873e1b6fcbc88b2b2689555

    game->screenSize.x = 1216;
    game->screenSize.y = 960;
    game->pWindow = NULL;
    game->pRenderer = NULL;
    game->pWindow = SDL_CreateWindow(
<<<<<<< HEAD
        "Bomberman",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        game->screenSize.x,
        game->screenSize.y,
        SDL_WINDOW_OPENGL
=======
        "Bomberman",             // window title
        SDL_WINDOWPOS_UNDEFINED, // initial x position
        SDL_WINDOWPOS_UNDEFINED, // initial y position
        game->screenSize.x,      // width, in pixels
        game->screenSize.y,      // height, in pixels
        SDL_WINDOW_OPENGL        // flags - see below
>>>>>>> 355992318ef981401873e1b6fcbc88b2b2689555
    );

    if (game->pWindow)
    {
        game->pRenderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);

<<<<<<< HEAD
        if (!game->pRenderer) {
            printf("Could not create renderer: %s\n", SDL_GetError());
            return NULL;
        }

    } else {
=======
        if (!game->pRenderer)
        {
            // In the case that the renderer could not be made...
            printf("Could not create renderer: %s\n", SDL_GetError());
            return NULL;
        }
    }
    else
    {
        // In the case that the window could not be made...
>>>>>>> 355992318ef981401873e1b6fcbc88b2b2689555
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }

<<<<<<< HEAD
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
=======
    SDL_Surface *surfaceBomberman = IMG_Load("assets/Bomberman/Front/Bman_F_f00.png");
    if (!surfaceBomberman)
    {
        fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
        game_destroy(game);
        return NULL;
    }
    else
    {
        game->pTexPlayer = SDL_CreateTextureFromSurface(game->pRenderer, surfaceBomberman);
        if (!game->pTexPlayer)
        {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            game_destroy(game);
            return NULL;
        }
        SDL_FreeSurface(surfaceBomberman);
        //on peut libérer la surface qui est juste temporaire pour créer la texture
    }

    SDL_Surface *surfaceBombe = IMG_Load("assets/Bomb/Bomb_f01.png");
    if (!surfaceBombe)
    {
        fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
        game_destroy(game);
        return NULL;
    }
    else
    {
        game->pTexBomb = SDL_CreateTextureFromSurface(game->pRenderer, surfaceBombe);
        if (!game->pTexBomb)
        {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            game_destroy(game);
            return NULL;
        }
        SDL_FreeSurface(surfaceBombe);
    }

    return game;
}

void game_draw(stGame *game, int flagBomb)
{

    SDL_SetRenderDrawColor(game->pRenderer, 100, 0, 0, 255);
    SDL_RenderClear(game->pRenderer);

    SDL_Rect destinationPlayer = {game->playerPositionRect.x, game->playerPositionRect.y, game->playerPositionRect.w, game->playerPositionRect.h};
    SDL_RenderCopy(game->pRenderer, game->pTexPlayer, NULL, &destinationPlayer);

    if (flagBomb == 1)
    {
        game->bombPositionRect.x = (game->playerPositionRect.x) + 10;
        game->bombPositionRect.y = (game->playerPositionRect.y) + 80;
    }

    SDL_Rect destinationBombe = {game->bombPositionRect.x, game->bombPositionRect.y, 48, 48};
    SDL_RenderCopy(game->pRenderer, game->pTexBomb, NULL, &destinationBombe);

    SDL_RenderPresent(game->pRenderer);
}

int game_event(stGame *game)
{
    int quit = 0;
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        //User requests quit
        if (e.type == SDL_QUIT)
        {
            quit = 1;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            //Select surfaces based on key press
            switch (e.key.keysym.sym)
            {
            case SDLK_RIGHT:
            case SDLK_LEFT:
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_SPACE:
            case SDLK_a:
                character_move(e.key.keysym.sym, game);
                break;
            case SDLK_ESCAPE:
                quit = 1;
                break;
            }
        }
    }
    return quit;
}

void character_move(SDL_Keycode direction, stGame *game)
{
    switch (direction)
    {
    case SDLK_RIGHT:
        if (game->playerPositionRect.x < (game->screenSize.x - game->playerPositionRect.w))
            game->playerPositionRect.x += 10;
        break;
    case SDLK_LEFT:
        if (game->playerPositionRect.x > 0)
            game->playerPositionRect.x -= 10;
        break;
    case SDLK_UP:
        if (game->playerPositionRect.y > 0)
            game->playerPositionRect.y -= 10;
        break;
    case SDLK_DOWN:
        if (game->playerPositionRect.y < (game->screenSize.y - game->playerPositionRect.h))
            game->playerPositionRect.y += 10;
        break;
    case SDLK_SPACE:
        /*if (!game->pTexBomb) {
                    printf("null");
                    SDL_Surface* surfaceBombe = IMG_Load("assets/Bomb/Bomb_f01.png");
                    game->pTexBomb = SDL_CreateTextureFromSurface(game->pRenderer, surfaceBombe);
                } */
        game_draw(game, 1);
        break;
        /*
            case SDLK_a: 
                SDL_DestroyTexture(game->pTexBomb);
                break; 
            */
    }
}

void game_destroy(stGame *game)
{
    if (game)
    {
>>>>>>> 355992318ef981401873e1b6fcbc88b2b2689555
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
