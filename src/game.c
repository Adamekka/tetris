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

MoveState Game_tetromino_move_down(const Game* const g, Tetromino* const t) {
    // Check Tetromino can move down
    for (uint8_t i = 0; i < TILES_IN_TETROMINO; i++) {
        const Vec2* tile = &t->tiles[i].value;
#ifdef DEBUG
        printf("tile->x: %d\n", tile->x);
        printf("tile->y: %d\n", tile->y);
#endif
        assert(tile->x >= 0);
        assert(tile->x < TILES_X);
        assert(tile->y >= 0);

        if (tile->y > TILES_Y)
            return GAME_OVER;

        if (tile->y - 1 == highest_tetrominoes[tile->x])
            return STOP;
    }

    // Move Tetromino down
    for (uint8_t i = 0; i < TILES_IN_TETROMINO; i++)
        t->tiles[i].value.y--;

    return MOVE;
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
        tetrominoes_allocated *= 1.5;

        g->tetrominoes = realloc(
            g->tetrominoes, sizeof(*g->tetrominoes) * tetrominoes_allocated
        );
    }

    g->tetrominoes[tetrominoes_count++] = (OptionalTetromino){true, t};

    Game_update_highest_tetrominoes(g);
}

void Game_tetromino_pop(const Game* const g, const uint16_t id) {
    for (uint16_t i = 0; i < tetrominoes_count; i++)
        if (g->tetrominoes[i].value.id == id)
            g->tetrominoes[i].present = false;

    Game_update_highest_tetrominoes(g);
}

void Game_update_highest_tetrominoes(const Game* const g) {
    for (uint16_t i = 0; i < TILES_X; i++)
        highest_tetrominoes[i] = 0;

    for (uint16_t i = 0; i < tetrominoes_count; i++) {
        if (!g->tetrominoes[i].present)
            continue;

        for (uint8_t j = 0; j < TILES_IN_TETROMINO; j++) {
            const Vec2* tile = &g->tetrominoes[i].value.tiles[j].value;

            if (tile->y > highest_tetrominoes[tile->x])
                highest_tetrominoes[tile->x] = tile->y;
        }
    }
}
