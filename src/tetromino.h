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
    uint8_t offset;
} Tetromino;

typedef Option(Tetromino) Option_Tetromino;

void Tetromino_init(
    Tetromino* const t,
    const uint16_t tetrominoes_count,
    const Settings* const settings
);

bool Tetromino_can_move(
    const Option_Vec2 new_pos[TILES_IN_TETROMINO],
    const Option_Tetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const settings
);

void Tetromino_rotate_right(
    Tetromino* const t,
    const Option_Tetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const settings
);
void Tetromino_rotate_left(
    Tetromino* const t,
    const Option_Tetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const settings
);

void Tetromino_move_right(
    Tetromino* const t,
    const Option_Tetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const settings
);
void Tetromino_move_left(
    Tetromino* const t,
    const Option_Tetromino other[],
    const uint16_t tetrominoes_count,
    const Settings* const settings
);
MoveState Tetromino_move_down(
    Tetromino* const t, uint16_t highest_tetrominoes[], const Settings* const settings
);

void Tetrominoes_draw(
    SDL_Renderer* const renderer,
    const Tetromino* const tetromino,
    const Tetromino* const tetromino_next,
    const Option_Tetromino other[],
    const uint16_t tetrominoes_count,
    const Assets* const assets,
    const Settings* const settings
);

#endif
