#include "tetromino.h"
#include "consts.h"
#include <assert.h>

uint16_t tetromino_ID_count = 0;

extern uint16_t highest_tetrominoes[TILES_X];

void Tetromino_rotate(Tetromino* const t, const Rotation rotation);

bool Tetromino_init(Tetromino* const t) {
    t->id = tetromino_ID_count++;
    t->rotation = UP;

    const TetrominoType tetromino_type
        = (TetrominoType)rand() % TETROMINO_TYPE_SIZE;
    t->type = tetromino_type;

    // docs/tetrominoes_edited.webp, UP column
    // Tetrominoes are first created in their UP position, then rotated
    switch (tetromino_type) {
        case I: {
            t->tiles[0] = (OptionalVec2){true, 0, 3}; // ....
            t->tiles[1] = (OptionalVec2){true, 1, 3}; // 0123
            t->tiles[2] = (OptionalVec2){true, 2, 3}; // ....
            t->tiles[3] = (OptionalVec2){true, 3, 3}; // ....
            break;
        }

        case J: {
            t->tiles[0] = (OptionalVec2){true, 0, 2}; // 0..
            t->tiles[1] = (OptionalVec2){true, 0, 1}; // 123
            t->tiles[2] = (OptionalVec2){true, 1, 1}; // ...
            t->tiles[3] = (OptionalVec2){true, 2, 1};
            break;
        }

        case L: {
            t->tiles[0] = (OptionalVec2){true, 2, 2}; // ..0
            t->tiles[1] = (OptionalVec2){true, 2, 1}; // 321
            t->tiles[2] = (OptionalVec2){true, 1, 1}; // ...
            t->tiles[3] = (OptionalVec2){true, 0, 1};
            break;
        }

        case O: {
            t->tiles[0] = (OptionalVec2){true, 0, 1}; // 01
            t->tiles[1] = (OptionalVec2){true, 1, 1}; // 23
            t->tiles[2] = (OptionalVec2){true, 0, 0};
            t->tiles[3] = (OptionalVec2){true, 1, 0};
            break;
        }

        case S: {
            t->tiles[0] = (OptionalVec2){true, 2, 2}; // .10
            t->tiles[1] = (OptionalVec2){true, 1, 2}; // 32.
            t->tiles[2] = (OptionalVec2){true, 1, 1}; // ...
            t->tiles[3] = (OptionalVec2){true, 0, 1};
            break;
        }

        case T: {
            t->tiles[0] = (OptionalVec2){true, 1, 2}; // .0.
            t->tiles[1] = (OptionalVec2){true, 0, 1}; // 123
            t->tiles[2] = (OptionalVec2){true, 1, 1}; // ...
            t->tiles[3] = (OptionalVec2){true, 2, 1};
            break;
        }

        case Z: {
            t->tiles[0] = (OptionalVec2){true, 0, 2}; // 01.
            t->tiles[1] = (OptionalVec2){true, 1, 2}; // .23
            t->tiles[2] = (OptionalVec2){true, 1, 1}; // ...
            t->tiles[3] = (OptionalVec2){true, 2, 1};
            break;
        }
    }

    Vec2 offset;
    switch (tetromino_type) {
        case I:
        case O: {
            offset.x = (uint8_t)rand() % (TILES_X - 4);
            offset.y = TILES_Y - 4;
            assert(offset.x < TILES_X - 4);
            assert(offset.x >= 0);
            break;
        }

        case J:
        case L:
        case S:
        case T:
        case Z: {
            offset.x = (uint8_t)rand() % (TILES_X - 3);
            offset.y = TILES_Y - 3;
            assert(offset.x < TILES_X - 3);
            assert(offset.x >= 0);
            break;
        }

        default: assert(false);
    }

    for (uint8_t i = 0; i < TILES_IN_TETROMINO; i++) {
        t->tiles[i].value = Vec2_add(t->tiles[i].value, offset);
        assert(t->tiles[i].value.x >= 0);
        assert(t->tiles[i].value.x < TILES_X);
    }

    const Rotation rotation = (Rotation)rand() % ROTATION_SIZE;
    Tetromino_rotate(t, rotation);

    for (uint8_t i = 0; i < TILES_IN_TETROMINO; i++) {
        Vec2* tile = &t->tiles[i].value;

        if (tile->y - 1 == highest_tetrominoes[tile->x])
            return false;
    }

#ifdef DEBUG
    printf("Tetromino Created\n");
    printf("ID: %u\n", t->id);
    printf("Type: %u\n", t->type);
    printf("Rotation: %u\n", t->rotation);
    printf("Tiles:\n");
    for (uint8_t i = 0; i < TILES_IN_TETROMINO; i++) {
        printf(
            "Tile %u: present=%u, x=%u, y=%u\n",
            i,
            t->tiles[i].present,
            t->tiles[i].value.x,
            t->tiles[i].value.y
        );
    }
#endif

    return true;
}

