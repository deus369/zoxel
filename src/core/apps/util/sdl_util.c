// sdl util things
const char *iconFilename = "resources/textures/game_icon.png";
int2 screen_dimensions = { 720, 480 };
float aspectRatio = 1;
float fov = 60;
unsigned long windowFlags;
char *data_path = NULL;

void set_data_path()
{
    char *base_path = SDL_GetBasePath();
    if (base_path)
    {
        data_path = base_path;
    }
    else
    {
        data_path = SDL_strdup("./");
    }
    #ifdef zoxel_debug_pathing
    printf("SDL data_path: %s\n", data_path);
    #endif
}

char* get_full_file_path(const char* filepath)
{
    char* fullpath = malloc(strlen(data_path) + strlen(filepath) + 1);
    strcpy(fullpath, data_path);
    strcat(fullpath, filepath);
    #ifdef zoxel_debug_pathing
    printf("fullpath: %s\n", fullpath);
    #endif
    return fullpath;
}

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
    printf("        -s --splitscreen split screen local coop\n");
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
    screen_dimensions.x = displayMode.w;
    screen_dimensions.y = displayMode.h;
    if (halfscreen)
    {
        screen_dimensions.x /= 2;
        screen_dimensions.y /= 2;
    }
#ifdef __EMSCRIPTEN__
    int2 canvas_size = get_canvas_size();
    printf("    Canvas Screen Dimensions: %ix%i\n", canvas_size.x, canvas_size.y);
    screen_dimensions = canvas_size;
#endif
}

//! Print debug info!
void print_sdl()
{
    #ifdef zoxel_debug_sdl
    printf("SDL\n");
    printf("    Platform:        %s\n", SDL_GetPlatform());
    printf("    CPU Count:       %d\n", SDL_GetCPUCount());
    printf("    System RAM:      %d MB\n", SDL_GetSystemRAM());
    printf("    Screen Dimensions: %ix%i\n", screen_dimensions.x, screen_dimensions.y);
    printf("    Supports SSE:    %s\n", SDL_HasSSE() ? "true" : "false");
    printf("    Supports SSE2:   %s\n", SDL_HasSSE2() ? "true" : "false");
    printf("    Supports SSE3:   %s\n", SDL_HasSSE3() ? "true" : "false");
    printf("    Supports SSE4.1: %s\n", SDL_HasSSE41() ? "true" : "false");
    printf("    Supports SSE4.2: %s\n", SDL_HasSSE42() ? "true" : "false");
    #endif
}

void print_opengl()
{
    #ifdef zoxel_debug_opengl
    // Load the modern OpenGL funcs
    printf("OpenGL Context\n");
    printf("    Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("    Renderer: %s\n", glGetString(GL_RENDERER));
    printf("    Version:  %s\n", glGetString(GL_VERSION));
    printf("    GLSL Version:    %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    #endif
}

void sdl_toggle_fullscreen(SDL_Window* window)
{
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP; // SDL_WINDOW_FULLSCREEN;
    bool isFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
    SDL_SetWindowFullscreen(window, isFullscreen ? 0 : FullscreenFlag);
    // SDL_ShowCursor(isFullscreen);
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
    char* fullpath = get_full_file_path(iconFilename);
    SDL_Surface *surface = IMG_Load(iconFilename); // IMG_Load(buffer);
    free(fullpath);
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
    /*if (fullscreen) 
    {
        windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }*/
    #endif
    // SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    int2 app_position = (int2) { };
    int displays = SDL_GetNumVideoDisplays();
    if (displays > 1 && window_index != -1 && window_index < displays)
    {
        app_position.x = screen_dimensions.x * window_index;
    }
    SDL_Window* window = SDL_CreateWindow("Zoxel",
        app_position.x, app_position.y,
        screen_dimensions.x, screen_dimensions.y, windowFlags);
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

/*void resize_viewports(int screenWidth, int screenHeight)
{
    // printf("Updated Canvas: Screen Dimensions [%i x %i] Aspect Ratio [%f].\n", screenWidth, screenHeight, aspectRatio);
    // what does viewport do? oh well
//#ifndef __EMSCRIPTEN__
    glViewport(0, 0, (GLsizei) screenWidth, (GLsizei) screenHeight);
//#endif
}*/

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

//! Quits the application from running indefinitely.
void quit()
{
    running = false;
    #ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
    #endif
}

extern void input_extract_from_sdl(ecs_world_t *world, SDL_Event event);
extern void resize_cameras(int width, int height);
extern void uis_on_viewport_resized(ecs_world_t *world, int width, int height);

void on_viewport_resized(ecs_world_t *world, int width, int height)
{
    #ifdef debug_viewport_resize
    printf("Viewport was resized [%ix%i]\n", width, height);
    #endif
    screen_dimensions.x = width;
    screen_dimensions.y = height;
    if(screen_dimensions.y <= 0)
    {
        screen_dimensions.y = 1;
    }
    aspectRatio = ((float)screen_dimensions.x) / ((float)screen_dimensions.y);
    // resize_viewports(width, height);
    resize_cameras(width, height);
    uis_on_viewport_resized(world, width, height);
}

//! Polls SDL for input events. Also handles resize and window quit events.
void update_sdl(ecs_world_t *world)
{
    SDL_Event event = { 0 };
    while (SDL_PollEvent(&event))
    {
        input_extract_from_sdl(world, event);
        int eventType = event.type;
        if (eventType == SDL_QUIT)
        {
            quit();
        }
        else if (eventType == SDL_KEYUP)
        {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_ESCAPE) 
            {
                quit();
            }
        }
        else if (eventType == SDL_WINDOWEVENT)
        {
            if(event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                on_viewport_resized(world, event.window.data1, event.window.data2);
            }
        }
    }
}

//! Convert starting arguments to Settings.
int process_arguments(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            PrintHelpMenu(argv[0]);
            return EXIT_FAILURE;
        }
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--fullscreen") == 0)
        {
            fullscreen = true;
        }
        if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--halfscreen") == 0)
        {
            halfscreen = true;
        }
        if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--splitscreen") == 0)
        {
            is_split_screen = true;
        }
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--vsync") == 0)
        {
            vsync = true;
        }
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--profiler") == 0)
        {
            profiler = true;
        }
        if (strcmp(argv[i], "-z") == 0 || strcmp(argv[i], "--headless") == 0)
        {
            headless = true;
        }
    }
    return EXIT_SUCCESS;
}

#ifdef __EMSCRIPTEN__

#define debug_ui_scaling

bool update_web_canvas(ecs_world_t *world)
{
    int2 canvas_size = get_canvas_size();
    if (screen_dimensions.x != canvas_size.x || screen_dimensions.y != canvas_size.y)
    {
        printf("update_web_canvas: Canvas size has changed [%i x %i]\n", canvas_size.x, canvas_size.y);
        on_viewport_resized(world, canvas_size.x, canvas_size.y);
        return true;
    }
    return false;
}
#endif