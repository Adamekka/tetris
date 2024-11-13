#ifndef GAME_H
#define GAME_H

#include "tetromino.h"

typedef struct {
    uint16_t score;
    OptionalTetromino* tetrominoes;
} Game;

void Game_init(Game* const g);
void Game_destroy(Game* const g);

void Game_tetromino_push(Game* const g, const Tetromino t);
void Game_update_highest_tetrominoes(const Game* const g);
void Game_check_lines(Game* const g);

#endif
