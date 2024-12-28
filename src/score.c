#include "score.h"
#include "consts.h"
#include "text.h"
#include <assert.h>

void Score_init(Score s) {
    FILE* file = fopen("score", "r");

    if (file == NULL) {
        // File does not exist
        for (uint8_t i = 0; i < SCORE_SIZE; i++)
            s[i] = 0;

        fclose(file);
        return;
    }

    char input[(SCORE_SIZE - 1) * (UINT16_MAX_DIGITS + 1)];
    fgets(input, sizeof(input), file);
    fclose(file);

    s[0] = (uint16_t)atoi(strtok(input, ";"));
    s[10] = 0; // Reserve the last for the new score

    for (uint8_t i = 1; i < (SCORE_SIZE - 1); i++)
        s[i] = (uint16_t)atoi(strtok(NULL, ";"));

    assert(strtok(NULL, ";") == NULL);
}

int32_t cmp(const void* a, const void* b) {
    return *(int16_t*)b - *(int16_t*)a;
}

void Score_add(Score s, uint16_t new_score) {
    s[10] = new_score;

    qsort(s, SCORE_SIZE, sizeof(*s), cmp);

    FILE* file = fopen("score", "w");
    assert(file != NULL);

    fprintf(
        file,
        "%hu;%hu;%hu;%hu;%hu;%hu;%hu;%hu;%hu;%hu\n",
        s[0],
        s[1],
        s[2],
        s[3],
        s[4],
        s[5],
        s[6],
        s[7],
        s[8],
        s[9]
    );

    fclose(file);
}

#define SCORE_HEIGHT 30

void Score_draw(
    const Score s, SDL_Renderer* const renderer, const Assets* const assets
) {
    const int32_t lpad = WINDOW_HEIGHT;

    char* score_title = "High scores";
    Text title;
    Text_init(
        &title,
        score_title,
        (Rect){lpad, SCORE_HEIGHT * 4, 0, 0},
        (SDL_Color){255, 255, 255, 255},
        (Option_uint16){0}
    );
    Text_draw(&title, renderer, assets);

    for (uint8_t i = 0; i < (SCORE_SIZE - 1); i++) {
        char score_text[sizeof("1. ") + UINT16_MAX_DIGITS];
        snprintf(score_text, sizeof(score_text), "%hu. %hu", i + 1, s[i]);

        Text score;
        Text_init(
            &score,
            score_text,
            (Rect){lpad, (SCORE_HEIGHT) * (i + 6), 0, 0},
            (SDL_Color){255, 255, 255, 255},
            (Option_uint16){0}
        );
        Text_draw(&score, renderer, assets);
    }
}
