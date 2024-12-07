#ifndef TETROMINO_H
#define TETROMINO_H

#include "move_state.h"
#include "settings.h"

typedef enum {
    I,
    J,
    L,
    O,
    S,
    T,
    Z,
} TetrominoType;

#define TETROMINO_TYPE_SIZE (Z + 1)

/// Clockwise
typedef enum {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
} Rotation;

#define ROTATION_SIZE (LEFT + 1)

#define TILES_IN_TETROMINO 4

typedef struct {
    OptionalVec2 tiles[TILES_IN_TETROMINO];
    TetrominoType type;
    Rotation rotation;
} Tetromino;

typedef optional(Tetromino) OptionalTetromino;

/// Returns false if game over
bool Tetromino_init(
    Tetromino* const t,
    const uint16_t highest_tetrominoes[],
    const uint16_t tetrominoes_count,
    const Settings* const s
);

void Tetromino_rotate_right(
    Tetromino* const t,
    const OptionalTetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const s
);
void Tetromino_rotate_left(
    Tetromino* const t,
    const OptionalTetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const s
);

void Tetromino_move_right(
    Tetromino* const t,
    const OptionalTetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const s
);
void Tetromino_move_left(
    Tetromino* const t,
    const OptionalTetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const s
);
MoveState Tetromino_move_down(
    Tetromino* const t, uint16_t highest_tetrominoes[], const Settings* const s
);

void Tetrominoes_draw(
    SDL_Renderer* const renderer,
    const Tetromino* const t,
    const OptionalTetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const s
);

#endif
