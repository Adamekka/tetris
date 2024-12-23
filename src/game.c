#include "game.h"
#include "tetromino_state.h"
#include "ui.h"
#include <assert.h>

#define INITIAL_ALLOCATED_TETROMINOES_COUNT 10

void Game_tetromino_push(Game* const g, const Tetromino t);
void Game_update_highest_tetrominoes(
    const Game* const g, const Settings* const s
);
void Game_check_lines(Game* const g, const Settings* const s);

void Game_init(Game* const g, const Settings* const s) {
    g->score = 0;

    // Prealloc some memory, so we don't have to realloc first few times
    g->tetrominoes
        = malloc(sizeof(*g->tetrominoes) * INITIAL_ALLOCATED_TETROMINOES_COUNT);

    g->tetrominoes_allocated = INITIAL_ALLOCATED_TETROMINOES_COUNT;
    g->tetrominoes_count = 0;

    g->highest_tetrominoes
        = malloc(sizeof(*g->highest_tetrominoes) * s->tiles.x);

    for (uint16_t i = 0; i < s->tiles.x; i++)
        g->highest_tetrominoes[i] = 0;
}

void Game_destroy(Game* const g) {
    free(g->tetrominoes);
    g->tetrominoes = NULL;
}

void Game_run(
    Game* g,
    Score score,
    const Assets* const a,
    const Settings* settings,
    SDL_Renderer* const renderer
) {
game_start:
    Game_init(g, settings);

    TetrominoState state = NEW;
    Tetromino tetromino;
    Tetromino next_tetromino;

    Tetromino_init(&next_tetromino, g->tetrominoes_count, settings);

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    if (event.type == SDL_QUIT
                        || event.key.keysym.sym == SDLK_q)
                        running = false;
                    else if (event.key.keysym.sym == SDLK_j)
                        Tetromino_rotate_left(
                            &tetromino,
                            g->tetrominoes,
                            g->tetrominoes_count,
                            settings
                        );
                    else if (event.key.keysym.sym == SDLK_l)
                        Tetromino_rotate_right(
                            &tetromino,
                            g->tetrominoes,
                            g->tetrominoes_count,
                            settings
                        );
                    else if (event.key.keysym.sym == SDLK_a)
                        Tetromino_move_left(
                            &tetromino,
                            g->tetrominoes,
                            g->tetrominoes_count,
                            settings
                        );
                    else if (event.key.keysym.sym == SDLK_d)
                        Tetromino_move_right(
                            &tetromino,
                            g->tetrominoes,
                            g->tetrominoes_count,
                            settings
                        );
                    else if (event.key.keysym.sym == SDLK_s)
                        for (uint8_t i = 0; i < 2; i++)
                            Tetromino_move_down(
                                &tetromino, g->highest_tetrominoes, settings
                            );
                }
            }
        }

        switch (state) {
            case NEW: {
                tetromino = next_tetromino;

                Tetromino_init(&next_tetromino, g->tetrominoes_count, settings);

                if (!Tetromino_can_move(
                        tetromino.tiles,
                        g->tetrominoes,
                        g->tetrominoes_count,
                        settings
                    )) {
                    UI_draw_game_over(renderer, a);
                    Score_add(score, g->score);
                    Game_destroy(g);
                    goto game_start;
                }

                state = MOVING;
                break;
            }

            case MOVING: {
                MoveState moved = Tetromino_move_down(
                    &tetromino, g->highest_tetrominoes, settings
                );

                if (moved == STOP) {
                    state = STOPPED;
                    goto STOPPED; // Skip input
                }

                break;
            }

            STOPPED:
            case STOPPED: {
                Game_tetromino_push(g, tetromino);
                Game_check_lines(g, settings);
                Game_update_highest_tetrominoes(g, settings);
                state = NEW;
                break;
            }
        }

        UI_draw_bg(renderer, settings);
        UI_draw_text(renderer, a, settings, g->score);
        Score_draw(score, renderer, a);

        Tetrominoes_draw(
            renderer,
            &tetromino,
            &next_tetromino,
            g->tetrominoes,
            g->tetrominoes_count,
            a,
            settings
        );

        SDL_RenderPresent(renderer);

        SDL_Delay(1000 / settings->speed);
    }

    Game_destroy(g);
    g = NULL;
}

