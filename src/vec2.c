#include "vec2.h"

Vec2 Vec2_add(const Vec2 a, const Vec2 b) {
    return (Vec2){a.x + b.x, a.y + b.y};
}

bool Vec2_eq(const Vec2 a, const Vec2 b) { return a.x == b.x && a.y == b.y; }
