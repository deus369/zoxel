#include <stdio.h>

int main() {
  printf("hello, world!\n");
    #ifdef __EMSCRIPTEN__
    printf("hello __EMSCRIPTEN__ define!\n");
    #endif
  return 0;
}
