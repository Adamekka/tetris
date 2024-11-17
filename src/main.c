#include "game.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window
        = SDL_CreateWindow("Tetris", 0, 0, 800, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    Assets assets;
    Assets_init(&assets);

    Game game;
    Game_run(&game, &assets, renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
