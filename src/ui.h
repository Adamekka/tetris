#ifndef UI_H
#define UI_H

#include "settings.h"

void UI_draw_bg(SDL_Renderer* const renderer, const Settings* const s);
void UI_draw_text(
    SDL_Renderer* const renderer,
    const Assets* const assets,
    const Settings* const s,
    const uint16_t score_int
);

#endif
