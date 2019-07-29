#include "../headerFiles/header.h"

st_game *game_init_test()
{
    st_game *game = {0};
    game = malloc(sizeof(st_game));

    for (int i = 0; i < 10; i++)
    {
        game->images[i] = NULL;
        game->images[i] = malloc(sizeof(st_img *));
    }

    //Contrôler que le sdl s'initialise correctement
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "impossible d'initialiser la sdl : %s\n", SDL_GetError());
        game_destroy(game);
        return NULL;
    }

    //initialiser la fenêtre
    game->pWindow = SDL_CreateWindow(
        "Bomberman",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREENSIZEX,
        SCREENSIZEY,
        SDL_WINDOW_OPENGL);

    if (game->pWindow)
    {
        game->pRenderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);

        if (!game->pRenderer)
        {
            printf("Could not create renderer: %s\n", SDL_GetError());
            game_destroy(game);
            return NULL;
        }
    }
    else
    {
        printf("Could not create window: %s\n", SDL_GetError());
        game_destroy(game);
        return NULL;
    }

    //charger les images
    char *paths[] = {"assets/bomberman.png"};

    for (int i = 0; i < 1; i++)
    {
        game->images[i]->path = paths[i];

        game->images[i]->surface = IMG_Load(paths[i]);
        if (!game->images[i]->surface)
        {
            fprintf(stderr, "Erreur au chargement de l'image : %s,%s\n", paths[i], IMG_GetError());
            game_destroy(game);
            return NULL;
        }
        else
        {
            game->images[i]->texture = SDL_CreateTextureFromSurface(game->pRenderer, game->images[i]->surface);
            if (!game->images[i]->texture)
            {
                fprintf(stderr, "Erreur au chargement de la texture : %s,%s\n", paths[i], SDL_GetError());
                game_destroy(game);
                return NULL;
            }
            SDL_FreeSurface(game->images[i]->surface);
        }
    }

    return game;
}

void draw_game_test(st_game *game)
{
    SDL_SetRenderDrawColor(game->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(game->pRenderer);

    game->images[0]->rectangle.y = 100;
    game->images[0]->rectangle.x = 100;
    game->images[0]->rectangle.w = 200;
    game->images[0]->rectangle.h = 200;

    SDL_Rect test = {game->images[0]->rectangle.x, game->images[0]->rectangle.y, game->images[0]->rectangle.w, game->images[0]->rectangle.h};
    SDL_RenderCopy(game->pRenderer, game->images[0]->texture, NULL, &test);
    SDL_RenderPresent(game->pRenderer);
}

void game_destroy(st_game *game)
{
    if (game)
    {
        if (game->pWindow)
        {
            SDL_DestroyWindow(game->pWindow);
        }
        if (game->pRenderer)
        {
            SDL_DestroyRenderer(game->pRenderer);
        }
        free(game);
    }
    SDL_Quit;
}