#ifndef GAME_H
#define GAME_H

#include "move_state.h"
#include "tetromino.h"

typedef struct {
    uint16_t score;
    OptionalTetromino* tetrominoes;
} Game;

void Game_init(Game* const g);
void Game_destroy(Game* const g);

MoveState Game_tetromino_move_down(const Game* const g, Tetromino* const t);

void Game_tetromino_push(Game* const g, const Tetromino t);
void Game_tetromino_pop(const Game* const g, const uint16_t id);

#endif
