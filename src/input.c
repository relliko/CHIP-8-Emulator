#include <input.h>

SDL_Event event;

void handle_input_events(void) {
    while (SDL_PollEvent(&event)) {
        switch( event.type ){
            case SDL_KEYDOWN:
                printf( "Key pressed\n" );
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        exit(1);
                        break;
                    case SDL_QUIT:
                        exit(1);
                        break;
                    case SDLK_1:
                        break;
                    case SDLK_2:
                        break;
                    case SDLK_3:
                        break;
                    case SDLK_4:
                        break;
                    case SDLK_q:
                        break;
                    case SDLK_w:
                        break;
                    case SDLK_e:
                        break;
                    case SDLK_r:
                        break;
                    case SDLK_a:
                        break;
                    case SDLK_s:
                        break;
                    case SDLK_d:
                        break;
                    case SDLK_f:
                        break;
                    case SDLK_z:
                        break;
                    case SDLK_x:
                        break;
                    case SDLK_c:
                        break;
                    case SDLK_v:
                        break;
                }
                break;

            case SDL_KEYUP:
                //printf( "Key release detected\n" );
                break;

            default:
                break;
        }   
    }
}