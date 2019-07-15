#include "../headerFiles/header.h"

void game_destroy_2(stGame *game)
{
    if (game)
    {
        SDL_DestroyWindow(game->pWindow);
        SDL_DestroyRenderer(game->pRenderer);

        free(game);
    }
    // Clean up
    SDL_Quit();
}