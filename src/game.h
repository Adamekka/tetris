#ifndef GAME_H
#define GAME_H

#include "assets.h"
#include "tetromino.h"

typedef struct {
    uint16_t score;
    OptionalTetromino* tetrominoes;
} Game;

void Game_run(Game* g, Assets* a, SDL_Renderer* const renderer);

#endif
