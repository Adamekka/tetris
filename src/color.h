#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL_render.h>

#define SDL_SetRenderDrawColor(renderer, color)                                \
    SDL_SetRenderDrawColor((renderer), (color.r), (color.g), (color.b), 255)

typedef struct {
    uint8_t r, g, b;
} Color;

Color Color_init(const uint8_t r, const uint8_t g, const uint8_t b);

SDL_Color Color_to_SDL_Color(const Color c);

#endif
