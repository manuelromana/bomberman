#include "../headerFiles/header.h"
#include "../headerFiles/fonts.h"

stGame *game_init_2()
{
    stGame *game = {0};
    game = malloc(sizeof(stGame));
    
    game->screenSize.x = 640;
    game->screenSize.y = 480;

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

    game->police1 = TTF_OpenFont(PATHFGRAFITI, 70);
    game->police2 = TTF_OpenFont(PATHFNEON, 45);
    SDL_Color noir = {0, 0, 0};

    game->pTextHostname = font_load(game, game->police1, TXTSURFHOSTNAME);
    game->pTextPortname = font_load(game, game->police1, TXTSURFPORTNAME);
    game->pTextWelcome = font_load(game,game->police1, TXTWELCOMESERVEUR);

    SDL_StartTextInput();

    return game;
}

void control_event(SDL_Event event, int *step, char **currentText, char **port, int socket_target)
{

    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case (SDL_QUIT):
            *step = -1;
        case (SDL_TEXTINPUT):
            strcat(*currentText, event.text.text);

            break;
        case (SDL_KEYDOWN):
            switch (event.key.keysym.sym)
            {
            case SDLK_BACKSPACE:
                strcpy(*currentText, "");
                break;
            case SDLK_RETURN:
                (*step)++;

                if (*step == 1)
                {

                    *currentText = *port;
                }

                break;

            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_RIGHT:
            case SDLK_LEFT:
            case SDLK_SPACE:
                send_key(event.key.keysym.sym, socket_target);
                break;
            }
        }
    }
}
void game_draw_hostname(stGame *game, char *hostname)
{
    SDL_Texture *pInputText = NULL;
    SDL_Rect inputPositionRect;

    //render fenêtre blanche
    SDL_SetRenderDrawColor(game->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(game->pRenderer);

    //render de l'invit de commande
    game->hostamePositionRect.x = 10;
    game->hostamePositionRect.y = 60;
    game->hostamePositionRect.w = 600;
    game->hostamePositionRect.h = 100;
    SDL_Rect hostnameInvite = {game->hostamePositionRect.x, game->hostamePositionRect.y, game->hostamePositionRect.w, game->hostamePositionRect.h};
    SDL_RenderCopy(game->pRenderer, game->pTextHostname, NULL, &hostnameInvite);

    //render de l'input
    SDL_Color noir = {0, 0, 0};
    if (*hostname != '\0')
    {
        pInputText = font_load(game, game->police2, hostname);

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
        pInputText = font_load(game, game->police2, port);

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