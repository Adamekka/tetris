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

void UI_draw_bg(SDL_Renderer* const renderer) {
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

void UI_draw_score(
    SDL_Renderer* const renderer,
    const Assets* const assets,
    const uint16_t score
) {
    char score_str[10];
    snprintf(score_str, 10, "Score: %d", score);
    char* hint = "A/D to move, S to accelerate, J/L to rotate, Q to quit.";

    SDL_Surface* score_surface = TTF_RenderText_Blended(
        assets->font, score_str, (SDL_Color){255, 255, 255, 255}
    );

    SDL_Surface* hint_surface = TTF_RenderText_Blended_Wrapped(
        assets->font, hint, (SDL_Color){255, 255, 255, 255}, WINDOW_WIDTH / 2
    );

    SDL_Texture* score_texture
        = SDL_CreateTextureFromSurface(renderer, score_surface);
    SDL_Texture* hint_texture
        = SDL_CreateTextureFromSurface(renderer, hint_surface);

    const SDL_Rect score_rect = {
      TILES_X * (TILE_SIZE + TILE_OFFSET) + 10,
      10,
      score_surface->w,
      score_surface->h
    };

    const SDL_Rect hint_rect = {
      TILES_X * (TILE_SIZE + TILE_OFFSET) + 10,
      WINDOW_HEIGHT - 100,
      hint_surface->w,
      hint_surface->h
    };

    SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
    SDL_RenderCopy(renderer, hint_texture, NULL, &hint_rect);

    SDL_FreeSurface(score_surface);
    SDL_FreeSurface(hint_surface);
    SDL_DestroyTexture(score_texture);
    SDL_DestroyTexture(hint_texture);
}
