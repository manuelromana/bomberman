#include "../headerFiles/header.h"

void game_draw_2(stGame *game)
{
    SDL_SetRenderDrawColor(game->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(game->pRenderer);
    game->textPositionRect.x = 60;
    game->textPositionRect.y = 150;
    game->textPositionRect.w = 400;
    game->textPositionRect.h = 100;
    SDL_Rect texte = {game->textPositionRect.x, game->textPositionRect.y, game->textPositionRect.w, game->textPositionRect.h};
    SDL_RenderCopy(game->pRenderer, game->pTexText, NULL, &texte);
    SDL_RenderPresent(game->pRenderer);
}
