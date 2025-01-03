#include "consts.h"
#include "main_menu.h"
#include <time.h>

int main(void) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Tetris", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    srand((uint32_t)time(NULL));

    Score score;
    Score_init(score);

    Assets assets;
    Assets_init(&assets);

    Settings settings;
    Settings_init(&settings);

    MainMenu_run(renderer, score, &assets, &settings);

    Assets_destroy(&assets);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
