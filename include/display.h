#include <SDL2/SDL.h>
#include <debug.h>

// Display is 64x32 px or 128x64 for SUPER-CHIP
#define PIXELS_WIDTH 64  // Actual resolution before scaling 
#define PIXELS_HEIGHT 32
#define WINDOW_SCALAR 15
#define SCREEN_WIDTH (PIXELS_WIDTH*WINDOW_SCALAR) // These are for scaling the window
#define SCREEN_HEIGHT (PIXELS_HEIGHT*WINDOW_SCALAR)
#define SCREEN_FPS 60


void init_display(void);
void cleanup_display(void);
void clear_screen(void);
uint8_t draw_from_mem(uint16_t addr, uint8_t x, uint8_t y, uint8_t n);
void render(void);