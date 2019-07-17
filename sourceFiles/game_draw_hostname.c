#include "../headerFiles/header.h"

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
