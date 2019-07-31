#include "../headerFiles/game.h"

stGame* game_init() {
  stGame* game = {0};
  game = malloc(sizeof(stGame));
  game->player = (struct stPlayer*)malloc(sizeof(stPlayer));
  game->map = (struct stMap*)malloc(sizeof(stMap));

  if (game == NULL || game->player == NULL || game->map == NULL) return NULL;

  game = map_init(game);
  game->screenSize.x = 1216;
  game->screenSize.y = 960;
  game->pWindow = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, game->screenSize.x,
                                   game->screenSize.y, SDL_WINDOW_OPENGL);
  game = player_init(game);
  game = bomb_init(game);

  if (game->pWindow) {
    game->pRenderer =
        SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!game->pRenderer) {
      printf("Could not create renderer: %s\n", SDL_GetError());
      return NULL;
    }
  } else {
    printf("Could not create window: %s\n", SDL_GetError());
    return NULL;
  }

  SDL_Surface* frontBomberman =
      IMG_Load("assets/Bomberman/Front/Bman_F_f00.png");
  SDL_Surface* backBomberman = IMG_Load("assets/Bomberman/Back/Bman_B_f00.png");
  SDL_Surface* rightSideBomberman =
      IMG_Load("assets/Bomberman/Side/Bman_F_f00.png");
  SDL_Surface* leftSideBomberman =
      IMG_Load("assets/Bomberman/Side/Bman_F_f00.png");

  if (!frontBomberman || !backBomberman || !rightSideBomberman ||
      !leftSideBomberman) {
    fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
    game_destroy(game);
    return NULL;
  } else {
    game->player->pTexPlayerFront =
        SDL_CreateTextureFromSurface(game->pRenderer, frontBomberman);
    game->player->pTexPlayerBack =
        SDL_CreateTextureFromSurface(game->pRenderer, backBomberman);
    game->player->pTexPlayerRight =
        SDL_CreateTextureFromSurface(game->pRenderer, rightSideBomberman);
    game->player->pTexPlayerLeft =
        SDL_CreateTextureFromSurface(game->pRenderer, leftSideBomberman);
    if (!game->player->pTexPlayerFront || !game->player->pTexPlayerBack) {
      fprintf(stderr, "Erreur au chargement de la texture ! %s\n",
              SDL_GetError());
      game_destroy(game);
      return NULL;
    }
  }

  SDL_Surface* surfaceBombe = IMG_Load("assets/Bomb/Bomb_f03.png");
  if (!surfaceBombe) {
    fprintf(stderr, "Erreur au chargement de l'image : %s\n", IMG_GetError());
    game_destroy(game);
    return NULL;
  } else {
    game->map->pTexBomb =
        SDL_CreateTextureFromSurface(game->pRenderer, surfaceBombe);
    if (!game->map->pTexBomb) {
      fprintf(stderr, "Erreur au chargement de la texture ?? %s\n",
              SDL_GetError());
      game_destroy(game);
      return NULL;
    }
  }

  return game;
}

void game_draw(stGame* game) {
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

  load_map(game);
  draw_map(game);

  SDL_SetRenderDrawColor(game->pRenderer, 10, 50, 10, 255);
  SDL_RenderFillRect(game->pRenderer, &destinationPlayerColision);
  SDL_RenderPresent(game->pRenderer);

  switch (game->player->playerDirection) {
    case 0:
      SDL_RenderCopy(game->pRenderer, game->player->pTexPlayerRight, NULL,
                     &destinationPlayer);
      break;
    case 1:
      SDL_RenderCopyEx(game->pRenderer, game->player->pTexPlayerLeft, NULL,
                       &destinationPlayer, 0, NULL, flip);
      break;
    case 2:
      SDL_RenderCopy(game->pRenderer, game->player->pTexPlayerBack, NULL,
                     &destinationPlayer);
      break;
    case 3:
      SDL_RenderCopy(game->pRenderer, game->player->pTexPlayerFront, NULL,
                     &destinationPlayer);
      break;
  }

  draw_bomb(game);
  while (game->bomb->bombs != NULL) {
    if (game->PresentTime - game->bomb->bombs->startTime)
      destroy_bomb(game, game->bomb);
    else
      break;
  }
  SDL_RenderPresent(game->pRenderer);
}

int game_event(stGame* game) {
  int quit = 0;
  SDL_Event e;

  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      quit = 1;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
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

void game_destroy(stGame* game) {
  if (game) {
    SDL_DestroyWindow(game->pWindow);
    SDL_DestroyRenderer(game->pRenderer);
    SDL_DestroyTexture(game->player->pTexPlayerFront);
    SDL_DestroyTexture(game->player->pTexPlayerBack);
    SDL_DestroyTexture(game->player->pTexPlayerLeft);
    SDL_DestroyTexture(game->player->pTexPlayerRight);
    SDL_DestroyTexture(game->map->pTexBomb);
    SDL_DestroyTexture(game->map->pTexWall);

    free(game->map);
    free(game->player);
    free(game);
  }
}

void game_boucle(stGame* game) {
  int quit = 0;
  game->LastTime = SDL_GetTicks();
  unsigned int lastFps, fps = 0;

  while (quit != 1) {
    game->PresentTime = SDL_GetTicks();
    game->Delta = game->PresentTime - game->LastTime;
    game->LastTime = game->PresentTime;
    game_draw(game);
    quit = game_event(game);
    fps++;
    if (game->PresentTime - lastFps > 1000) {
      printf("FPS : %d\n", fps);
      fps = 0;
      lastFps = game->PresentTime;
    }
    SDL_Delay(15);
  }
}