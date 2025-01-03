#ifndef UI_H
#define UI_H

#include "settings.h"

void UI_draw_bg(SDL_Renderer* const renderer, const Settings* const settings);
void UI_draw_text(
    SDL_Renderer* const renderer,
    const Assets* const assets,
    const Settings* const settings,
    const uint16_t score_int
);

void UI_draw_game_over(
    SDL_Renderer* const renderer, const Assets* const assets
);

#endif
