#include "settings.h"
#include "button.h"
#include "consts.h"
#include <assert.h>

#define TILES_X_DEFAULT 10
#define TILES_X_MIN 6
#define TILES_X_MAX 13

#define TILES_Y_DEFAULT 16
#define TILES_Y_MIN 8
#define TILES_Y_MAX 16

#define TILE_SIZE_DEFAULT 32
#define TILE_SIZE_MIN 1
#define TILE_SIZE_MAX 32

#define TILE_OFFSET_DEFAULT 4
#define TILE_OFFSET_MIN 1
#define TILE_OFFSET_MAX 4

#define SPEED_DEFAULT 5
#define SPEED_MIN 1
#define SPEED_MAX UINT8_MAX

typedef enum {
    TILES_X = 0,
    TILES_Y = 1,
    TILE_SIZE = 2,
    TILE_OFFSET = 3,
    SPEED = 4,
    BACK = 5,
} SettingsOption;

#define SETTINGS_OPTIONS (BACK + 1)

void Settings_next_option(SettingsOption* const selected);
void Settings_previous_option(SettingsOption* const selected);
void Settings_increase(Settings* const s, const SettingsOption selected);
void Settings_decrease(Settings* const s, const SettingsOption selected);

void Settings_draw(
    const Settings* const s,
    SDL_Renderer* const renderer,
    const Assets* const assets,
    const SettingsOption selected
);

void Settings_init(Settings* s) {
    s->tiles = (Vec2){TILES_X_DEFAULT, TILES_Y_DEFAULT};
    s->tile_size = TILE_SIZE_DEFAULT;
    s->tile_offset = TILE_OFFSET_DEFAULT;
    s->speed = SPEED_DEFAULT;
}

void Settings_run(
    Settings* const s, SDL_Renderer* const renderer, const Assets* const assets
) {
    SDL_Event event;
    SettingsOption selected = 0;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    if (event.type == SDL_QUIT
                        || event.key.keysym.sym == SDLK_q)
                        running = false;
                    else if (event.key.keysym.sym == SDLK_w
                             || event.key.keysym.sym == SDLK_UP)
                        Settings_previous_option(&selected);
                    else if (event.key.keysym.sym == SDLK_s
                             || event.key.keysym.sym == SDLK_DOWN)
                        Settings_next_option(&selected);
                    else if (event.key.keysym.sym == SDLK_a
                             || event.key.keysym.sym == SDLK_LEFT)
                        Settings_decrease(s, selected);
                    else if (event.key.keysym.sym == SDLK_d
                             || event.key.keysym.sym == SDLK_RIGHT)
                        Settings_increase(s, selected);
                    else if (event.key.keysym.sym == SDLK_RETURN)
                        if (selected == BACK) {
                            running = false;
                            break;
                        }
                }
            }
        }

        Settings_draw(s, renderer, assets, selected);
        SDL_RenderPresent(renderer);
    }
}

void Settings_next_option(SettingsOption* const selected) {
    *selected = (*selected + 1) % SETTINGS_OPTIONS;
}

void Settings_previous_option(SettingsOption* const selected) {
    *selected = (*selected + SETTINGS_OPTIONS - 1) % SETTINGS_OPTIONS;
}

void Settings_increase(Settings* const s, const SettingsOption selected) {
    switch (selected) {
        case TILES_X: {
            if (s->tiles.x < TILES_X_MAX)
                s->tiles.x++;
            break;
        }

        case TILES_Y: {
            if (s->tiles.y < TILES_Y_MAX)
                s->tiles.y++;
            break;
        }

        case TILE_SIZE: {
            if (s->tile_size < TILE_SIZE_MAX)
                s->tile_size++;
            break;
        }

        case TILE_OFFSET: {
            if (s->tile_offset < TILE_OFFSET_MAX)
                s->tile_offset++;
            break;
        }

        case SPEED: {
            if (s->speed < SPEED_MAX)
                s->speed++;
            break;
        }

        default: assert(false);
    }
}

void Settings_decrease(Settings* const s, const SettingsOption selected) {
    switch (selected) {
        case TILES_X: {
            if (s->tiles.x > TILES_X_MIN)
                s->tiles.x--;
            break;
        }

        case TILES_Y: {
            if (s->tiles.y > TILES_Y_MIN)
                s->tiles.y--;
            break;
        }

        case TILE_SIZE: {
            if (s->tile_size > TILE_SIZE_MIN)
                s->tile_size--;
            break;
        }

        case TILE_OFFSET: {
            if (s->tile_offset > TILE_OFFSET_MIN)
                s->tile_offset--;
            break;
        }

        case SPEED: {
            if (s->speed > SPEED_MIN)
                s->speed--;
            break;
        }

        default: assert(false);
    }
}

#define SETTINGS_TOP_PADDING                                                   \
    (WINDOW_HEIGHT / 2 - BUTTON_HEIGHT * SETTINGS_OPTIONS + 75)

