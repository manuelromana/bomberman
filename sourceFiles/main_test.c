#include "../headerFiles/header.h"

int main(void)
{

    st_game *game = game_init_test();
    draw_game_test(game);
    SDL_Delay(3000);
    game_destroy(game);
    return 0;
}