#include "ui.h"
#include "consts.h"

// 0x333333
#define TILE_COLOR_R 0x33
#define TILE_COLOR_G 0x33
#define TILE_COLOR_B 0x33

// 0x000000
#define BG_COLOR_R 0x00
#define BG_COLOR_G 0x00
#define BG_COLOR_B 0x00

void UI_draw_bg(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(
        renderer, TILE_COLOR_R, TILE_COLOR_G, TILE_COLOR_B, 255
    );

    for (int x = 0; x < TILES_X; x++)
        for (int y = 0; y < TILES_Y; y++) {
            const SDL_Rect rect = {
              x * (TILE_SIZE + TILE_OFFSET) + LEFT_PADDING,
              y * (TILE_SIZE + TILE_OFFSET) + TOP_PADDING,
              TILE_SIZE,
              TILE_SIZE
            };

            SDL_RenderFillRect(renderer, &rect);
        }
}

void UI_draw_score(SDL_Renderer* renderer, Assets* assets, uint16_t score) {
    char score_str[10];
    snprintf(score_str, 10, "Score: %d", score);

    SDL_Surface* surface = TTF_RenderText_Blended(
        assets->font, score_str, (SDL_Color){255, 255, 255, 255}
    );

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {
      TILES_X * (TILE_SIZE + TILE_OFFSET) + 10, 10, surface->w, surface->h
    };

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
