#include <display.h>

SDL_Window *window;

void init_display(void) {

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "CHIP-8 EMULATOR",                 // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        SCREEN_WIDTH,                      // width, in pixels
        SCREEN_HEIGHT,                     // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        exit(1);
    }
}

void cleanup_display(void) {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void render() {
    return;
}
