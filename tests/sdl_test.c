#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

  SDL_version compiled;
  SDL_VERSION(&compiled);
  printf("Compiled against SDL version %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch);

  SDL_version linked;
  SDL_GetVersion(&linked);
  printf("Linked against SDL version %d.%d.%d\n", linked.major, linked.minor, linked.patch);

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Failed to initialize SDL: %s\n", SDL_GetError());
    return -1;
  }

  SDL_Window* window = SDL_CreateWindow(
    "Test OpenGL",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    800, 600,
    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
  );
  if (!window) {
    printf("Failed to create window: %s\n", SDL_GetError());
    return -1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

  SDL_GLContext context = SDL_GL_CreateContext(window);
  if (!context) {
    printf("Failed to create OpenGL context: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  if (*SDL_GetError()) {
    printf("2 Failed to create OpenGL context: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  if (SDL_GL_MakeCurrent(window, context) != 0) {
    printf("Failed to make OpenGL context current: %s\n", SDL_GetError());
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  printf("OpenGL context successfully created and made current.\n");
  SDL_Delay(30000);

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
