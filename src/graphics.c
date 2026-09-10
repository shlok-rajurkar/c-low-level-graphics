#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdint.h>

#define WIDTH 320
#define HEIGHT 200



uint32_t framebuffer[WIDTH * HEIGHT]; 

void put_pixel(int x, int y, uint32_t color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        return;
    }
    framebuffer[WIDTH * y  + x] = color;
}

void clear(uint32_t color) {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        framebuffer[i] = color;
    }
}

int main(void) {

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event;

    const double target_frame = 1.0/60;
    
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
    uint32_t frame = 0;

    while (is_running) {

        uint64_t start = SDL_GetPerformanceCounter();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                is_running = 0;
            }
        }

        clear(0x2A2A2A);

        int x = frame % 320;
        int y = HEIGHT/2;
        put_pixel(x, y, 0x00FFFF);



        SDL_UpdateTexture(texture, NULL, framebuffer, WIDTH * sizeof(uint32_t));

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        uint64_t end = SDL_GetPerformanceCounter();

        double elapsed = (double)(end - start) / (double)SDL_GetPerformanceFrequency();

        if (elapsed < target_frame) {
            SDL_Delay((target_frame - elapsed) * 1000.0);
        }

        frame += 1;
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}