#define SETTINGS_BUTTON_PADDING 20

void Settings_draw(
    const Settings* const s,
    SDL_Renderer* const renderer,
    const Assets* const assets,
    const SettingsOption selected
) {
    // Background
    const Color settings_bg = Color_init(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B);

    SDL_SetRenderDrawColor(renderer, settings_bg);
    SDL_RenderClear(renderer);

    // Text
    const Rect tiles_x_rect = {
      WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
      SETTINGS_TOP_PADDING,
      BUTTON_WIDTH,
      BUTTON_HEIGHT
    };

    const Rect tiles_y_rect = {
      WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
      SETTINGS_TOP_PADDING + BUTTON_HEIGHT + SETTINGS_BUTTON_PADDING,
      BUTTON_WIDTH,
      BUTTON_HEIGHT
    };

    const Rect tile_size_rect = {
      WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
      SETTINGS_TOP_PADDING + BUTTON_HEIGHT * 2 + SETTINGS_BUTTON_PADDING * 2,
      BUTTON_WIDTH,
      BUTTON_HEIGHT
    };

    const Rect tile_offset_rect = {
      WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
      SETTINGS_TOP_PADDING + BUTTON_HEIGHT * 3 + SETTINGS_BUTTON_PADDING * 3,
      BUTTON_WIDTH,
      BUTTON_HEIGHT
    };

    const Rect speed_rect = {
      WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
      SETTINGS_TOP_PADDING + BUTTON_HEIGHT * 4 + SETTINGS_BUTTON_PADDING * 4,
      BUTTON_WIDTH,
      BUTTON_HEIGHT
    };

    const Rect back_rect = {
      WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
      SETTINGS_TOP_PADDING + BUTTON_HEIGHT * 6 + SETTINGS_BUTTON_PADDING * 6,
      BUTTON_WIDTH,
      BUTTON_HEIGHT
    };

    const Color bg = Color_init(BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B);

    const Color selected_bg = Color_init(
        BUTTON_SELECTED_COLOR_R,
        BUTTON_SELECTED_COLOR_G,
        BUTTON_SELECTED_COLOR_B
    );

    const Color text_color = Color_init(255, 255, 255);

    Button tiles_x_button;
    char tiles_x_str[sizeof("Tiles X: ") + UINT8_MAX_DIGITS];
    snprintf(tiles_x_str, sizeof(tiles_x_str), "Tiles X: %u", s->tiles.x);
    Button_init(
        &tiles_x_button, tiles_x_str, tiles_x_rect, bg, selected_bg, text_color
    );
    Button_draw(&tiles_x_button, renderer, assets, selected == TILES_X);

    Button tiles_y_button;
    char tiles_y_str[sizeof("Tiles Y: ") + UINT8_MAX_DIGITS];
    snprintf(tiles_y_str, sizeof(tiles_y_str), "Tiles Y: %u", s->tiles.y);
    Button_init(
        &tiles_y_button, tiles_y_str, tiles_y_rect, bg, selected_bg, text_color
    );
    Button_draw(&tiles_y_button, renderer, assets, selected == TILES_Y);

    Button tile_size_button;
    char tile_size_str[sizeof("Tile size: ") + UINT16_MAX_DIGITS];
    snprintf(
        tile_size_str, sizeof(tile_size_str), "Tile size: %u", s->tile_size
    );
    Button_init(
        &tile_size_button,
        tile_size_str,
        tile_size_rect,
        bg,
        selected_bg,
        text_color
    );
    Button_draw(&tile_size_button, renderer, assets, selected == TILE_SIZE);

    Button tile_offset_button;
    char tile_offset_str[sizeof("Tile offset: ") + UINT16_MAX_DIGITS];
    snprintf(
        tile_offset_str,
        sizeof(tile_offset_str),
        "Tile offset: %u",
        s->tile_offset
    );
    Button_init(
        &tile_offset_button,
        tile_offset_str,
        tile_offset_rect,
        bg,
        selected_bg,
        text_color
    );
    Button_draw(&tile_offset_button, renderer, assets, selected == TILE_OFFSET);

    Button speed_button;
    char speed_str[sizeof("Speed: ") + UINT8_MAX_DIGITS];
    snprintf(speed_str, sizeof(speed_str), "Speed: %u", s->speed);
    Button_init(
        &speed_button, speed_str, speed_rect, bg, selected_bg, text_color
    );
    Button_draw(&speed_button, renderer, assets, selected == SPEED);

    Button back_button;
    Button_init(&back_button, "Back", back_rect, bg, selected_bg, text_color);
    Button_draw(&back_button, renderer, assets, selected == BACK);

    Rect text_rect = {150, WINDOW_HEIGHT / 4, 0, 0};

    Text hint;
    Text_init(
        &hint,
        "WASD or arrows to navigate, changing values may break UI",
        text_rect,
        Color_to_SDL_Color(text_color),
        (Option_uint16){1, 250}
    );
    Text_draw(&hint, renderer, assets);
}
