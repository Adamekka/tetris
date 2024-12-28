#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL_render.h>

#define SDL_SetRenderDrawColor(renderer, color)                                \
    SDL_SetRenderDrawColor((renderer), (color.r), (color.g), (color.b), 255)

// 0x000069
#define BG_COLOR_R 0
#define BG_COLOR_G 0
#define BG_COLOR_B 0x69

// 0x0000AA
#define BUTTON_COLOR_R 0
#define BUTTON_COLOR_G 0
#define BUTTON_COLOR_B 0xAA

// 0x0000FF
#define BUTTON_SELECTED_COLOR_R 0
#define BUTTON_SELECTED_COLOR_G 0
#define BUTTON_SELECTED_COLOR_B 0xFF

typedef struct {
    uint8_t r, g, b;
} Color;

Color Color_init(const uint8_t r, const uint8_t g, const uint8_t b);

SDL_Color Color_to_SDL_Color(const Color c);

#endif
