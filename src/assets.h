#ifndef ASSETS_H
#define ASSETS_H

#include <SDL2/SDL_ttf.h>

typedef struct {
    TTF_Font* font;
} Assets;

void Assets_init(Assets* const a);
void Assets_destroy(const Assets* const a);

#endif
