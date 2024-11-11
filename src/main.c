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

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    if (event.type == SDL_QUIT)
                        running = false;
                    else if (event.key.keysym.sym == SDLK_j)
                        Tetromino_rotate_left(&tetromino, game.tetrominoes);
                    else if (event.key.keysym.sym == SDLK_l)
                        Tetromino_rotate_right(&tetromino, game.tetrominoes);
                    else if (event.key.keysym.sym == SDLK_a)
                        Tetromino_move_left(&tetromino, game.tetrominoes);
                    else if (event.key.keysym.sym == SDLK_d)
                        Tetromino_move_right(&tetromino, game.tetrominoes);
                    else if (event.key.keysym.sym == SDLK_s) {
                        MoveState s = MOVE;
                        while (s == MOVE)
                            s = Tetromino_move_down(&tetromino);
                    }
                }
            }
        }

        switch (state) {
            case NEW: {
                bool ok = Tetromino_init(&tetromino);

                if (!ok)
                    running = false;

                state = MOVING;
                break;
            }

            case MOVING: {
                MoveState moved = Tetromino_move_down(&tetromino);

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

        UI_draw_bg(renderer);

        Tetrominoes_draw(renderer, &tetromino, game.tetrominoes);

        SDL_RenderPresent(renderer);

        SDL_Delay(1000 / 6);
    }

    // TODO: Game over screen

    Game_destroy(&game);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
