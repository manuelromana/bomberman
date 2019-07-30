#include "../headerFiles/map.h"
#include "../headerFiles/game.h"

void draw_bomb(stGame* game) {
    game->map->bombPositionRect.x = (game->player->playerPositionRect.x) + 10;
    game->map->bombPositionRect.y =  (game->player->playerPositionRect.y) + 80;
}