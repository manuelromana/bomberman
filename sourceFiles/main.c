#include "../headerFiles/game.h"

int main(int argc, char *argv[]) {
  stGame *game = game_init();

  game_boucle(game);
  game_destroy(game);

  SDL_Quit();
  return (EXIT_SUCCESS);
}