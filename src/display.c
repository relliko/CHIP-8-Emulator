#include <display.h>
#include <mem.h>
#include <debug.h>

SDL_Window *window;
SDL_Renderer* renderer = NULL;

// Makes up the bits representing the pixels on screen
// CHIP-8 is monochrome so bits are sufficient to represent them.
uint8_t pixels[PIXELS_HEIGHT][PIXELS_WIDTH];

void init_display(void) {
    SDL_Init(SDL_INIT_VIDEO);
    // Initialize the window
    window = SDL_CreateWindow(
        "CHIP-8 EMULATOR",                 // window title
        0,                                 // initial x position
        0,                                 // initial y position
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
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void cleanup_display(void) {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Draws a grid on the screen for debugging
static void draw_pixel_grid(int x, int y) {
    SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0x10);
    SDL_Rect outlineRect = {x*WINDOW_SCALAR, y*WINDOW_SCALAR, WINDOW_SCALAR, WINDOW_SCALAR};
    SDL_RenderDrawRect(renderer, &outlineRect);
}

// Wipes all pixels by setting entire pixel array to 0.
void clear_screen(void) {
    for (int y = 0; y < PIXELS_HEIGHT; y++) {
        for (int x = 0; x < PIXELS_WIDTH; x++) {
            pixels[y][x] = 0x00;
        }
    }
}

// Draws an n pixel tall sprite from memory location held in addr at x,y in the pixel array.
// Returns 1 if a pixel was turned off by this operation, else 0
int draw_from_mem(uint16_t addr, uint8_t x, uint8_t y, uint8_t n) {
    int flipped = 0;
    //printf("addr: 0x%x | x: %d | y: %d | n: %d | template: 0x%x\n", addr, x, y, n, MEMORY[addr]);
    for (int i = 0; i < n; i++) {
        uint8_t template = MEMORY[addr+i];
        for (int j = 0; j < 8; j++) {
            uint8_t original = pixels[y+i][x+j];
            pixels[y+i][x+j] = pixels[y+i][x+j] ^ (0x80 & (template << j));
            if (pixels[y+i][x+j] != original) {
                flipped = 1;
            }
        }
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
static int pixel_on_at_pos(uint8_t bits) {
    if (bits > 0) {
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
            if (pixel_on_at_pos(pixels[y][x])) {
                draw_pixel(x, y);
            } else {
                clear_pixel(x, y);
            }
            draw_pixel_grid(x, y);
        }
    }
    SDL_Delay(5);
    SDL_RenderPresent(renderer);

    return;
}
