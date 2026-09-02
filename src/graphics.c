#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdint.h>

#define WIDTH 320
#define HEIGHT 200

uint32_t framebuffer[WIDTH * HEIGHT]; 

int main(void) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    
    window = SDL_CreateWindow(
        "SDL Framebuffer", 
        WIDTH, 
        HEIGHT, 
        0
    );

    renderer = SDL_CreateRenderer(
        window,
        NULL
    );


    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_XRGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH,
        HEIGHT
    );
    SDL_Init(SDL_INIT_VIDEO);
    return EXIT_SUCCESS;
}
