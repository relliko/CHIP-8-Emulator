#include <display.h>
#include <mem.h>
#include <debug.h>

SDL_Window *window;
SDL_Renderer* renderer = NULL;

// Makes up the bits representing the pixels on screen
// CHIP-8 is monochrome so bits are sufficient to represent them.
uint8_t pixels[PIXELS_HEIGHT][PIXELS_WIDTH/8];

void init_display(void) {
    SDL_Init(SDL_INIT_VIDEO);
    // Initialize the window
    window = SDL_CreateWindow(
        "CHIP-8 EMULATOR",                 // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        SCREEN_WIDTH,                      // width, in pixels
        SCREEN_HEIGHT,                     // height, in pixels
        SDL_WINDOW_OPENGL                  // flags
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
    SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xff);
    SDL_Rect outlineRect = {x*WINDOW_SCALAR, y*WINDOW_SCALAR, WINDOW_SCALAR, WINDOW_SCALAR};
    SDL_RenderDrawRect(renderer, &outlineRect);
}

// Wipes all pixels by setting entire pixel array to 0.
void clear_screen(void) {
    for (int y = 0; y < PIXELS_HEIGHT; y++) {
        for (int x = 0; x < PIXELS_WIDTH/8; x++) {
            pixels[y][x] = 0x00;
        }
    }
}

// Draws an n pixel tall sprite from memory location held in addr at x,y in the pixel array.
// Returns 1 if a pixel was turned off by this operation, else 0
int draw_from_mem(uint16_t addr, short n, uint8_t x, uint8_t y) {
    int flipped = 0;
    // TODO: Sprite wrapping
    for (int i = 0; i < n; i++) {
        pixels[y+i][x] = pixels[y+i][x] | MEMORY[addr+i];
    }
    return flipped;
}

// Sets the render color to purple
static void set_color_purple(void) {
    SDL_SetRenderDrawColor(renderer, 0x3c, 0x00, 0x5a, 0xff);
}

static void set_color_black(void) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
}

// static void set_color_white(void) {
//     SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
// }

// Draws the pixel at x,y as a purple rect
static void draw_pixel(int x, int y) {
    set_color_purple();
    SDL_Rect fillRect = {x*WINDOW_SCALAR, y*WINDOW_SCALAR, WINDOW_SCALAR, WINDOW_SCALAR};
    SDL_RenderFillRect(renderer, &fillRect);
}

// "Clears" a pixel by drawing the color representing a blank
static void clear_pixel(int x, int y) {
    set_color_black();
    SDL_Rect fillRect = {x*WINDOW_SCALAR, y*WINDOW_SCALAR, WINDOW_SCALAR, WINDOW_SCALAR};
    SDL_RenderFillRect(renderer, &fillRect);
}

// Determines if the nth pixel from left to right in the byte is on
// Uses zero indexing.
static int pixel_on_at_pos(uint8_t bits, int n) {
    if (bits == 0 || n > 7) {
        return 0;
    } else if (0x1 & bits && n == 0) {
        return 1;
    } else if (0x2 & bits && n == 1) {
        return 1;
    } else if (0x4 & bits && n == 2) {
        return 1;
    } else if (0x8 & bits && n == 3) {
        return 1;
    } else if (0x10 & bits && n == 4) {
        return 1;
    } else if (0x20 & bits && n == 5) {
        return 1;
    } else if (0x40 & bits && n == 6) {
        return 1;
    } else if (0x80 & bits && n == 7) {
        return 1;
    }
    return 0;
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0x3c, 0x00, 0x5a, 0xff);
    // Draw a rect for every pixel in the grid
    // offset position based on x,y of pixels array
    for (int y = 0; y < PIXELS_HEIGHT; y++) {
        for (int x = 0; x < PIXELS_WIDTH; x++) {
            if (pixel_on_at_pos(pixels[y][x/8], (x % 8))) {
                draw_pixel(x, y);
            } else {
                clear_pixel(x, y);
            }
            //draw_pixel_grid(x, y);
        }
    }

    SDL_RenderPresent(renderer);

    return;
}
