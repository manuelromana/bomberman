#include "../headerFiles/header.h"

stGame *game_init_2()
{
    stGame *game = NULL;
    game = malloc(sizeof(stGame));

    game->screenSize.x = 640;
    game->screenSize.y = 480;
    game->pWindow = NULL;
    game->pRenderer = NULL;
    game->police1 = NULL;
    game->police2 = NULL;
    game->SurfHostname = NULL;
    game->SurfPortname = NULL;

    TTF_Init();
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    game->pWindow = SDL_CreateWindow(
        "Bomberman",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        game->screenSize.x,
        game->screenSize.y,
        SDL_WINDOW_OPENGL);
    if (game->pWindow)
    {
        game->pRenderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);

        if (!game->pRenderer)
        {
            printf("Could not create renderer: %s\n", SDL_GetError());
            return NULL;
        }
    }
    else
    {
        printf("Could not create window: %s\n", SDL_GetError());

        return NULL;
    }

    game->police1 = TTF_OpenFont("assets/font/Grafiti.ttf", 70);
    game->police2 = TTF_OpenFont("assets/font/Neon.ttf", 45);

    SDL_Color noir = {0, 0, 0};
    game->SurfHostname = TTF_RenderText_Blended(game->police1, "Tapez l'hostname suivi d'entree :", noir);

    if (!game->SurfHostname)
    {
        fprintf(stderr, "Erreur au chargement du text : %s\n", IMG_GetError());
        game_destroy_2(game);
        return NULL;
    }
    else
    {
        game->pTextHostname = SDL_CreateTextureFromSurface(game->pRenderer, game->SurfHostname);

        if (!game->pTextHostname)
        {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            game_destroy_2(game);
            return NULL;
        }

        SDL_FreeSurface(game->SurfHostname);
    }

    game->SurfPortname = TTF_RenderText_Blended(game->police1, "Tapez le numero de port puis entree : ", noir);

    if (!game->SurfPortname)
    {
        fprintf(stderr, "Erreur au chargement du text : %s\n", IMG_GetError());
        game_destroy_2(game);
        return NULL;
    }
    else
    {
        game->pTextPortname = SDL_CreateTextureFromSurface(game->pRenderer, game->SurfPortname);
        if (!game->pTextPortname)
        {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            game_destroy_2(game);
            return NULL;
        }

        SDL_FreeSurface(game->SurfPortname);
    }

    // Welcome page
    /*Écriture du texte de bienvenu dans la SDL_Surface correspondante*/

    game->SurfWelcome = TTF_RenderText_Blended(game->police1, "Bienvenue, tapez une commande pour le server", noir);

    if (!game->SurfWelcome) //condition si pas de surface
    {
        fprintf(stderr, "Erreur au chargement du text : %s\n", IMG_GetError());
        game_destroy_2(game);
        return NULL;
    }
    else
    { //si surface créée on construit la texture
        game->pTextWelcome = SDL_CreateTextureFromSurface(game->pRenderer, game->SurfWelcome);
        if (!game->pTextWelcome)
        {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            game_destroy_2(game);
            return NULL;
        }
        //on free la surface qui était temporaire
        SDL_FreeSurface(game->SurfWelcome);
    }

    SDL_StartTextInput();

    return game;
}

