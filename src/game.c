#include "game.h"
#include "consts.h"
#include <assert.h>

#define INITIAL_ALLOCATED_TETROMINOES_COUNT 10

uint16_t tetrominoes_allocated = INITIAL_ALLOCATED_TETROMINOES_COUNT;
uint16_t tetrominoes_count = 0;

// Cache the highest Tetromino in each column
uint16_t highest_tetrominoes[TILES_X] = {0};

void Game_update_highest_tetrominoes(const Game* const g);

void Game_init(Game* const g) {
    g->score = 0;

    // Prealloc some memory, so we don't have to realloc first few times
    g->tetrominoes
        = malloc(sizeof(*g->tetrominoes) * INITIAL_ALLOCATED_TETROMINOES_COUNT);
}

void Game_destroy(Game* const g) {
    free(g->tetrominoes);
    g->tetrominoes = NULL;
}

void Game_tetromino_push(Game* const g, const Tetromino t) {
    // Replace destroyed Tetromino with new one if possible
    for (uint16_t i = 0; i < tetrominoes_count; i++)
        if (!g->tetrominoes[i].present) {
            g->tetrominoes[i] = (OptionalTetromino){true, t};
            return;
        }

    // If not, push or allocate more memory
    if (tetrominoes_count >= tetrominoes_allocated) {
        // The C++ way of calculating the new size for std::vector
        tetrominoes_allocated = (uint16_t)round(tetrominoes_allocated * 1.5);

        g->tetrominoes = realloc(
            g->tetrominoes, sizeof(*g->tetrominoes) * tetrominoes_allocated
        );
    }

    g->tetrominoes[tetrominoes_count++] = (OptionalTetromino){true, t};
}

void Game_tetromino_cleanup(const Game* const g) {
    for (uint16_t i = 0; i < tetrominoes_count; i++) {
        bool present = false;

        for (uint8_t j = 0; j < TILES_IN_TETROMINO; j++)
            present |= g->tetrominoes[i].value.tiles[j].present;

        if (!present)
            g->tetrominoes[i].present = false;
    }
}

void Game_update_highest_tetrominoes(const Game* const g) {
    for (uint16_t i = 0; i < TILES_X; i++)
        highest_tetrominoes[i] = 0;

    for (uint16_t i = 0; i < tetrominoes_count; i++) {
        if (!g->tetrominoes[i].present)
            continue;

        const Tetromino* t = &g->tetrominoes[i].value;

        for (uint8_t j = 0; j < TILES_IN_TETROMINO; j++) {
            if (!t->tiles[j].present)
                continue;

            const Vec2* tile = &t->tiles[j].value;

            if (tile->y > highest_tetrominoes[tile->x])
                highest_tetrominoes[tile->x] = tile->y;
        }
    }
}

void Game_check_lines(Game* const g) {
    bool any_found = false;

    for (uint8_t y = 0; y < TILES_Y; y++) {
        bool found = true;

        for (uint8_t x = 0; x < TILES_X; x++) {
            bool col_tile_found = false;

            for (uint16_t i = 0; i < tetrominoes_count; i++) {
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
        for (uint16_t i = 0; i < tetrominoes_count; i++)
            if (g->tetrominoes[i].present)
                for (uint8_t j = 0; j < TILES_IN_TETROMINO; j++)
                    if (g->tetrominoes[i].value.tiles[j].present)
                        if (g->tetrominoes[i].value.tiles[j].value.y == y)
                            g->tetrominoes[i].value.tiles[j].present = false;

        // Move all Tetrominoes above the line down
        for (uint16_t i = 0; i < tetrominoes_count; i++)
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
