#ifndef GAME_H
#define GAME_H

#include "assets.h"
#include "tetromino.h"

typedef struct {
    uint16_t score;
    OptionalTetromino* tetrominoes;
} Game;

void Game_init(Game* const g);
void Game_destroy(Game* const g);

void Game_run(Game* g, const Assets* const a, SDL_Renderer* const renderer);

#endif
