#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "score.h"
#include "settings.h"

void MainMenu_run(
    SDL_Renderer* const renderer,
    Score score,
    const Assets* const assets,
    Settings* const settings
);

#endif
