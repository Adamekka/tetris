#include "consts.h"
#include "main_menu.h"
#include "settings.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Tetris", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    Assets assets;
    Assets_init(&assets);

    Settings settings;
    Settings_init(&settings);

    MainMenu_run(renderer, &assets);

    Assets_destroy(&assets);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
