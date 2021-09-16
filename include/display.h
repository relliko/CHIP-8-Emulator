#include <SDL2/SDL.h>

// Display is 64x32 px or 128x64 for SUPER-CHIP
#define WINDOW_SCALAR 15
#define SCREEN_WIDTH (64*WINDOW_SCALAR) // pixels
#define SCREEN_HEIGHT (32*WINDOW_SCALAR)
#define SCREEN_FPS 60


void init_display(void);
void cleanup_display(void);
void render(void);