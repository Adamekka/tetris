#ifndef SCORE_H
#define SCORE_H

#include "assets.h"

#define SCORE_SIZE 11

/// The last is reserved for the new score and then sorting
typedef uint16_t Score[SCORE_SIZE];

void Score_init(Score s);

void Score_add(Score s, const uint16_t new_score);

void Score_draw(
    const Score s, SDL_Renderer* const renderer, const Assets* const a
);

#endif
