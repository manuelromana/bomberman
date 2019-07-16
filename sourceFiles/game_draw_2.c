#include "../headerFiles/header.h"

void game_draw_2(stGame *game, char *test)
{

    TTF_Font *police = NULL;

    SDL_Surface *testsurface = NULL;
    SDL_Texture *testText = NULL;
    SDL_Rect testPositionRect;

    SDL_SetRenderDrawColor(game->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(game->pRenderer);

    // printf("test:%s\n", test);
    //render invitation
    game->textPositionRect.x = 60;
    game->textPositionRect.y = 60;
    game->textPositionRect.w = 400;
    game->textPositionRect.h = 100;
    SDL_Rect texte = {game->textPositionRect.x, game->textPositionRect.y, game->textPositionRect.w, game->textPositionRect.h};

    // render input
    // surface
    police = TTF_OpenFont("assets/font/angelina.TTF", 65);

    SDL_Color noir = {0, 0, 0};
    if (*test != '\0')
    {
        testsurface = TTF_RenderText_Blended(police, test, noir);
        if (!testsurface)
        {
            fprintf(stderr, "Erreur au chargement du texte : %s\n", IMG_GetError());
            game_destroy_2(game);
            return;
        }
        else
        { //création de la texture si la surface à marché
            testText = SDL_CreateTextureFromSurface(game->pRenderer, testsurface);
            if (!testText)
            {
                fprintf(stderr, "Erreur au chargement de la texture: %s\n", SDL_GetError());
                game_destroy_2(game);
                return;
            }
            SDL_FreeSurface(testsurface);
        }
        int width = my_strlen(test);

        //déclaration de la position
        testPositionRect.x = 60;
        testPositionRect.y = 130;
        testPositionRect.w = 15 * width;
        testPositionRect.h = 50;
        SDL_Rect testinput = {testPositionRect.x, testPositionRect.y, testPositionRect.w, testPositionRect.h};
        SDL_RenderCopy(game->pRenderer, testText, NULL, &testinput);
    }
    SDL_RenderCopy(game->pRenderer, game->pTexText, NULL, &texte);

    SDL_RenderPresent(game->pRenderer);
}
