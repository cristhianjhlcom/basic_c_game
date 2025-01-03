#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define RED_SQUARE_WIDTH 50
#define RED_SQUARE_HEIGHT 50

int main(void) {
    // Init SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL is not installed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // Create windows.
    SDL_Window *window = SDL_CreateWindow(
        "First Windows",
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

    // Variables for red square.
    int posX, posY = 100;
    int speed = 5;
    // Conditional for run the app and event variables.
    bool is_running = true;
    SDL_Event event;

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

            // Handle square go out of screen.
            if (posX < 0) posX = 0;
            if (posY < 0) posY = 0;
            if (posX > (WINDOW_WIDTH - RED_SQUARE_WIDTH)) posX = WINDOW_WIDTH - RED_SQUARE_WIDTH;
            if (posY > (WINDOW_HEIGHT - RED_SQUARE_HEIGHT)) posY = WINDOW_HEIGHT - RED_SQUARE_HEIGHT;
        }

        // Clean screen. (black screen)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the red square.
        SDL_Rect red_rect = { posX, posY, RED_SQUARE_WIDTH, RED_SQUARE_HEIGHT };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &red_rect);

        // Show change on screen.
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
