#include "ui.h"
#include "consts.h"
#include "text.h"
#include <assert.h>

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

    for (uint8_t x = 0; x < s->tiles.x; x++)
        for (uint8_t y = 0; y < s->tiles.y; y++) {
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
    const Assets* const a,
    const Settings* const s,
    const uint16_t score_int
) {
    char score_str[SCORE_STR_LEN];
    snprintf(score_str, SCORE_STR_LEN, "Score: %u", score_int);

    const int32_t lpad = s->tiles.x * (s->tile_size + s->tile_offset);

    const Rect score_rect = {
      lpad + 60,
      BUTTON_HEIGHT - 30,
      0,
      0,
    };

    const Rect hint_rect = {lpad + 205, WINDOW_HEIGHT - 50, 0, 0};

    Text score;
    Text_init(
        &score,
        score_str,
        score_rect,
        (SDL_Color){255, 255, 255, 255},
        (Option_uint16){0}
    );
    Text_draw(&score, renderer, a);

    Text hint;
    Text_init(
        &hint,
        "A/D to move, S to accelerate, J/L to rotate, Q to quit.",
        hint_rect,
        (SDL_Color){255, 255, 255, 255},
        (Option_uint16){1, WINDOW_WIDTH / 2}
    );
    Text_draw(&hint, renderer, a);
}

#define GAME_OVER_MESSAGE "Game Over, new game will start in 3 seconds"
#define LOOPS 3

void UI_draw_game_over(SDL_Renderer* const renderer, const Assets* const a) {
    for (uint8_t i = 1; i <= LOOPS; i++) {
        SDL_SetRenderDrawColor(
            renderer, BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, 255
        );
        SDL_RenderClear(renderer);

        const Rect game_over_rect = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, 0};

        char game_over_text[sizeof(GAME_OVER_MESSAGE) + LOOPS];

        switch (i) {
            case 1: {
                snprintf(
                    game_over_text,
                    sizeof(game_over_text),
                    "%s.",
                    GAME_OVER_MESSAGE
                );
                break;
            }

            case 2: {
                snprintf(
                    game_over_text,
                    sizeof(game_over_text),
                    "%s..",
                    GAME_OVER_MESSAGE
                );
                break;
            }

            case 3: {
                snprintf(
                    game_over_text,
                    sizeof(game_over_text),
                    "%s...",
                    GAME_OVER_MESSAGE
                );
                break;
            }

            default: {
                assert(false);
                return;
            }
        }

        Text game_over;
        Text_init(
            &game_over,
            game_over_text,
            game_over_rect,
            (SDL_Color){255, 255, 255, 255},
            (Option_uint16){0}
        );
        Text_draw(&game_over, renderer, a);

        SDL_RenderPresent(renderer);

        SDL_Delay(1000);
    }
}
