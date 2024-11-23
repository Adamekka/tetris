#ifndef BUTTON_H
#define BUTTON_H

#include "color.h"
#include "text.h"

typedef struct {
    Text text;
    Color bg;
    Color selected_bg;
} Button;

void Button_init(
    Button* const b,
    const char* const text,
    const Rect rect,
    const Color bg,
    const Color selected_bg,
    const Color text_color
);

void Button_draw(
    const Button* const b,
    SDL_Renderer* const renderer,
    const Assets* const assets,
    bool selected
);

#endif
