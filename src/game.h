#ifndef GAME_H
#define GAME_H

#include "tetromino.h"

typedef struct {
    uint16_t score;
    OptionalTetromino* tetrominoes;
} Game;

void Game_run(Game* const g, SDL_Renderer* const renderer);

#endif
