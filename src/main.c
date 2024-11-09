#include "game.h"
#include "tetromino_state.h"
#include "ui.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window
        = SDL_CreateWindow("Tetris", 0, 0, 800, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_RenderClear(renderer);

    Game game;
    Game_init(&game);

    TetrominoState state = NEW;
    Tetromino tetromino;

    SDL_Event event;
    bool running = true;
    float last_time = SDL_GetTicks();

    while (running) {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                running = false;

        const float delta_time = SDL_GetTicks() - last_time;
        last_time = SDL_GetTicks();

        switch (state) {
            case NEW: {
                bool ok = Tetromino_init(&tetromino);

                if (!ok)
                    running = false;

                state = MOVING;
                break;
            }

            case MOVING: {
                MoveState moved = Game_tetromino_move_down(&game, &tetromino);

                if (moved == STOP)
                    state = STOPPED;
                else if (moved == GAME_OVER)
                    running = false;

                break;
            }

            case STOPPED: {
                Game_tetromino_push(&game, tetromino);
                state = NEW;
                break;
            }
        }

        SDL_RenderClear(renderer);

        UI_draw_bg(renderer);

        Tetrominoes_draw(renderer, &tetromino, game.tetrominoes);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 10);
    }

    // TODO: Game over screen

    Game_destroy(&game);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
