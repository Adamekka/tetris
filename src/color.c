#include "color.h"

Color Color_init(const uint8_t r, const uint8_t g, const uint8_t b) {
    return (Color){r, g, b};
}

SDL_Color Color_to_SDL_Color(const Color c) {
    return (SDL_Color){c.r, c.g, c.b, 255};
}
