#include "../../headerFiles/game/game.h"

stGame *game_init()
{
  stGame *game = {0};
  game = malloc(sizeof(stGame));
  game->player = (struct stPlayer *)malloc(sizeof(stPlayer));
  game->map = (struct stMap *)malloc(sizeof(stMap));
  game->object = (struct stObject *)malloc(sizeof(stObject));

  if (game == NULL || game->player == NULL || game->map == NULL ||
      game->object == NULL)
    return NULL;

  game->pWindow = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, 1216,
                                   960, SDL_WINDOW_OPENGL);

  if (game->pWindow)
  {
    game->pRenderer =
        SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!game->pRenderer)
    {
      printf("Could not create renderer: %s\n", SDL_GetError());
      return NULL;
    }
  }
  else
  {
    printf("Could not create window: %s\n", SDL_GetError());
    return NULL;
  }

  textures_init(game);
  map_init(game);
  player_init(game);
  object_init(game);

  return game;
}

stGame *game_network_init(SDL_Window *pWindow, SDL_Renderer *pRenderer)
{
  stGame *game = {0};
  game = malloc(sizeof(stGame));
  game->player = (struct stPlayer *)malloc(sizeof(stPlayer));
  game->map = (struct stMap *)malloc(sizeof(stMap));
  game->object = (struct stObject *)malloc(sizeof(stObject));

  if (game == NULL || game->player == NULL || game->map == NULL ||
      game->object == NULL)
    return NULL;

  game->pWindow = pWindow;
  game->pRenderer = pRenderer;

  textures_init(game);
  map_init(game);
  player_init(game);
  object_init(game);

  return game;
}
void game_draw(stGame *game)
{
  SDL_SetRenderDrawColor(game->pRenderer, 10, 50, 10, 255);
  SDL_RenderClear(game->pRenderer);
  SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
  SDL_Rect destinationPlayer = {game->player->playerX, game->player->playerY,
                                game->player->playerPositionRect.w,
                                game->player->playerPositionRect.h};

  SDL_Rect destinationPlayerColision = {
      game->player->playerX + game->player->playerColisionRect.x,
      game->player->playerY + game->player->playerColisionRect.y,
      game->player->playerColisionRect.w, game->player->playerColisionRect.h};

  draw_map(game);

  SDL_SetRenderDrawColor(game->pRenderer, 10, 50, 10, 255);
  SDL_RenderFillRect(game->pRenderer, &destinationPlayerColision);

  draw_bomb(game);
  while (game->object->bombs != NULL)
  {
    if (game->presentTime - game->object->bombs->startTime > 3000)
    {
      create_explosion(game, game->object->bombs);
      destroy_bomb(game, game->object->bombs);
    }
    else
      break;
  }

  draw_explosion(game);
  explosion *currentExplosion = game->object->explosion;
  explosion *tempExplosion;
  while (currentExplosion != NULL)
  {
    tempExplosion = currentExplosion->next;
    if (currentExplosion->startTime + 1000 < game->presentTime)
    {
      destroy_explosion(game, currentExplosion);
    }
    currentExplosion = tempExplosion;
  }
  switch (game->player->playerDirection)
  {
  case 0:
    SDL_RenderCopy(game->pRenderer, game->texture[2]->texture, NULL,
                   &destinationPlayer);
    break;
  case 1:
    SDL_RenderCopyEx(game->pRenderer, game->texture[2]->texture, NULL,
                     &destinationPlayer, 0, NULL, flip);
    break;
  case 2:
    SDL_RenderCopy(game->pRenderer, game->texture[1]->texture, NULL,
                   &destinationPlayer);
    break;
  case 3:
    SDL_RenderCopy(game->pRenderer, game->texture[0]->texture, NULL,
                   &destinationPlayer);
    break;
  }
  SDL_RenderPresent(game->pRenderer);
}

void game_network_event(int *step, stGame *game)
{

  SDL_Event e;

  while (SDL_PollEvent(&e) != 0)
  {
    if (e.type == SDL_QUIT)
    {
      *step = -1;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_RIGHT:
      case SDLK_LEFT:
      case SDLK_UP:
      case SDLK_DOWN:
        character_move(e.key.keysym.sym, game);
        break;
      case SDLK_SPACE:
        create_bomb(game);
        break;
      case SDLK_ESCAPE:
        *step = -1;
        break;
      }
    }
  }
}

int game_event(stGame *game)
{
  int quit = 0;
  SDL_Event e;

  while (SDL_PollEvent(&e) != 0)
  {
    if (e.type == SDL_QUIT)
    {
      quit = 1;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_RIGHT:
      case SDLK_LEFT:
      case SDLK_UP:
      case SDLK_DOWN:
        character_move(e.key.keysym.sym, game);
        break;
      case SDLK_SPACE:
        create_bomb(game);
        break;
      case SDLK_ESCAPE:
        quit = 1;
        break;
      }
    }
  }
  return quit;
}

void game_destroy(stGame *game)
{
  if (game)
  {
    SDL_DestroyWindow(game->pWindow);
    SDL_DestroyRenderer(game->pRenderer);

    textures_destroy(game);
    free(game->map);
    free(game->player);
    free(game);
    SDL_StopTextInput();
  }
}

void game_boucle(stGame *game)
{
  int quit = 0;
  game->lastTime = SDL_GetTicks();
  unsigned int lastFps = 0;
  unsigned int fps = 0;

  while (quit != 1)
  {
    game->presentTime = SDL_GetTicks();
    game->delta = game->presentTime - game->lastTime;
    game->lastTime = game->presentTime;
    game_draw(game);
    quit = game_event(game);
    fps++;
    if (game->presentTime - lastFps > 1000)
    {
      printf("FPS : %d\n", fps);
      fps = 0;
      lastFps = game->presentTime;
    }
    SDL_Delay(15);
  }
}

void draw_player_test(stGame *game)
{
  SDL_SetRenderDrawColor(game->pRenderer, 10, 50, 10, 255);
  SDL_RenderClear(game->pRenderer);
  //SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
  SDL_Rect destinationPlayer = {game->player->playerX, game->player->playerY,
                                game->player->playerPositionRect.w,
                                game->player->playerPositionRect.h};
  SDL_RenderCopy(game->pRenderer, game->texture[2]->texture, NULL,
                 &destinationPlayer);
  SDL_RenderPresent(game->pRenderer);
}