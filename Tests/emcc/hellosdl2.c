// build with emcc -o hellosdl.html tests/emcc/hellosdl.c -s USE_SDL=2
#include <stdio.h>
#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

int main()
{
    printf("hello, sdl 2!\n");
    return 0;
}
