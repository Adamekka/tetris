#ifndef UI_H
#define UI_H

#include "assets.h"

void UI_draw_bg(SDL_Renderer* const renderer);
void UI_draw_score(
    SDL_Renderer* const renderer,
    const Assets* const assets,
    const uint16_t score
);

#endif
