#include "button.h"

void Button_init(
    Button* const b,
    const char* const text,
    const Rect rect,
    const Color bg,
    const Color selected_bg,
    const Color text_color
) {
    Text text_;
    Text_init(
        &text_, text, rect, Color_to_SDL_Color(text_color), (Option_uint16){0}
    );

    b->text = text_;
    b->bg = bg;
    b->selected_bg = selected_bg;
}

void Button_draw(
    const Button* const b,
    SDL_Renderer* const renderer,
    const Assets* const assets,
    bool selected
) {
    // Background
    if (selected)
        SDL_SetRenderDrawColor(renderer, b->selected_bg);
    else
        SDL_SetRenderDrawColor(renderer, b->bg);

    SDL_RenderFillRect(renderer, &b->text.rect);

    Text_draw(&b->text, renderer, assets);
}
