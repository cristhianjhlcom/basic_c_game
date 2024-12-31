#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL is not installed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    printf("SDL success installed.\n");
    SDL_Quit();
    return EXIT_SUCCESS;
}
