#include "button.h"
#include "consts.h"
#include "game.h"

typedef enum {
    PLAY = 0,
    SETTINGS = 1,
    QUIT = 2,
} MainMenuOption;

#define MAIN_MENU_OPTIONS (QUIT + 1)

void MainMenu_next_option(MainMenuOption* const selected);
void MainMenu_previous_option(MainMenuOption* const selected);

void MainMenu_draw(
    SDL_Renderer* const renderer,
    const Assets* const assets,
    const MainMenuOption selected
);

void MainMenu_run(
    SDL_Renderer* const renderer,
    Score score,
    const Assets* const assets,
    Settings* const settings
) {
    SDL_Event event;
    MainMenuOption selected = PLAY;
    bool running = true;

main_menu_start:
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    if (event.type == SDL_QUIT
                        || event.key.keysym.sym == SDLK_q)
                        return;
                    else if (event.key.keysym.sym == SDLK_w
                             || event.key.keysym.sym == SDLK_UP)
                        MainMenu_previous_option(&selected);
                    else if (event.key.keysym.sym == SDLK_s
                             || event.key.keysym.sym == SDLK_DOWN)
                        MainMenu_next_option(&selected);
                    else if (event.key.keysym.sym == SDLK_RETURN) {
                        if (selected == QUIT)
                            return;

                        running = false;
                        break;
                    }
                }
            }
        }

        MainMenu_draw(renderer, assets, selected);
        SDL_RenderPresent(renderer);
    }

    switch (selected) {
        case PLAY: {
            Game game;
            Game_run(&game, score, assets, settings, renderer);
            running = true;
            goto main_menu_start;
            break;
        }

        case SETTINGS: {
            Settings_run(settings, renderer, assets);
            running = true;
            goto main_menu_start;
            break;
        }

        case QUIT: {
            return;
            break;
        }
    }
}

void MainMenu_next_option(MainMenuOption* const selected) {
    *selected = (*selected + 1) % MAIN_MENU_OPTIONS;
}

void MainMenu_previous_option(MainMenuOption* const selected) {
    *selected = (*selected + MAIN_MENU_OPTIONS - 1) % MAIN_MENU_OPTIONS;
}

#define MAIN_MENU_TOP_PADDING                                                  \
    (WINDOW_HEIGHT / 2 - BUTTON_HEIGHT * (MAIN_MENU_OPTIONS - 1))

void MainMenu_draw(
    SDL_Renderer* const renderer,
    const Assets* const assets,
    const MainMenuOption selected
) {
    // Background
    const Color main_menu_bg = Color_init(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B);

    SDL_SetRenderDrawColor(renderer, main_menu_bg);
    SDL_RenderClear(renderer);

    // Text
    const Rect tetris_rect
        = {WINDOW_WIDTH / 2, MAIN_MENU_TOP_PADDING - BUTTON_HEIGHT * 2, 0, 0};

    const Rect hint_rect
        = {WINDOW_WIDTH / 2, WINDOW_HEIGHT - BUTTON_HEIGHT, 0, 0};

    const Color text_color = Color_init(255, 255, 255);

    Text tetris_text;
    Text_init(
        &tetris_text,
        "Tetris",
        tetris_rect,
        (SDL_Color){255, 255, 255, 255},
        (Option_uint16){0}
    );
    Text_draw(&tetris_text, renderer, assets);

    Text hint_text;
    Text_init(
        &hint_text,
        "W/S or UP/DOWN to navigate, ENTER to select, Q to quit.",
        hint_rect,
        (SDL_Color){255, 255, 255, 255},
        (Option_uint16){0}
    );
    Text_draw(&hint_text, renderer, assets);

    // Buttons
    const Rect play_rect = {
      WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
      MAIN_MENU_TOP_PADDING,
      BUTTON_WIDTH,
      BUTTON_HEIGHT
    };

    const Rect settings_rect = {
      WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
      MAIN_MENU_TOP_PADDING + BUTTON_HEIGHT * 2,
      BUTTON_WIDTH,
      BUTTON_HEIGHT
    };

    const Rect quit_rect = {
      WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
      MAIN_MENU_TOP_PADDING + BUTTON_HEIGHT * 4,
      BUTTON_WIDTH,
      BUTTON_HEIGHT
    };

    const Color bg = Color_init(BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B);

    const Color selected_bg = Color_init(
        BUTTON_SELECTED_COLOR_R,
        BUTTON_SELECTED_COLOR_G,
        BUTTON_SELECTED_COLOR_B
    );

    Button play_button;
    Button_init(&play_button, "Play", play_rect, bg, selected_bg, text_color);
    Button_draw(&play_button, renderer, assets, selected == PLAY);

    Button settings_button;
    Button_init(
        &settings_button, "Settings", settings_rect, bg, selected_bg, text_color
    );
    Button_draw(&settings_button, renderer, assets, selected == SETTINGS);

    Button quit_button;
    Button_init(&quit_button, "Quit", quit_rect, bg, selected_bg, text_color);
    Button_draw(&quit_button, renderer, assets, selected == QUIT);
}
