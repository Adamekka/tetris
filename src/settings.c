#include "settings.h"

#define TILES_X 10
#define TILES_Y 16

#define TOP_PADDING 4
#define LEFT_PADDING 4

#define TILE_SIZE 32
#define TILE_OFFSET 4

void Settings_init(Settings* s) {
    s->tiles = (Vec2){TILES_X, TILES_Y};
    s->tile_size = TILE_SIZE;
    s->tile_offset = TILE_OFFSET;
}
