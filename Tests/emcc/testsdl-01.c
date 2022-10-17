// just test the opengl SDL window

// Build
// clear; emcc -o Tests/emcc/exports/testsdl-01.html Tests/emcc/testsdl-01.c -s USE_SDL=2;

// Run
// emrun --browser firefox Tests/emcc/exports/testsdl-01.html

// build and run
// clear; emcc -o Tests/emcc/exports/testsdl-01.html Tests/emcc/testsdl-01.c -s USE_SDL=2; emrun --browser firefox Tests/emcc/exports/testsdl-01.html

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

// Useful tut https://www.jamesfmackenzie.com/2019/12/01/webassembly-graphics-with-sdl/
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;

void drawRandomPixels()
{
    printf("Hello\n");
    if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
    Uint8 * pixels = surface->pixels;
    for (int i=0; i < 1048576; i++)
    {
        char randomByte = rand() % 255;
        pixels[i] = randomByte;
    }
    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
    SDL_Texture *screenTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(screenTexture);
}

int main()
{
    printf("hello, world!\n");
    #ifdef __EMSCRIPTEN__
    printf("hello __EMSCRIPTEN__ define!\n");
    #endif
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(512, 512, 0, &window, &renderer);
    surface = SDL_CreateRGBSurface(0, 512, 512, 32, 0, 0, 0, 0);
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(drawRandomPixels, 60, 1);
#else
    // while true, run main loop here
#endif
    return 0;
}