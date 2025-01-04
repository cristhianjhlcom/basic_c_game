#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define RED_SQUARE_WIDTH 50
#define RED_SQUARE_HEIGHT 50
#define BLUE_SQUARE_WIDTH 50
#define BLUE_SQUARE_HEIGHT 50

bool check_collision(SDL_Rect a, SDL_Rect b);

int main(void) {
    // Init SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL is not installed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // Create windows.
    SDL_Window *window = SDL_CreateWindow(
        "Square Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        printf("Error creating the windows: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Create renderer.
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (!renderer) {
        printf("Error creating the renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // SDL_ttf Initialization.
    if (TTF_Init() == -1) {
        printf("Error ttf initialization SDL_ttf %s\n", TTF_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Load any font.
    TTF_Font *font = TTF_OpenFont("fonts/arcade_classic.ttf", 24);
    if (!font) {
        printf("Error loading font %s\n", TTF_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Variables for red square.
    int posX = 100;
    int posY = 100;
    // Variables for blue square.
    int bPosX = 400;
    int bPosY = 300;
    int speed = 10;
    // Conditional for run the app and event variables.
    bool is_running = true;
    bool show_reset_button = false;
    SDL_Event event;

    // Create surface for text and texture.
    SDL_Color white_color = { 255, 255, 255, 255 };
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, "Game Over", white_color);
    if (!text_surface) {
        printf("Error creating text surface %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_FreeSurface(text_surface);
    SDL_Rect text_rect = { 300, 250, 200, 50 };
    
    // Draw the reset button.
    SDL_Rect reset_button = { 350, 300, 100, 50 };
    // Draw the red square.
    SDL_Rect red_rect = { posX, posY, RED_SQUARE_WIDTH, RED_SQUARE_HEIGHT };
    // Draw the blue square.
    SDL_Rect blue_rect = { bPosX, bPosY, BLUE_SQUARE_WIDTH, BLUE_SQUARE_HEIGHT };

    // Create reset text surface.
    SDL_Color black_color = { 0, 0, 0, 255 };
    SDL_Surface *reset_text_surface = TTF_RenderText_Solid(font, "Reset", black_color);
    if (!reset_text_surface) {
        printf("Error creating reset text surface %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_Texture *reset_text_texture = SDL_CreateTextureFromSurface(renderer, reset_text_surface);
    SDL_FreeSurface(reset_text_surface);
    SDL_Rect reset_text_rect = { reset_button.x + 10, reset_button.y + 10, 80, 30 };

    // Game loop.
    while (is_running) {
        // Handle events.
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = false;
            }
            // Handle player keydowns.
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        posY -= speed;
                        break;
                    case SDLK_DOWN:
                        posY += speed;
                        break;
                    case SDLK_LEFT:
                        posX -= speed;
                        break;
                    case SDLK_RIGHT:
                        posX += speed;
                        break;
                }
            }

            // Handle mouse click.
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // Check is the click is insede of button.
                if (show_reset_button &&
                    mouseX >= reset_button.x &&
                    mouseX <= reset_button.x + reset_button.w &&
                    mouseY >= reset_button.y &&
                    mouseY <= reset_button.y + reset_button.h) {
                    posX = 100;
                    posY = 100;
                    red_rect.x = posX;
                    red_rect.y = posY;
                    show_reset_button = false;
                    printf("Pressed reset button\n");
                }
            }

            // Update red square position.
            red_rect.x = posX;
            red_rect.y = posY;

            // Handle square go out of screen.
            if (posX < 0) posX = 0;
            if (posY < 0) posY = 0;
            if (posX > (WINDOW_WIDTH - RED_SQUARE_WIDTH)) posX = WINDOW_WIDTH - RED_SQUARE_WIDTH;
            if (posY > (WINDOW_HEIGHT - RED_SQUARE_HEIGHT)) posY = WINDOW_HEIGHT - RED_SQUARE_HEIGHT;
        }

        // Clean screen. (black screen)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render blue square.
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &blue_rect);

        if (check_collision(red_rect, blue_rect)) {
            show_reset_button = true;
            SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
        }

        if (show_reset_button) {
            // Colorize white reset button.
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &reset_button);
            SDL_RenderCopy(renderer, reset_text_texture, NULL, &reset_text_rect);
        } else {
            // Change to green of red_rect.
            // Render on screen the red_rect.
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &red_rect);
        }

        // Show change on screen.
        SDL_RenderPresent(renderer);
    }
    // Clean resources.
    SDL_DestroyTexture(text_texture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    return EXIT_SUCCESS;
}

bool check_collision(SDL_Rect a, SDL_Rect b) {
    return (a.x + a.w >= b.x) && // A's right edge >= B's left edge.
        (a.x <= b.x + b.w) &&    // A's left edge <= B's right edge.
        (a.y + a.h >= b.y) &&    // A's botton edge >= B's top edge.
        (a.y <= b.y + b.h);      // A's top edge <= B's botton edge.
}
