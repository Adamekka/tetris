#ifndef TETROMINO_H
#define TETROMINO_H

#include "move_state.h"
#include "rotation.h"
#include "settings.h"
#include "tetromino_type.h"

#define TILES_IN_TETROMINO 4

typedef struct {
    Option_Vec2 tiles[TILES_IN_TETROMINO];
    TetrominoType type;
    Rotation rotation;
} Tetromino;

typedef Option(Tetromino) Option_Tetromino;

/// Returns false if game over
bool Tetromino_init(
    Tetromino* const t,
    const Option_Tetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const s
);

void Tetromino_rotate_right(
    Tetromino* const t,
    const Option_Tetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const s
);
void Tetromino_rotate_left(
    Tetromino* const t,
    const Option_Tetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const s
);

void Tetromino_move_right(
    Tetromino* const t,
    const Option_Tetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const s
);
void Tetromino_move_left(
    Tetromino* const t,
    const Option_Tetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const s
);
MoveState Tetromino_move_down(
    Tetromino* const t, uint16_t highest_tetrominoes[], const Settings* const s
);

void Tetrominoes_draw(
    SDL_Renderer* const renderer,
    const Tetromino* const t,
    const Option_Tetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const s
);

#endif
