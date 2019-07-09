#include "../headerFiles/header.h"

void draw_bomb(stGame* game, int flagBomb) {
    if (flagBomb == 1) {
            game->bombPositionRect.x = (game->playerPositionRect.x) + 10;
            game->bombPositionRect.y =  (game->playerPositionRect.y) + 80;
    }
}