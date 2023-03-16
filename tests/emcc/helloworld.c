// build with 
// ~/projects/emsdk/upstream/emscripten/emcc -o build/helloworld.html tests/emcc/helloworld.c
// ~/projects/emsdk/upstream/emscripten/emrun --browser firefox-esr build/helloworld.html
#include <stdio.h>

int main() {
  printf("hello, world!\n");
    #ifdef __EMSCRIPTEN__
    printf("hello __EMSCRIPTEN__ define!\n");
    #endif
  return 0;
}
