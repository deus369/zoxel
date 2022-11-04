// build with emcc -o hellosdl.html tests/emcc/hellosdl.c -s USE_SDL=2
#include <stdio.h>
#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include <SDL2/SDL.h>

int main()
{
    printf("hello, sdl!\n");
    return 0;
}
