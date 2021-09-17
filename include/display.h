#include <SDL2/SDL.h>
#include <debug.h>

// Display is 64x32 px or 128x64 for SUPER-CHIP
#define PIXELS_WIDTH 64  // Actual resolution before scaling 
#define PIXELS_HEIGHT 32
#define WINDOW_SCALAR 10
#define SCREEN_WIDTH (64*WINDOW_SCALAR) // These are for scaling the window
#define SCREEN_HEIGHT (32*WINDOW_SCALAR)
#define SCREEN_FPS 60


void init_display(void);
void cleanup_display(void);
void render(void);