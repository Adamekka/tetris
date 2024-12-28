#ifndef GAME_H
#define GAME_H

#include "score.h"
#include "tetromino.h"

typedef struct {
    uint16_t score;
    Option_Tetromino* tetrominoes;
    uint16_t tetrominoes_allocated;
    uint16_t tetrominoes_count;
    // Cache the highest Tetromino in each column
    uint16_t* highest_tetrominoes;
} Game;

void Game_run(
    Game* g,
    Score score,
    const Assets* const assets,
    const Settings* settings,
    SDL_Renderer* const renderer
);

#endif
