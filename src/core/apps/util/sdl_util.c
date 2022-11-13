// emscripten app functions
#ifdef __EMSCRIPTEN__

EM_JS(int, get_canvas_width, (), { return window.innerWidth; });
EM_JS(int, get_canvas_height, (), { return window.innerHeight; });

// bool isResizeCanvas = false;
int2 get_canvas_size()
{
    return (int2) { get_canvas_width(), get_canvas_height() };
}

// Condensed
void resize_canvas()
{
    printf("Resizing Canvas [%ix%i]", get_canvas_width(), get_canvas_height());
}
#endif

const char *iconFilename = "resources/textures/GameIcon.png";
int2 screenDimensions = { 720, 480 };
// int2 screenDimensions = { 1920, 800 };
float aspectRatio = 1;
float fov = 60;
unsigned long windowFlags;

//! Zoxel can also be a command tool... Wuut?!?!!
void PrintHelpMenu(const char* arg0)
{
    printf("\n");
    printf("-=-=-=-=-=--=-=-=-=-=--=-=-=-=-=--=-=-=-=-=-\n");
    printf("\n");
    printf("Welcome to Zoxel Help Menu\n\n");
    printf("    Usage: %s [options]\n", arg0);
    printf("\n");
    printf("    Options:\n");
    printf("\n");
    printf("        -h --help        print this help\n");
    printf("        -f --fullscreen  fullscreen window\n");
    printf("        -g --halfscreen  halfscreen window\n");
    printf("        -v --vsync       enable vsync\n");
    printf("        -p --profiler       enable profiler\n");
    printf("\n");
    printf("-=-=-=-=-=--=-=-=-=-=--=-=-=-=-=--=-=-=-=-=-\n");
    printf("\n");
}

void SetStartScreenSize()
{
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    screenDimensions.x = displayMode.w;
    screenDimensions.y = displayMode.h;
    if (halfscreen)
    {
        screenDimensions.x /= 2;
        screenDimensions.y /= 2;
    }
#ifdef __EMSCRIPTEN__
    int2 canvas_size = get_canvas_size();
    printf("    Canvas Screen Dimensions: %ix%i\n", canvas_size.x, canvas_size.y);
    screenDimensions = canvas_size;
#endif
}

//! Print debug info!
void print_sdl()
{
    printf("SDL\n");
    printf("    Platform:        %s\n", SDL_GetPlatform());
    printf("    CPU Count:       %d\n", SDL_GetCPUCount());
    printf("    System RAM:      %d MB\n", SDL_GetSystemRAM());
    printf("    Screen Dimensions: %ix%i\n", screenDimensions.x, screenDimensions.y);
    printf("    Supports SSE:    %s\n", SDL_HasSSE() ? "true" : "false");
    printf("    Supports SSE2:   %s\n", SDL_HasSSE2() ? "true" : "false");
    printf("    Supports SSE3:   %s\n", SDL_HasSSE3() ? "true" : "false");
    printf("    Supports SSE4.1: %s\n", SDL_HasSSE41() ? "true" : "false");
    printf("    Supports SSE4.2: %s\n", SDL_HasSSE42() ? "true" : "false");
}

void print_opengl()
{
    // Load the modern OpenGL funcs
    printf("OpenGL Context\n");
    printf("    Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("    Renderer: %s\n", glGetString(GL_RENDERER));
    printf("    Version:  %s\n", glGetString(GL_VERSION));
    printf("    GLSL Version:    %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

//! Initialize SDL things, thingy things.
int SetSDLAttributes(bool vsync)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Failed to Initialize SDL2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // Request at least 32-bit color
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // Request a double-buffered, OpenGL 3.3 (or higher) core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_RENDERER_SOFTWARE SDL_RENDERER_ACCELERATED
    SDL_GL_SetSwapInterval(vsync ? 1 : 0);
    return EXIT_SUCCESS;
}

//! Loads a Game Icon from the ui-icons folder.
void LoadIconSDL(SDL_Window* window)
{
#ifdef SDL_IMAGES
    SDL_Surface *surface = IMG_Load(iconFilename); // IMG_Load(buffer);
    // The icon is attached to the window pointer
    SDL_SetWindowIcon(window, surface);
    // ...and the surface containing the icon pixel data is no longer required.
    SDL_FreeSurface(surface);
#endif
}


//! Spawn the SDLWindow.
SDL_Window* SpawnWindowSDL(bool fullscreen)
{
    windowFlags = SDL_WINDOW_OPENGL;
    #ifndef __EMSCRIPTEN__
    if (fullscreen) 
    {
        windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    #endif
    SDL_Window* window = SDL_CreateWindow("Zoxel",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        screenDimensions.x, screenDimensions.y, windowFlags);
    if (window == NULL)
    {
        SDL_Quit();
        fprintf(stderr, "Failed to Create SDLWindow: %s\n", SDL_GetError());
        return window;
    }
    // SDL_GLContext is an alias for "void*"
    SDL_GL_SetSwapInterval(1);
    LoadIconSDL(window);
    SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_GL_SwapWindow(window);
    return window;
}

SDL_GLContext* create_sdl_context(SDL_Window* window)
{
    SDL_GLContext* context = SDL_GL_CreateContext(window);
    if (context == NULL)
    {
        fprintf(stderr, "Failed to Create OpenGL Context: %s\n", SDL_GetError());
    }
    print_opengl();
    return context;
}

void resize_viewports(int screenWidth, int screenHeight)
{
    // printf("Updated Canvas: Screen Dimensions [%i x %i] Aspect Ratio [%f].\n", screenWidth, screenHeight, aspectRatio);
    // what does viewport do? oh well
#ifndef __EMSCRIPTEN__
    glViewport(0, 0, (GLsizei) screenWidth, (GLsizei) screenHeight);
#endif
}

SDL_Window* spawn_sdl_window()
{
    int didFail = SetSDLAttributes(vsync);
    SetStartScreenSize();
    print_sdl();
    if (didFail == EXIT_FAILURE)
    {
        printf("Failed to SetSDLAttributes.");
        return NULL;
    }
    SDL_Window* window = SpawnWindowSDL(fullscreen);
    return window;
}

void sdl_on_end()
{
    SDL_Quit();
}

#ifdef __EMSCRIPTEN__
extern void on_viewport_resized(int width, int height);

bool update_web_canvas()
{
    int2 canvas_size = get_canvas_size();
    if (screenDimensions.x != canvas_size.x || screenDimensions.y != canvas_size.y)
    {
        printf("Canvas size has changed [%i x %i]\n", canvas_size.x, canvas_size.y);
        on_viewport_resized(canvas_size.x, canvas_size.y);
        return true;
    }
    return false;
}
#endif

// old window code
// SDL_CreateWindowAndRenderer(screenDimensions.x, screenDimensions.y, 0, &window, &renderer);
/*windowFlags = SDL_WINDOW_OPENGL;
SDL_CreateWindow("Zoxel", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenDimensions.x, screenDimensions.y, windowFlags);
context = SDL_GL_CreateContext(window);
if (context == NULL)
{
    return -1;
}*/
// SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
// #ifdef __EMSCRIPTEN__
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
// #else
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
// #endif