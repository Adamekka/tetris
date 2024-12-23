#ifndef VEC2_H
#define VEC2_H

#include "option.h"
#include <stdint.h>

typedef struct {
    uint8_t x, y;
} Vec2;

typedef Option(Vec2) Option_Vec2;

Vec2 Vec2_add(const Vec2 a, const Vec2 b);

bool Vec2_eq(const Vec2 a, const Vec2 b);

#endif
