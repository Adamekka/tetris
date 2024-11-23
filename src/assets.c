#include "assets.h"

void Assets_init(Assets* const a) {
    TTF_Init();
    a->font = TTF_OpenFont("assets/ComicMono.ttf", 24);
}

void Assets_destroy(const Assets* const a) {
    TTF_CloseFont(a->font);
    TTF_Quit();
}
