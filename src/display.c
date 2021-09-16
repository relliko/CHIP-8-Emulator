#include <display.h>

SDL_Window *window;

// Makes up the bits representing the pixels on screen
// CHIP-8 is monochrome so bits are sufficient to represent them.
uint8_t pixels[SCREEN_HEIGHT/8][SCREEN_WIDTH/8];

void init_display(void) {
    SDL_Init(SDL_INIT_VIDEO);
    printf("%lu\n", sizeof(pixels[0]));
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