void game_draw_hostname(stGame *game, char *hostname)
{
    SDL_Surface *pInputsurface = NULL;
    SDL_Texture *pInputText = NULL;
    SDL_Rect inputPositionRect;

    //render fenêtre blanche
    SDL_SetRenderDrawColor(game->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(game->pRenderer);

    game->hostamePositionRect.x = 10;
    game->hostamePositionRect.y = 60;
    game->hostamePositionRect.w = 600;
    game->hostamePositionRect.h = 100;
    SDL_Rect hostnameInvite = {game->hostamePositionRect.x, game->hostamePositionRect.y, game->hostamePositionRect.w, game->hostamePositionRect.h};
    SDL_RenderCopy(game->pRenderer, game->pTextHostname, NULL, &hostnameInvite);

    SDL_Color noir = {0, 0, 0};
    if (*hostname != '\0')
    {
        pInputsurface = TTF_RenderText_Blended(game->police2, hostname, noir);
        if (!pInputsurface)
        {
            fprintf(stderr, "Erreur au chargement du texte : %s\n", IMG_GetError());
            game_destroy_2(game);
            return;
        }
        else
        {
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

        inputPositionRect.x = 60;
        inputPositionRect.y = 160;
        inputPositionRect.w = 15 * width;
        inputPositionRect.h = 50;
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

    //render fenêtre blanche
    SDL_SetRenderDrawColor(game->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(game->pRenderer);

    game->portPositionRect.x = 60;
    game->portPositionRect.y = 60;
    game->portPositionRect.w = 550;
    game->portPositionRect.h = 100;
    SDL_Rect portInvite = {game->portPositionRect.x, game->portPositionRect.y, game->portPositionRect.w, game->portPositionRect.h};
    SDL_RenderCopy(game->pRenderer, game->pTextPortname, NULL, &portInvite);

    SDL_Color noir = {0, 0, 0};
    if (*port != '\0')
    {
        pInputsurface = TTF_RenderText_Blended(game->police2, port, noir);
        if (!pInputsurface)
        {
            fprintf(stderr, "Erreur au chargement du texte : %s\n", IMG_GetError());
            game_destroy_2(game);
            return;
        }
        else
        {
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

        inputPositionRect.x = 60;
        inputPositionRect.y = 160;
        inputPositionRect.w = 15 * width;
        inputPositionRect.h = 50;

        SDL_Rect destinationInput = {inputPositionRect.x, inputPositionRect.y, inputPositionRect.w, inputPositionRect.h};
        SDL_RenderCopy(game->pRenderer, pInputText, NULL, &destinationInput);
    }

    SDL_RenderPresent(game->pRenderer);
}

void game_draw_welcome(stGame *game)
{
    //render fenêtre blanche
    SDL_SetRenderDrawColor(game->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(game->pRenderer);

    //render Welcome Message
    game->welcomePositionRect.x = 60;
    game->welcomePositionRect.y = 60;
    game->welcomePositionRect.w = 550;
    game->welcomePositionRect.h = 100;
    SDL_Rect welcomeMess = {game->welcomePositionRect.x, game->welcomePositionRect.y, game->welcomePositionRect.w, game->welcomePositionRect.h};
    SDL_RenderCopy(game->pRenderer, game->pTextWelcome, NULL, &welcomeMess);
    SDL_RenderPresent(game->pRenderer);
}

void game_destroy_2(stGame *game)
{
    if (game)
    {
        TTF_CloseFont(game->police1);
        TTF_CloseFont(game->police2);
        SDL_StopTextInput();
        SDL_DestroyWindow(game->pWindow);
        SDL_DestroyRenderer(game->pRenderer);

        free(game);
    }

    SDL_Quit();
}

void send_key(SDL_Keycode keydown, int mysocket)
{

    switch (keydown)
    {
    case SDLK_UP:
        if (send(mysocket, "up\n", 3, MSG_NOSIGNAL) < 0)
        {
            puts("send failed");
            close(mysocket);
        }
        break;
    case SDLK_DOWN:
        if (send(mysocket, "Down\n", 5, MSG_NOSIGNAL) < 0)
        {
            puts("send failed");
            close(mysocket);
        }
        break;
    case SDLK_RIGHT:
        if (send(mysocket, "Right\n", 6, MSG_NOSIGNAL) < 0)
        {
            puts("send failed");
            close(mysocket);
        }
        break;
    case SDLK_LEFT:
        if (send(mysocket, "Left\n", 5, MSG_NOSIGNAL) < 0)
        {
            puts("send failed");
            close(mysocket);
        }
        break;
    case SDLK_SPACE:
        if (send(mysocket, "Action\n", 7, MSG_NOSIGNAL) < 0)
        {
            puts("send failed");
            close(mysocket);
        }
        break;
    }
}