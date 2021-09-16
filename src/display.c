#include <display.h>
#include <unistd.h>

SDL_Window *window;
SDL_Renderer* renderer = NULL;

// Makes up the bits representing the pixels on screen
// CHIP-8 is monochrome so bits are sufficient to represent them.
uint8_t pixels[(SCREEN_HEIGHT/WINDOW_SCALAR)/8][(SCREEN_WIDTH/WINDOW_SCALAR)/8];

void init_display(void) {
    SDL_Init(SDL_INIT_VIDEO);
    // Initialize the window
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

    // Initialize the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void cleanup_display(void) {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Draws a grid on the screen for debugging
static void draw_pixel_grid(int x, int y) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_Rect outlineRect = {x*WINDOW_SCALAR, y*WINDOW_SCALAR, WINDOW_SCALAR, WINDOW_SCALAR};
    SDL_RenderDrawRect(renderer, &outlineRect);
}

// Sets the render color to purple
static void set_color_purple() {
    SDL_SetRenderDrawColor(renderer, 0x3c, 0x00, 0x5a, 0xff);
}

// Draws the pixel at x,y as a purple rect
static void draw_purple_pixel(int x, int y) {
    set_color_purple();
    SDL_Rect fillRect = {x*WINDOW_SCALAR, y*WINDOW_SCALAR, WINDOW_SCALAR, WINDOW_SCALAR};
    SDL_RenderFillRect(renderer, &fillRect);
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0x3c, 0x00, 0x5a, 0xff);
    // Draw a rect for every pixel in the grid
    // offset position based on x,y of pixels array
    for (int y = 0; y < SCREEN_HEIGHT/WINDOW_SCALAR; y++) {
        for (int x = 0; x < SCREEN_WIDTH/WINDOW_SCALAR; x++) {
            draw_purple_pixel(x, y);
            draw_pixel_grid(x, y);
        }
    }
    SDL_RenderPresent(renderer);

    return;
}
