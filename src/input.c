#include <input.h>
#include <SDL2/SDL.h>

SDL_Event event;

int PRESSED_KEY = 0xDEADBEEF;

// Returns the value of the key that is currently being pressed.
// If it returns 0xDEADBEEF, there is no key being pressed.
int get_currently_pressed() {
    return PRESSED_KEY;
}

void handle_input_events(void) {
    while (SDL_PollEvent(&event)) {
        switch( event.type ){
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        exit(1);
                        break;
                    case SDL_QUIT:
                        exit(1);
                        break;
                    case SDLK_1:
                        PRESSED_KEY = 0x1;
                        break;
                    case SDLK_2:
                        PRESSED_KEY = 0x2;
                        break;
                    case SDLK_3:
                        PRESSED_KEY = 0x3;
                        break;
                    case SDLK_4:
                        PRESSED_KEY = 0xC;
                        break;
                    case SDLK_q:
                        PRESSED_KEY = 0x4;
                        break;
                    case SDLK_w:
                        PRESSED_KEY = 0x5;
                        break;
                    case SDLK_e:
                        PRESSED_KEY = 0x6;
                        break;
                    case SDLK_r:
                        PRESSED_KEY = 0xD;
                        break;
                    case SDLK_a:
                        PRESSED_KEY = 0x7;
                        break;
                    case SDLK_s:
                        PRESSED_KEY = 0x8;
                        break;
                    case SDLK_d:
                        PRESSED_KEY = 0x9;
                        break;
                    case SDLK_f:
                        PRESSED_KEY = 0xE;
                        break;
                    case SDLK_z:
                        PRESSED_KEY = 0xA;
                        break;
                    case SDLK_x:
                        PRESSED_KEY = 0x0;
                        break;
                    case SDLK_c:
                        PRESSED_KEY = 0xB;
                        break;
                    case SDLK_v:
                        PRESSED_KEY = 0xF;
                        break;
                }
                break;

            case SDL_KEYUP:
                PRESSED_KEY = 0xDEADBEEF;
                break;

            default:
                break;
        }   
    }
}