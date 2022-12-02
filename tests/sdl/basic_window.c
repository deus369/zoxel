// cc -std=c99 tests/sdl/basic_window.c -o basic_window -lSDL2
// #include <SDL2/SDL.h>
#include <SDL3/SDL.h>

int main(int argc, char *argv[])
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  int done;
  SDL_Event event;
  if (SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) <0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
        "SDL_CreateWindowAndRenderer() failed: %s", SDL_GetError());
    return(2);
  }
  SDL_SetWindowSize(window, 480, 480);
  done = 0;
  while (!done)
  {
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
