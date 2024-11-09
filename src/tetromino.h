#ifndef TETROMINO_H
#define TETROMINO_H

#include "vec2.h"
#include <SDL2/SDL.h>

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
    uint16_t id;
    OptionalVec2 tiles[TILES_IN_TETROMINO];
    TetrominoType type;
    Rotation rotation;
} Tetromino;

typedef optional(Tetromino) OptionalTetromino;

/// Returns false if game over
bool Tetromino_init(Tetromino* const t);

void Tetromino_rotate_right(Tetromino* const t);
void Tetromino_rotate_left(Tetromino* const t);

/// First Tetromino is the one that is currently moving, the array is the rest
void Tetrominoes_draw(
    SDL_Renderer* const renderer,
    const Tetromino* const t,
    const OptionalTetromino ts[]
);

#endif
