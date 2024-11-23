#ifndef TEXT_H
#define TEXT_H

#include "assets.h"
#include "optional_int.h"
#include "rect.h"

typedef struct {
    const char* text;
    Rect rect;
    SDL_Color color;
    optional_uint16 wrap;
} Text;

void Text_init(
    Text* const t,
    const char* const text,
    const Rect rect,
    const SDL_Color color,
    const optional_uint16 wrap
);

void Text_draw(
    const Text* const t,
    SDL_Renderer* const renderer,
    const Assets* const assets
);

#endif
