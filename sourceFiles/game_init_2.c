#include "../headerFiles/header.h"

stGame *game_init_2()
{

    stGame *game = NULL;
    game = malloc(sizeof(stGame));

    game->screenSize.x = 640;
    game->screenSize.y = 480;
    game->pWindow = NULL;
    game->pRenderer = NULL;
    SDL_Texture *texture, *text;

    //initialiser la ttf pour les textes
    TTF_Init();
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    //création de la fenêtre
    game->pWindow = SDL_CreateWindow(
        "Bomberman",             // window title
        SDL_WINDOWPOS_UNDEFINED, // initial x position
        SDL_WINDOWPOS_UNDEFINED, // initial y position
        game->screenSize.x,      // width, in pixels
        game->screenSize.y,      // height, in pixels
        SDL_WINDOW_OPENGL        // flags - see below
    );
    //création du renderer
    if (game->pWindow)
    {
        game->pRenderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);

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
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }

    //création de la surface pour charger la police
    SDL_Surface *police = NULL;
    police = TTF_OpenFont("assets/font/angelina.TTF", 65);

    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    SDL_Surface *text = NULL;
    SDL_Color bleu = {69, 14, 237};
    text = TTF_RenderText_Blended(police, "entrer l'hostname !", bleu);

    return game;
}