void Game_tetromino_push(Game* const g, const Tetromino t) {
    // Replace destroyed Tetromino with new one if possible
    for (uint16_t i = 0; i < g->tetrominoes_count; i++)
        if (!g->tetrominoes[i].present) {
            g->tetrominoes[i] = (Option_Tetromino){true, t};
            return;
        }

    // If not, push or allocate more memory
    if (g->tetrominoes_count >= g->tetrominoes_allocated) {
        // The C++ way of calculating the new size for std::vector
        g->tetrominoes_allocated
            = (uint16_t)round(g->tetrominoes_allocated * 1.5);

        g->tetrominoes = realloc(
            g->tetrominoes, sizeof(*g->tetrominoes) * g->tetrominoes_allocated
        );
    }

    g->tetrominoes[g->tetrominoes_count++] = (Option_Tetromino){true, t};
}

void Game_tetromino_cleanup(const Game* const g) {
    for (uint16_t i = 0; i < g->tetrominoes_count; i++) {
        bool present = false;

        for (uint8_t j = 0; j < TILES_IN_TETROMINO; j++)
            present |= g->tetrominoes[i].value.tiles[j].present;

        if (!present)
            g->tetrominoes[i].present = false;
    }
}

void Game_update_highest_tetrominoes(
    const Game* const g, const Settings* const s
) {
    for (uint16_t i = 0; i < s->tiles.x; i++)
        g->highest_tetrominoes[i] = 0;

    for (uint16_t i = 0; i < g->tetrominoes_count; i++) {
        if (!g->tetrominoes[i].present)
            continue;

        const Tetromino* t = &g->tetrominoes[i].value;

        for (uint8_t j = 0; j < TILES_IN_TETROMINO; j++) {
            if (!t->tiles[j].present)
                continue;

            const Vec2* tile = &t->tiles[j].value;

            if (tile->y > g->highest_tetrominoes[tile->x])
                g->highest_tetrominoes[tile->x] = tile->y;
        }
    }
}

void Game_check_lines(Game* const g, const Settings* const s) {
    bool any_found = false;

    for (int16_t y = s->tiles.y - 1; y >= 0; y--) {
        bool found = true;

        for (uint8_t x = 0; x < s->tiles.x; x++) {
            bool col_tile_found = false;

            for (uint16_t i = 0; i < g->tetrominoes_count; i++) {
                if (g->tetrominoes[i].present) {
                    for (uint8_t j = 0; j < TILES_IN_TETROMINO; j++) {
                        if (g->tetrominoes[i].value.tiles[j].present
                            && g->tetrominoes[i].value.tiles[j].value.x == x
                            && g->tetrominoes[i].value.tiles[j].value.y == y) {
                            col_tile_found = true;
                            break;
                        }
                    }
                }
                if (col_tile_found)
                    goto next_x_tile;
            }

            if (!col_tile_found) {
                found = false;
                goto next_y_line;
            }

        next_x_tile:
        }

        assert(found);
        any_found = true;

        g->score++;

        // Remove all tiles in the line
        for (uint16_t i = 0; i < g->tetrominoes_count; i++)
            if (g->tetrominoes[i].present)
                for (uint8_t j = 0; j < TILES_IN_TETROMINO; j++)
                    if (g->tetrominoes[i].value.tiles[j].present)
                        if (g->tetrominoes[i].value.tiles[j].value.y == y)
                            g->tetrominoes[i].value.tiles[j].present = false;

        // Move all Tetrominoes above the line down
        for (uint16_t i = 0; i < g->tetrominoes_count; i++)
            if (g->tetrominoes[i].present)
                for (uint8_t j = 0; j < TILES_IN_TETROMINO; j++)
                    if (g->tetrominoes[i].value.tiles[j].present
                        && g->tetrominoes[i].value.tiles[j].value.y > y)
                        g->tetrominoes[i].value.tiles[j].value.y--;

    next_y_line:
    }

    if (any_found)
        Game_tetromino_cleanup(g);
}
