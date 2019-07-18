#include "../headerFiles/header.h"

stGame *game_init_2()
{

    stGame *game = NULL;
    game = malloc(sizeof(stGame));

    game->screenSize.x = 640;
    game->screenSize.y = 480;
    game->pWindow = NULL;
    game->pRenderer = NULL;
    game->police = NULL;
    game->SurfHostname = NULL;
    game->SurfPortname = NULL;
    // game->textPositionRect.x = 60;
    // game->textPositionRect.y = 370;
    //SDL_Texture *texture, *text;

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

    game->police = TTF_OpenFont("assets/font/angelina.TTF", 65);

    // HOSTAME initialisation de l'invation de commande
    /*Écriture du texte Hostname dans la SDL_Surface texte hostname en mode Blended (optimal) */

    SDL_Color noir = {0, 0, 0};
    game->SurfHostname = TTF_RenderText_Blended(game->police, "entrer l'hostname :", noir);

    if (!game->SurfHostname) //condition si pas de surface
    {
        fprintf(stderr, "Erreur au chargement du text : %s\n", IMG_GetError());
        game_destroy_2(game);
        return NULL;
    }
    else
    { //si surface créée on construit la texture
        game->pTextHostname = SDL_CreateTextureFromSurface(game->pRenderer, game->SurfHostname);
        if (!game->pTextHostname)
        {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            game_destroy_2(game);
            return NULL;
        }
        //on free la surface qui était temporaire
        SDL_FreeSurface(game->SurfHostname);
    }

    // PORTNAME initialisation de l'invation de commande
    /*Écriture du texte portname dans la SDL_Surface texte hostname en mode Blended (optimal) */

    game->SurfPortname = TTF_RenderText_Blended(game->police, "entrer le numero de port !", noir);

    if (!game->SurfPortname) //condition si pas de surface
    {
        fprintf(stderr, "Erreur au chargement du text : %s\n", IMG_GetError());
        game_destroy_2(game);
        return NULL;
    }
    else
    { //si surface créée on construit la texture
        game->pTextPortname = SDL_CreateTextureFromSurface(game->pRenderer, game->SurfPortname);
        if (!game->pTextPortname)
        {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            game_destroy_2(game);
            return NULL;
        }
        //on free la surface qui était temporaire
        SDL_FreeSurface(game->SurfPortname);
    }

    SDL_StartTextInput();

    return game;
}

void game_draw_hostname(stGame *game, char *hostname)
{

    SDL_Surface *pInputsurface = NULL;
    SDL_Texture *pInputText = NULL;
    SDL_Rect inputPositionRect;

    SDL_SetRenderDrawColor(game->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(game->pRenderer);

    //render invitation
    game->hostamePositionRect.x = 60;
    game->hostamePositionRect.y = 60;
    game->hostamePositionRect.w = 400;
    game->hostamePositionRect.h = 100;
    SDL_Rect hostnameInvite = {game->hostamePositionRect.x, game->hostamePositionRect.y, game->hostamePositionRect.w, game->hostamePositionRect.h};
    SDL_RenderCopy(game->pRenderer, game->pTextHostname, NULL, &hostnameInvite);

    // render input
    // surface
    SDL_Color noir = {0, 0, 0};
    if (*hostname != '\0')
    {
        pInputsurface = TTF_RenderText_Blended(game->police, hostname, noir);
        if (!pInputsurface)
        {
            fprintf(stderr, "Erreur au chargement du texte : %s\n", IMG_GetError());
            game_destroy_2(game);
            return;
        }
        else
        { //création de la texture si la surface à marché
            pInputText = SDL_CreateTextureFromSurface(game->pRenderer, pInputsurface);
            if (!pInputText)
            {
                fprintf(stderr, "Erreur au chargement de la texture: %s\n", SDL_GetError());
                game_destroy_2(game);
                return;
            }
            SDL_FreeSurface(pInputsurface);
        }
        int width = my_strlen(hostname);

        //déclaration de la position
        inputPositionRect.x = 60;
        inputPositionRect.y = 130;
        inputPositionRect.w = 15 * width;
        inputPositionRect.h = 50;
        //positionnner l'input dans la fenêtre
        SDL_Rect destinationInput = {inputPositionRect.x, inputPositionRect.y, inputPositionRect.w, inputPositionRect.h};
        SDL_RenderCopy(game->pRenderer, pInputText, NULL, &destinationInput);
    }

    SDL_RenderPresent(game->pRenderer);
}

void game_draw_port(stGame *game, char *port)
{

    SDL_Surface *pInputsurface = NULL;
    SDL_Texture *pInputText = NULL;
    SDL_Rect inputPositionRect;

    SDL_SetRenderDrawColor(game->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(game->pRenderer);

    //render invitation port
    game->portPositionRect.x = 60;
    game->portPositionRect.y = 60;
    game->portPositionRect.w = 400;
    game->portPositionRect.h = 100;
    SDL_Rect portInvite = {game->portPositionRect.x, game->portPositionRect.y, game->portPositionRect.w, game->portPositionRect.h};
    SDL_RenderCopy(game->pRenderer, game->pTextPortname, NULL, &portInvite);

    // render input
    // surface
    SDL_Color noir = {0, 0, 0};
    if (*port != '\0')
    {
        pInputsurface = TTF_RenderText_Blended(game->police, port, noir);
        if (!pInputsurface)
        {
            fprintf(stderr, "Erreur au chargement du texte : %s\n", IMG_GetError());
            game_destroy_2(game);
            return;
        }
        else
        { //création de la texture si la surface à marché
            pInputText = SDL_CreateTextureFromSurface(game->pRenderer, pInputsurface);
            if (!pInputText)
            {
                fprintf(stderr, "Erreur au chargement de la texture: %s\n", SDL_GetError());
                game_destroy_2(game);
                return;
            }
            SDL_FreeSurface(pInputsurface);
        }
        int width = my_strlen(port);

        //déclaration de la position
        inputPositionRect.x = 60;
        inputPositionRect.y = 130;
        inputPositionRect.w = 15 * width;
        inputPositionRect.h = 50;
        //positionnner l'input dans la fenêtre
        SDL_Rect destinationInput = {inputPositionRect.x, inputPositionRect.y, inputPositionRect.w, inputPositionRect.h};
        SDL_RenderCopy(game->pRenderer, pInputText, NULL, &destinationInput);
    }

    SDL_RenderPresent(game->pRenderer);
}

void game_destroy_2(stGame *game)
{
    if (game)
    {
        TTF_CloseFont(game->police);
        SDL_StopTextInput();
        SDL_DestroyWindow(game->pWindow);
        SDL_DestroyRenderer(game->pRenderer);

        free(game);
    }
    // Clean up
    SDL_Quit();
}