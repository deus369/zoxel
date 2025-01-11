#include <SDL2/SDL.h>
#include <stdio.h>

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *win = SDL_CreateWindow("SDL Test", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  if (win == NULL) {
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Delay(30000);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}
