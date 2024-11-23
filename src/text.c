#include "text.h"
#include <assert.h>

void Text_init(
    Text* const t,
    const char* const text,
    const Rect rect,
    const SDL_Color color,
    const optional_uint16 wrap
) {
    t->text = text;
    t->rect = rect;
    t->color = color;
    t->wrap = wrap;
}

void Text_draw(
    const Text* const t,
    SDL_Renderer* const renderer,
    const Assets* const assets
) {
    SDL_Surface* surface = NULL;

    if (t->wrap.present)
        surface = TTF_RenderText_Blended_Wrapped(
            assets->font, t->text, t->color, t->wrap.value
        );
    else
        surface = TTF_RenderText_Blended(assets->font, t->text, t->color);

    assert(surface);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    const Rect text_rect = {
      t->rect.x + t->rect.w / 2 - surface->w / 2,
      t->rect.y + t->rect.h / 2 - surface->h / 2,
      surface->w,
      surface->h
    };

    SDL_RenderCopy(renderer, texture, NULL, &text_rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
