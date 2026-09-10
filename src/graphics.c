#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdint.h>

#define WIDTH 320
#define HEIGHT 200

uint32_t framebuffer[WIDTH * HEIGHT]; 

void put_pixel(int x, int y, uint32_t color) {
    framebuffer[WIDTH * y  + x] = color;
}

int main(void) {

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event;
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL Init Failed: %s \n", SDL_GetError());
        return EXIT_FAILURE;
    };


    window = SDL_CreateWindow(
        "SDL Framebuffer", 
        WIDTH * 4, 
        HEIGHT * 4, 
        0
    );

    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow failed: %s \n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(
        window,
        NULL
    );

    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s \n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_XRGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH, 
        HEIGHT
    );

    if (texture == NULL) {
        fprintf(stderr, "SDL_CreateTexture failed: %s \n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    uint8_t is_running = 1;

    while (is_running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                is_running = 0;
            }
        }



        put_pixel(WIDTH/2, HEIGHT/2, 0x00FF00);




        SDL_UpdateTexture(texture, NULL, framebuffer, WIDTH * sizeof(uint32_t));

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}


