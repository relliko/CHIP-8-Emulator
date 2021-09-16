#include <SDL2/SDL.h>

// Display is 64x32 px or 128x64 for SUPER-CHIP
#define WINDOW_SCALAR 10
#define SCREEN_WIDTH (64*WINDOW_SCALAR) // pixels
#define SCREEN_HEIGHT (32*WINDOW_SCALAR)


void init_display(void);
void cleanup_display(void);
void render(void);