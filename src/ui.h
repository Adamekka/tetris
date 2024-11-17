#ifndef UI_H
#define UI_H

#include "assets.h"

void UI_draw_bg(SDL_Renderer* renderer);
void UI_draw_score(SDL_Renderer* renderer, Assets* assets, uint16_t score);

#endif
