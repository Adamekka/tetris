#include "assets.h"

void Assets_init(Assets* const assets) {
    TTF_Init();
    assets->font = TTF_OpenFont("assets/ComicMono.ttf", 24);
}
