// build with 
// ~/projects/emsdk/upstream/emscripten/emcc -o build/hellosdl.html tests/emcc/hellosdl.c -s USE_SDL=2
// ~/projects/emsdk/upstream/emscripten/emrun --browser firefox-esr build/hellosdl.html
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
