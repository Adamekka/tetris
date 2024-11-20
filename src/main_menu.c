#include "consts.h"
#include "game.h"
#include <assert.h>

typedef enum {
    PLAY_SELECTED = 0,
    SETTINGS_SELECTED = 1,
    QUIT_SELECTED = 2,
    PLAY,
    SETTINGS,
} MainMenuOption;

#define MAIN_MENU_OPTIONS (QUIT_SELECTED + 1)

void MainMenu_next_option(MainMenuOption* const selected);
void MainMenu_previous_option(MainMenuOption* const selected);

void MainMenu_draw(
    SDL_Renderer* const renderer,
    const Assets* const assets,
    const MainMenuOption selected
);

void MainMenu_run(SDL_Renderer* const renderer, const Assets* const assets) {
    SDL_Event event;
    MainMenuOption selected = PLAY_SELECTED;
    bool running = true;

main_menu_start:
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    if (event.type == SDL_QUIT
                        || event.key.keysym.sym == SDLK_q)
                        running = false;
                    else if (event.key.keysym.sym == SDLK_w
                             || event.key.keysym.sym == SDLK_UP)
                        MainMenu_previous_option(&selected);
                    else if (event.key.keysym.sym == SDLK_s
                             || event.key.keysym.sym == SDLK_DOWN)
                        MainMenu_next_option(&selected);
                    else if (event.key.keysym.sym == SDLK_RETURN) {
                        switch (selected) {
                            case PLAY_SELECTED: {
                                selected = PLAY;
                                running = false;
                                break;
                            }

                            case SETTINGS_SELECTED: {
                                selected = SETTINGS;
                                running = false;
                                break;
                            }

                            case QUIT_SELECTED: {
                                return;
                                break;
                            }

                            default: assert(false); break;
                        }
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
            Game_run(&game, assets, renderer);
            selected = PLAY_SELECTED;
            running = true;
            goto main_menu_start;
            break;
        }

        case SETTINGS: {
            // TODO
            selected = SETTINGS_SELECTED;
            running = true;
            goto main_menu_start;
            break;
        }

        default: assert(false); break;
    }
}

void MainMenu_next_option(MainMenuOption* const selected) {
    *selected = (*selected + 1) % MAIN_MENU_OPTIONS;
}

void MainMenu_previous_option(MainMenuOption* const selected) {
    *selected = (*selected + MAIN_MENU_OPTIONS - 1) % MAIN_MENU_OPTIONS;
}

// 0x000069
#define MAIN_MENU_BG_COLOR_R 0
#define MAIN_MENU_BG_COLOR_G 0
#define MAIN_MENU_BG_COLOR_B 69

// 0x0000AA
#define MAIN_MENU_BUTTON_COLOR_R 0
#define MAIN_MENU_BUTTON_COLOR_G 0
#define MAIN_MENU_BUTTON_COLOR_B 0xAA

// 0x0000FF
#define MAIN_MENU_BUTTON_SELECTED_COLOR_R 0
#define MAIN_MENU_BUTTON_SELECTED_COLOR_G 0
#define MAIN_MENU_BUTTON_SELECTED_COLOR_B 0xFF

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50

#define MAIN_MENU_TOP_PADDING                                                  \
    (WINDOW_HEIGHT / 2 - BUTTON_HEIGHT * (MAIN_MENU_OPTIONS - 1))

