#ifndef SETTINGS_H
#define SETTINGS_H

#include "assets.h"
#include "vec2.h"

typedef struct {
    Vec2 tiles;
    uint16_t tile_size;
    uint16_t tile_offset;
    uint8_t speed;
} Settings;

void Settings_init(Settings* const s);
void Settings_run(
    Settings* const s, SDL_Renderer* const renderer, const Assets* const assets
);

#endif
