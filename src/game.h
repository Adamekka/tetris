#ifndef GAME_H
#define GAME_H

#include "tetromino.h"

typedef struct {
    uint16_t score;
    Option_Tetromino* tetrominoes;
    uint16_t tetrominoes_allocated;
    uint16_t tetrominoes_count;
    // Cache the highest Tetromino in each column
    uint16_t* highest_tetrominoes;
} Game;

void Game_init(Game* const g, const Settings* const s);
void Game_destroy(Game* const g);

void Game_run(
    Game* g,
    const Assets* const a,
    const Settings* s,
    SDL_Renderer* const renderer
);

#endif
