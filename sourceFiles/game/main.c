#include "../../headerFiles/game/gameMulti.h"

int main(int argc, char *argv[])
{
  stGame *game = game_init();

  game_boucle(game);
  game_destroy(game);
  printf("%s", "bonjour");

  SDL_Quit();
  return (EXIT_SUCCESS);
}