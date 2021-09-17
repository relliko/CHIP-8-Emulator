#include <SDL2/SDL.h>
#include <debug.h>

// Display is 64x32 px or 128x64 for SUPER-CHIP
#define PIXELS_WIDTH 64  // Actual resolution before scaling 
#define PIXELS_HEIGHT 32
#define WINDOW_SCALAR 10
#define SCREEN_WIDTH (64*WINDOW_SCALAR) // These are for scaling the window
#define SCREEN_HEIGHT (32*WINDOW_SCALAR)
#define SCREEN_FPS 60

// Makes up the bits representing the pixels on screen
// CHIP-8 is monochrome so bits are sufficient to represent them.
uint8_t pixels[PIXELS_HEIGHT][PIXELS_WIDTH/8];

void init_display(void);
void cleanup_display(void);
void render(void);