void MainMenu_draw(
    SDL_Renderer* const renderer,
    const Assets* const assets,
    const MainMenuOption selected
) {
    SDL_SetRenderDrawColor(
        renderer,
        MAIN_MENU_BG_COLOR_R,
        MAIN_MENU_BG_COLOR_G,
        MAIN_MENU_BG_COLOR_B,
        255
    );

    SDL_RenderClear(renderer);

    const SDL_Rect play_button = {
      WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
      MAIN_MENU_TOP_PADDING,
      BUTTON_WIDTH,
      BUTTON_HEIGHT
    };

    const SDL_Rect settings_button = {
      WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
      MAIN_MENU_TOP_PADDING + BUTTON_HEIGHT * 2,
      BUTTON_WIDTH,
      BUTTON_HEIGHT
    };

    const SDL_Rect quit_button = {
      WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
      MAIN_MENU_TOP_PADDING + BUTTON_HEIGHT * 4,
      BUTTON_WIDTH,
      BUTTON_HEIGHT
    };

    switch (selected) {
        case PLAY_SELECTED: {
            SDL_SetRenderDrawColor(
                renderer,
                MAIN_MENU_BUTTON_SELECTED_COLOR_R,
                MAIN_MENU_BUTTON_SELECTED_COLOR_G,
                MAIN_MENU_BUTTON_SELECTED_COLOR_B,
                255
            );

            SDL_RenderFillRect(renderer, &play_button);

            SDL_SetRenderDrawColor(
                renderer,
                MAIN_MENU_BUTTON_COLOR_R,
                MAIN_MENU_BUTTON_COLOR_G,
                MAIN_MENU_BUTTON_COLOR_B,
                255
            );

            SDL_RenderFillRect(renderer, &settings_button);
            SDL_RenderFillRect(renderer, &quit_button);
            break;
        }

        case SETTINGS_SELECTED: {
            SDL_SetRenderDrawColor(
                renderer,
                MAIN_MENU_BUTTON_SELECTED_COLOR_R,
                MAIN_MENU_BUTTON_SELECTED_COLOR_G,
                MAIN_MENU_BUTTON_SELECTED_COLOR_B,
                255
            );

            SDL_RenderFillRect(renderer, &settings_button);

            SDL_SetRenderDrawColor(
                renderer,
                MAIN_MENU_BUTTON_COLOR_R,
                MAIN_MENU_BUTTON_COLOR_G,
                MAIN_MENU_BUTTON_COLOR_B,
                255
            );

            SDL_RenderFillRect(renderer, &play_button);
            SDL_RenderFillRect(renderer, &quit_button);
            break;
        }

        case QUIT_SELECTED: {
            SDL_SetRenderDrawColor(
                renderer,
                MAIN_MENU_BUTTON_SELECTED_COLOR_R,
                MAIN_MENU_BUTTON_SELECTED_COLOR_G,
                MAIN_MENU_BUTTON_SELECTED_COLOR_B,
                255
            );

            SDL_RenderFillRect(renderer, &quit_button);

            SDL_SetRenderDrawColor(
                renderer,
                MAIN_MENU_BUTTON_COLOR_R,
                MAIN_MENU_BUTTON_COLOR_G,
                MAIN_MENU_BUTTON_COLOR_B,
                255
            );

            SDL_RenderFillRect(renderer, &play_button);
            SDL_RenderFillRect(renderer, &settings_button);
            break;
        }

        default: assert(selected == PLAY || selected == SETTINGS); break;
    }

    const char* tetris = "Tetris";
    const char* play = "Play";
    const char* settings = "Settings";
    const char* quit = "Quit";
    const char* hint
        = "W/S or UP/DOWN to navigate, ENTER to select, Q to quit.";

    SDL_Surface* tetris_surface = TTF_RenderText_Blended(
        assets->font, tetris, (SDL_Color){255, 255, 255, 255}
    );

    SDL_Surface* play_surface = TTF_RenderText_Blended(
        assets->font, play, (SDL_Color){255, 255, 255, 255}
    );

    SDL_Surface* settings_surface = TTF_RenderText_Blended(
        assets->font, settings, (SDL_Color){255, 255, 255, 255}
    );

    SDL_Surface* quit_surface = TTF_RenderText_Blended(
        assets->font, quit, (SDL_Color){255, 255, 255, 255}
    );

    SDL_Surface* hint_surface = TTF_RenderText_Blended(
        assets->font, hint, (SDL_Color){255, 255, 255, 255}
    );

    SDL_Texture* tetris_texture
        = SDL_CreateTextureFromSurface(renderer, tetris_surface);
    SDL_Texture* play_texture
        = SDL_CreateTextureFromSurface(renderer, play_surface);
    SDL_Texture* settings_texture
        = SDL_CreateTextureFromSurface(renderer, settings_surface);
    SDL_Texture* quit_texture
        = SDL_CreateTextureFromSurface(renderer, quit_surface);
    SDL_Texture* hint_texture
        = SDL_CreateTextureFromSurface(renderer, hint_surface);

    const SDL_Rect tetris_rect = {
      WINDOW_WIDTH / 2 - tetris_surface->w / 2,
      MAIN_MENU_TOP_PADDING - BUTTON_HEIGHT * 2,
      tetris_surface->w,
      tetris_surface->h
    };

    const SDL_Rect play_rect = {
      WINDOW_WIDTH / 2 - play_surface->w / 2,
      MAIN_MENU_TOP_PADDING + (int32_t)(BUTTON_HEIGHT * 0.25),
      play_surface->w,
      play_surface->h
    };

    const SDL_Rect settings_rect = {
      WINDOW_WIDTH / 2 - settings_surface->w / 2,
      MAIN_MENU_TOP_PADDING + (int32_t)(BUTTON_HEIGHT * 2.25),
      settings_surface->w,
      settings_surface->h
    };

    const SDL_Rect quit_rect = {
      WINDOW_WIDTH / 2 - quit_surface->w / 2,
      MAIN_MENU_TOP_PADDING + (int32_t)(BUTTON_HEIGHT * 4.25),
      quit_surface->w,
      quit_surface->h
    };

    const SDL_Rect hint_rect = {
      WINDOW_WIDTH / 2 - hint_surface->w / 2,
      WINDOW_HEIGHT - BUTTON_HEIGHT,
      hint_surface->w,
      hint_surface->h
    };

    SDL_RenderCopy(renderer, tetris_texture, NULL, &tetris_rect);
    SDL_RenderCopy(renderer, play_texture, NULL, &play_rect);
    SDL_RenderCopy(renderer, settings_texture, NULL, &settings_rect);
    SDL_RenderCopy(renderer, quit_texture, NULL, &quit_rect);
    SDL_RenderCopy(renderer, hint_texture, NULL, &hint_rect);

    SDL_FreeSurface(tetris_surface);
    SDL_FreeSurface(play_surface);
    SDL_FreeSurface(settings_surface);
    SDL_FreeSurface(quit_surface);
    SDL_FreeSurface(hint_surface);
    SDL_DestroyTexture(tetris_texture);
    SDL_DestroyTexture(play_texture);
    SDL_DestroyTexture(settings_texture);
    SDL_DestroyTexture(quit_texture);
    SDL_DestroyTexture(hint_texture);
}
