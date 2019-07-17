#include "../headerFiles/header.h"

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