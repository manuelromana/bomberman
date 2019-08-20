#include "../headerFiles/fonts.h"
#include "../headerFiles/header.h"

SDL_Texture *font_load(stGame *game, TTF_Font *police, char* content) {
    SDL_Color noir = {0, 0, 0};
    
    //font->texture = malloc(sizeof(stFont *));

    game->surface = TTF_RenderText_Blended(police, content, noir);

    if (!game->surface) {
        fprintf(stderr, "Erreur au chargement du text : %s\n", IMG_GetError());
        game_destroy_2(game);
    } else {
        game->texture = SDL_CreateTextureFromSurface(game->pRenderer, game->surface);

        if (!game->texture) {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            game_destroy_2(game);
        }

        SDL_FreeSurface(game->surface);

        return game->texture;
    }

}