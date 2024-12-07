#include "ui.h"
#include "consts.h"
#include "text.h"

// 0x333333
#define TILE_COLOR_R 0x33
#define TILE_COLOR_G 0x33
#define TILE_COLOR_B 0x33

// 0x000000
#define BG_COLOR_R 0x00
#define BG_COLOR_G 0x00
#define BG_COLOR_B 0x00

void UI_draw_bg(SDL_Renderer* const renderer, const Settings* const s) {
    SDL_SetRenderDrawColor(renderer, BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(
        renderer, TILE_COLOR_R, TILE_COLOR_G, TILE_COLOR_B, 255
    );

    for (int x = 0; x < s->tiles.x; x++)
        for (int y = 0; y < s->tiles.y; y++) {
            const Rect rect = {
              x * (s->tile_size + s->tile_offset) + LEFT_PADDING,
              y * (s->tile_size + s->tile_offset) + TOP_PADDING,
              s->tile_size,
              s->tile_size
            };

            SDL_RenderFillRect(renderer, &rect);
        }
}

#define SCORE_STR_LEN (sizeof("Score: ") + UINT16_MAX_DIGITS)

void UI_draw_text(
    SDL_Renderer* const renderer,
    const Assets* const assets,
    const Settings* const s,
    const uint16_t score_int
) {
    char score_str[SCORE_STR_LEN];
    snprintf(score_str, SCORE_STR_LEN, "Score: %u", score_int);

    const int L_PAD = s->tiles.x * (s->tile_size + s->tile_offset);

    const Rect score_rect = {
      L_PAD + 60,
      BUTTON_HEIGHT - 30,
      0,
      0,
    };

    const Rect hint_rect = {L_PAD + 205, WINDOW_HEIGHT - 50, 0, 0};

    Text score;
    Text_init(
        &score,
        score_str,
        score_rect,
        (SDL_Color){255, 255, 255, 255},
        (optional_uint16){0}
    );
    Text_draw(&score, renderer, assets);

    Text hint;
    Text_init(
        &hint,
        "A/D to move, S to accelerate, J/L to rotate, Q to quit.",
        hint_rect,
        (SDL_Color){255, 255, 255, 255},
        (optional_uint16){1, WINDOW_WIDTH / 2}
    );
    Text_draw(&hint, renderer, assets);
}
