// cc -std=c99 tests/sdl/sdl_window.c -o build/sdl_window -lSDL2 && ./build/sdl_window
#include <SDL2/SDL.h> // <SDL3/SDL.h>

int main(int argc, char *argv[])
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  if (SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) <0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
        "SDL_CreateWindowAndRenderer() failed: %s", SDL_GetError());
    return(2);
  }
  SDL_SetWindowSize(window, 480, 480);
  int done = 0;
  while (!done)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        done = 1;
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(100);
  }
  SDL_Quit();
  return(0);
}
