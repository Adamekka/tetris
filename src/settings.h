#ifndef SETTINGS_H
#define SETTINGS_H

#include "vec2.h"

typedef struct {
    Vec2 tiles;
    uint16_t tile_size;
    uint16_t tile_offset;
} Settings;

void Settings_init(Settings* s);

#endif