void Tetromino_rotate_right(Tetromino* const t) {
    const Rotation rotation = (t->rotation + 1) % ROTATION_SIZE;
    assert(rotation < ROTATION_SIZE);
    Tetromino_rotate(t, rotation);
}

void Tetromino_rotate_left(Tetromino* const t) {
    const Rotation rotation = (t->rotation + ROTATION_SIZE - 1) % ROTATION_SIZE;
    assert(rotation >= 0);
    Tetromino_rotate(t, rotation);
}

// docs/tetrominoes_edited.webp
void Tetromino_rotate(Tetromino* const t, const Rotation rotation) {
    switch (t->type) {
        case I: {
            switch (t->rotation) {
                case UP: {
                    switch (rotation) {
                        case UP: break;
                        case RIGHT: {
                            // ....    ..0.
                            // 0123 -> ..1.
                            // ....    ..2.
                            // ....    ..3.
                            t->tiles[0].value.x += 2;
                            t->tiles[0].value.y++;
                            t->tiles[1].value.x++;
                            t->tiles[2].value.y--;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y -= 2;
                            break;
                        }

                        case DOWN: {
                            // ....    ....
                            // 0123 -> ....
                            // ....    0123
                            // ....    ....
                            t->tiles[0].value.y--;
                            t->tiles[1].value.y--;
                            t->tiles[2].value.y--;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case LEFT: {
                            // ....    .0..
                            // 0123 -> .1..
                            // ....    .2..
                            // ....    .3..
                            t->tiles[0].value.x++;
                            t->tiles[0].value.y++;
                            t->tiles[2].value.x--;
                            t->tiles[2].value.y--;
                            t->tiles[3].value.x -= 2;
                            t->tiles[3].value.y -= 2;
                            break;
                        }
                    }
                    break;
                }

                case RIGHT: {
                    switch (rotation) {
                        case UP: {
                            // ..0.    ....
                            // ..1. -> 0123
                            // ..2.    ....
                            // ..3.    ....
                            t->tiles[0].value.x -= 2;
                            t->tiles[0].value.y--;
                            t->tiles[1].value.x--;
                            t->tiles[2].value.y++;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y += 2;
                            break;
                        }

                        case DOWN: {
                            // ..0.    ....
                            // ..1. -> ....
                            // ..2.    0123
                            // ..3.    ....
                            t->tiles[0].value.x -= 2;
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case RIGHT:
                        case LEFT: assert(false); break;
                    }
                    break;
                }

                case DOWN: {
                    switch (rotation) {
                        case RIGHT: {
                            // ....    ..0.
                            // .... -> ..1.
                            // 0123    ..2.
                            // ....    ..3.
                            t->tiles[0].value.x += 2;
                            t->tiles[0].value.y += 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case LEFT: {
                            // ....    .0..
                            // .... -> .1..
                            // 0123    .2..
                            // ....    .3..
                            t->tiles[0].value.x++;
                            t->tiles[0].value.y += 2;
                            t->tiles[1].value.y++;
                            t->tiles[2].value.x--;
                            t->tiles[3].value.x -= 2;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case UP:
                        case DOWN: assert(false); break;
                    }
                    break;
                }

                case LEFT: {
                    switch (rotation) {
                        case UP: {
                            // .0..    ....
                            // .1.. -> 0123
                            // .2..    ....
                            // .3..    ....
                            t->tiles[0].value.x--;
                            t->tiles[0].value.y--;
                            t->tiles[2].value.x++;
                            t->tiles[2].value.y++;
                            t->tiles[3].value.x += 2;
                            t->tiles[3].value.y += 2;
                            break;
                        }

                        case DOWN: {
                            // .0..    ....
                            // .1.. -> ....
                            // .2..    0123
                            // .3..    ....
                            t->tiles[0].value.x--;
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.y--;
                            t->tiles[2].value.x++;
                            t->tiles[3].value.x += 2;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case RIGHT:
                        case LEFT: assert(false); break;
                    }
                    break;
                }
            }
            break;
        }

        case J: {
            switch (t->rotation) {
                case UP: {
                    switch (rotation) {
                        case UP: break;
                        case RIGHT: {
                            // 0..    .10
                            // 123 -> .2.
                            // ...    .3.
                            t->tiles[0].value.x += 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case DOWN: {
                            // 0..    ...
                            // 123 -> 321
                            // ...    ..0
                            t->tiles[0].value.x += 2;
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.x += 2;
                            t->tiles[3].value.x -= 2;
                            break;
                        }

                        case LEFT: {
                            // 0..    .3.
                            // 123 -> .2.
                            // ...    01.
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y++;
                            break;
                        }
                    }
                    break;
                }

                case RIGHT: {
                    switch (rotation) {
                        case UP: {
                            // .10    0..
                            // .2. -> 123
                            // .3.    ...
                            t->tiles[0].value.x -= 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case DOWN: {
                            // .10    ...
                            // .2. -> 321
                            // .3.    ..0
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case RIGHT:
                        case LEFT: assert(false); break;
                    }
                    break;
                }

                case DOWN: {
                    switch (rotation) {
                        case RIGHT: {
                            // ...    .10
                            // 321 -> .2.
                            // ..0    .3.
                            t->tiles[0].value.y += 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case LEFT: {
                            // ...    .3.
                            // 321 -> .2.
                            // ..0    01.
                            t->tiles[0].value.x -= 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case UP:
                        case DOWN: assert(false); break;
                    }
                    break;
                }

                case LEFT: {
                    switch (rotation) {
                        case UP: {
                            // .3.    0..
                            // .2. -> 123
                            // 01.    ...
                            t->tiles[0].value.y += 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case DOWN: {
                            // .3.    ...
                            // .2. -> 321
                            // 01.    ..0
                            t->tiles[0].value.x += 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case RIGHT:
                        case LEFT: assert(false); break;
                    }
                    break;
                }
            }
            break;
        }

        case L: {
            switch (t->rotation) {
                case UP: {
                    switch (rotation) {
                        case UP: break;
                        case RIGHT: {
                            // ..0    .3.
                            // 321 -> .2.
                            // ...    .10
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case DOWN: {
                            // ..0    ...
                            // 321 -> 123
                            // ...    0..
                            t->tiles[0].value.x -= 2;
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.x -= 2;
                            t->tiles[3].value.x += 2;
                            break;
                        }

                        case LEFT: {
                            // ..0    01.
                            // 321 -> .2.
                            // ...    .3.
                            t->tiles[0].value.x -= 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y--;
                            break;
                        }
                    }
                    break;
                }

                case RIGHT: {
                    switch (rotation) {
                        case UP: {
                            // .3.    ..0
                            // .2. -> 321
                            // .10    ...
                            t->tiles[0].value.y += 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case DOWN: {
                            // .3.    ...
                            // .2. -> 123
                            // .10    0..
                            t->tiles[0].value.x -= 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case RIGHT:
                        case LEFT: assert(false); break;
                    }
                    break;
                }

                case DOWN: {
                    switch (rotation) {
                        case RIGHT: {
                            // ...    .3.
                            // 123 -> .2.
                            // 0..    .10
                            t->tiles[0].value.x += 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case LEFT: {
                            // ...    01.
                            // 123 -> .2.
                            // 0..    .3.
                            t->tiles[0].value.y += 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case UP:
                        case DOWN: assert(false); break;
                    }
                    break;
                }

                case LEFT: {
                    switch (rotation) {
                        case UP: {
                            // 01.    ..0
                            // .2. -> 321
                            // .3.    ...
                            t->tiles[0].value.x += 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case DOWN: {
                            // 01.    ...
                            // .2. -> 123
                            // .3.    0..
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case RIGHT:
                        case LEFT: assert(false); break;
                    }
                    break;
                }
            }
            break;
        }

        case O: break;

        case S: {
            switch (t->rotation) {
                case UP: {
                    switch (rotation) {
                        case UP: break;
                        case RIGHT: {
                            // .10    .3.
                            // 32. -> .21
                            // ...    ..0
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case DOWN: {
                            // .10    ...
                            // 32. -> .23
                            // ...    01.
                            t->tiles[0].value.x -= 2;
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.y -= 2;
                            t->tiles[3].value.x += 2;
                            break;
                        }

                        case LEFT: {
                            // .10    0..
                            // 32. -> 12.
                            // ...    .3.
                            t->tiles[0].value.x -= 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y--;
                            break;
                        }
                    }
                    break;
                }

                case RIGHT: {
                    switch (rotation) {
                        case UP: {
                            // .3.    .10
                            // .21 -> 32.
                            // ..0    ...
                            t->tiles[0].value.y += 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case DOWN: {
                            // .3.    ...
                            // .21 -> .23
                            // ..0    01.
                            t->tiles[0].value.x -= 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case RIGHT:
                        case LEFT: assert(false); break;
                    }
                    break;
                }

                case DOWN: {
                    switch (rotation) {
                        case RIGHT: {
                            // ...    .3.
                            // .23 -> .21
                            // 01.    ..0
                            t->tiles[0].value.y += 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case LEFT: {
                            // ...    0..
                            // .23 -> 12.
                            // 01.    .3.
                            t->tiles[0].value.y += 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case UP:
                        case DOWN: assert(false); break;
                    }
                    break;
                }

                case LEFT: {
                    switch (rotation) {
                        case UP: {
                            // 0..    .10
                            // 12. -> 32.
                            // .3.    ...
                            t->tiles[0].value.x += 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case DOWN: {
                            // 0..    ...
                            // 12. -> .23
                            // .3.    01.
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case RIGHT:
                        case LEFT: assert(false); break;
                    }
                    break;
                }
            }
            break;
        }

        case T: {
            switch (t->rotation) {
                case UP: {
                    switch (rotation) {
                        case UP: break;
                        case RIGHT: {
                            // .0.    .1.
                            // 123 -> .20
                            // ...    .3.
                            t->tiles[0].value.x++;
                            t->tiles[0].value.y--;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case DOWN: {
                            // .0.    ...
                            // 123 -> 321
                            // ...    .0.
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.x += 2;
                            t->tiles[3].value.x -= 2;
                            break;
                        }

                        case LEFT: {
                            // .0.    .3.
                            // 123 -> 02.
                            // ...    .1.
                            t->tiles[0].value.x--;
                            t->tiles[0].value.y--;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y++;
                            break;
                        }
                    }
                    break;
                }

                case RIGHT: {
                    switch (rotation) {
                        case UP: {
                            // .1.    .0.
                            // .20 -> 123
                            // .3.    ...
                            t->tiles[0].value.x--;
                            t->tiles[0].value.y++;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case DOWN: {
                            // .1.    ...
                            // .20 -> 321
                            // .3.    .0.
                            t->tiles[0].value.x--;
                            t->tiles[0].value.y--;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case RIGHT:
                        case LEFT: assert(false); break;
                    }
                    break;
                }

                case DOWN: {
                    switch (rotation) {
                        case RIGHT: {
                            // ...    .1.
                            // 321 -> .20
                            // .0.    .3.
                            t->tiles[0].value.x++;
                            t->tiles[0].value.y++;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case LEFT: {
                            // ...    .3.
                            // 321 -> 02.
                            // .0.    .1.
                            t->tiles[0].value.x--;
                            t->tiles[0].value.y++;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case UP:
                        case DOWN: assert(false); break;
                    }
                    break;
                }

                case LEFT: {
                    switch (rotation) {
                        case UP: {
                            // .3.    .0.
                            // 02. -> 123
                            // .1.    ...
                            t->tiles[0].value.x++;
                            t->tiles[0].value.y++;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case DOWN: {
                            // .3.    ...
                            // 02. -> 321
                            // .1.    .0.
                            t->tiles[0].value.x++;
                            t->tiles[0].value.y--;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case RIGHT:
                        case LEFT: assert(false); break;
                    }
                    break;
                }
            }
            break;
        }

        case Z: {
            switch (t->rotation) {
                case UP: {
                    switch (rotation) {
                        case UP: break;
                        case RIGHT: {
                            // 01.    ..0
                            // .23 -> .21
                            // ...    .3.
                            t->tiles[0].value.x += 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case DOWN: {
                            // 01.    ...
                            // .23 -> 32.
                            // ...    .10
                            t->tiles[0].value.x += 2;
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.y -= 2;
                            t->tiles[3].value.x -= 2;
                            break;
                        }

                        case LEFT: {
                            // 01.    .3.
                            // .23 -> 12.
                            // ...    0..
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y++;
                            break;
                        }
                    }
                    break;
                }

                case RIGHT: {
                    switch (rotation) {
                        case UP: {
                            // ..0    01.
                            // .21 -> .23
                            // .3.    ...
                            t->tiles[0].value.x -= 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case DOWN: {
                            // ..0    ...
                            // .21 -> 32.
                            // .3.    .10
                            t->tiles[0].value.y -= 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case RIGHT:
                        case LEFT: assert(false); break;
                    }
                    break;
                }

                case DOWN: {
                    switch (rotation) {
                        case RIGHT: {
                            // ...    ..0
                            // 32. -> .21
                            // .10    .3.
                            t->tiles[0].value.y += 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case LEFT: {
                            // ...    .3.
                            // 32. -> 12.
                            // .10    0..
                            t->tiles[0].value.x -= 2;
                            t->tiles[1].value.x--;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y++;
                            break;
                        }

                        case UP:
                        case DOWN: assert(false); break;
                    }
                    break;
                }

                case LEFT: {
                    switch (rotation) {
                        case UP: {
                            // .3.    01.
                            // 12. -> .23
                            // 0..    ...
                            t->tiles[0].value.y += 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y++;
                            t->tiles[3].value.x++;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case DOWN: {
                            // .3.    ...
                            // 12. -> 32.
                            // 0..    .10
                            t->tiles[0].value.x += 2;
                            t->tiles[1].value.x++;
                            t->tiles[1].value.y--;
                            t->tiles[3].value.x--;
                            t->tiles[3].value.y--;
                            break;
                        }

                        case RIGHT:
                        case LEFT: assert(false); break;
                    }
                    break;
                }
            }
            break;
        }
    }

    t->rotation = rotation;
}

// 0x00FFFF
#define I_COLOR_R 0x00
#define I_COLOR_G 0xFF
#define I_COLOR_B 0xFF

// 0x0000FF
#define J_COLOR_R 0x00
#define J_COLOR_G 0x00
#define J_COLOR_B 0xFF

// 0xFF8800
#define L_COLOR_R 0xFF
#define L_COLOR_G 0x88
#define L_COLOR_B 0x00

// 0xFFFF00
#define O_COLOR_R 0xFF
#define O_COLOR_G 0xFF
#define O_COLOR_B 0x00

// 0x00FF00
#define S_COLOR_R 0x00
#define S_COLOR_G 0xFF
#define S_COLOR_B 0x00

// 0x880088
#define T_COLOR_R 0x88
#define T_COLOR_G 0x00
#define T_COLOR_B 0x88

// 0xFF0000
#define Z_COLOR_R 0xFF
#define Z_COLOR_G 0x00
#define Z_COLOR_B 0x00

extern uint8_t tetrominoes_count;

void Tetromino_draw(SDL_Renderer* const renderer, const Tetromino* t) {
    switch (t->type) {
        case I: {
            SDL_SetRenderDrawColor(
                renderer, I_COLOR_R, I_COLOR_G, I_COLOR_B, 255
            );
            break;
        }

        case J: {
            SDL_SetRenderDrawColor(
                renderer, J_COLOR_R, J_COLOR_G, J_COLOR_B, 255
            );
            break;
        }

        case L: {
            SDL_SetRenderDrawColor(
                renderer, L_COLOR_R, L_COLOR_G, L_COLOR_B, 255
            );
            break;
        }

        case O: {
            SDL_SetRenderDrawColor(
                renderer, O_COLOR_R, O_COLOR_G, O_COLOR_B, 255
            );
            break;
        }

        case S: {
            SDL_SetRenderDrawColor(
                renderer, S_COLOR_R, S_COLOR_G, S_COLOR_B, 255
            );
            break;
        }

        case T: {
            SDL_SetRenderDrawColor(
                renderer, T_COLOR_R, T_COLOR_G, T_COLOR_B, 255
            );
            break;
        }

        case Z: {
            SDL_SetRenderDrawColor(
                renderer, Z_COLOR_R, Z_COLOR_G, Z_COLOR_B, 255
            );
            break;
        }

        default: assert(false); break;
    }

    for (uint8_t i = 0; i < TILES_IN_TETROMINO; i++) {
        if (t->tiles[i].present) {
            const SDL_Rect rect = {
              t->tiles[i].value.x * (TILE_SIZE + TILE_OFFSET) + LEFT_PADDING,
              (TILES_Y - t->tiles[i].value.y) * (TILE_SIZE + TILE_OFFSET)
                  + TOP_PADDING,
              TILE_SIZE,
              TILE_SIZE
            };

            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void Tetrominoes_draw(
    SDL_Renderer* const renderer,
    const Tetromino* const t,
    const OptionalTetromino ts[]
) {
    Tetromino_draw(renderer, t);

    for (uint8_t i = 0; i < tetrominoes_count; i++) {
        const OptionalTetromino* const t = &ts[i];

        if (t->present)
            Tetromino_draw(renderer, &t->value);
    }
}
