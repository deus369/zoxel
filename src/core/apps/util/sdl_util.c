// sdl util things
const char *iconFilename = resources_folder_name"textures/game_icon.png";
int2 screen_dimensions = { 720, 480 };
float aspectRatio = 1;
float fov = 60;
unsigned long windowFlags;

//! Print debug info!
void print_sdl()
{
    #ifdef zoxel_debug_sdl
        zoxel_log("SDL\n");
        zoxel_log("    Platform:        %s\n", SDL_GetPlatform());
        zoxel_log("    CPU Count:       %d\n", SDL_GetCPUCount());
        zoxel_log("    System RAM:      %d MB\n", SDL_GetSystemRAM());
        zoxel_log("    Screen Dimensions: %ix%i\n", screen_dimensions.x, screen_dimensions.y);
        zoxel_log("    Supports SSE:    %s\n", (SDL_HasSSE() ? "true" : "false"));
        zoxel_log("    Supports SSE2:   %s\n", (SDL_HasSSE2() ? "true" : "false"));
        zoxel_log("    Supports SSE3:   %s\n", (SDL_HasSSE3() ? "true" : "false"));
        zoxel_log("    Supports SSE4.1: %s\n", (SDL_HasSSE41() ? "true" : "false"));
        zoxel_log("    Supports SSE4.2: %s\n", (SDL_HasSSE42() ? "true" : "false"));
    #endif
}

int2 get_sdl_screen_size()
{
    int2 screen_size = int2_zero;
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    screen_size.x = displayMode.w;
    screen_size.y = displayMode.h;
    if (halfscreen)
    {
        screen_size.x /= 2;
        screen_size.y /= 2;
    }
    return screen_size;
}

void set_screen_size()
{
    #ifndef WEB_BUILD
        screen_dimensions = get_sdl_screen_size();
    #else
        screen_dimensions = get_webasm_screen_size();
    #endif
}

void sdl_toggle_fullscreen(SDL_Window* window)
{
    #ifndef ANDROID_BUILD
        Uint32 fullscreen_flag = SDL_WINDOW_FULLSCREEN_DESKTOP; // SDL_WINDOW_FULLSCREEN;
    #else
        Uint32 fullscreen_flag = SDL_WINDOW_FULLSCREEN;
    #endif
    unsigned char isFullscreen = SDL_GetWindowFlags(window) & fullscreen_flag;
    SDL_SetWindowFullscreen(window, isFullscreen ? 0 : fullscreen_flag);
    // SDL_ShowCursor(isFullscreen);
}

//! Initialize SDL things, thingy things.
int set_sdl_attributes(unsigned char vsync)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        // zoxel_log(stderr, "Failed to Initialize SDL2: %s\n", SDL_GetError());
        zoxel_log("Failed to Initialize SDL2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // Request at least 32-bit color
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // Request a double-buffered, OpenGL 3.0 ES (or higher) profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, sdl_gl_major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, sdl_gl_minor);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_RENDERER_SOFTWARE SDL_RENDERER_ACCELERATED
    SDL_GL_SetSwapInterval(vsync); //  ? 1 : 0);
    return EXIT_SUCCESS;
}

//! Loads a Game Icon from the ui-icons folder.
void load_app_icon(SDL_Window* window)
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

SDL_GLContext* create_sdl_context(SDL_Window* window)
{
    SDL_GLContext* context = SDL_GL_CreateContext(window);
    if (context == NULL)
    {
        // zoxel_log(stderr, "Failed to Create OpenGL Context: %s\n", SDL_GetError());
        zoxel_log("Failed to Create OpenGL Context: %s\n", SDL_GetError());
    }
    return context;
}


//! Spawn the SDLWindow.
SDL_Window* spawn_sdl_window()
{
    int didFail = set_sdl_attributes(vsync);
    set_screen_size();
    print_sdl();
    if (didFail == EXIT_FAILURE)
    {
        zoxel_log("Failed to set_sdl_attributes.");
        return NULL;
    }
    unsigned char is_resizeable = 1;
    windowFlags = SDL_WINDOW_OPENGL;
    #ifdef ANDROID_BUILD
        windowFlags = SDL_WINDOW_FULLSCREEN_DESKTOP; // SDL_WINDOW_FULLSCREEN;
        is_resizeable = false;
    #endif
    /*#ifndef WEB_BUILD
    if (fullscreen) 
    {
        printf("Setting fullscreen!\n");
        windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    #endif*/
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
        // fprintf(stderr, "Failed to Create SDLWindow: %s\n", SDL_GetError());
        zoxel_log("Failed to Create SDLWindow: %s\n", SDL_GetError());
        return window;
    }
    SDL_GL_SetSwapInterval(1);
    load_app_icon(window);
    SDL_SetWindowResizable(window, is_resizeable); // SDL_TRUE);
    SDL_GL_SwapWindow(window);
    return window;
}

extern void input_extract_from_sdl(ecs_world_t *world, SDL_Event event);
extern void input_extract_from_sdl_per_frame(ecs_world_t *world);
extern void resize_cameras(int width, int height);
extern void uis_on_viewport_resized(ecs_world_t *world, int width, int height);

void on_viewport_resized(ecs_world_t *world, int width, int height)
{
    #ifdef debug_viewport_resize
    zoxel_log("Viewport was resized [%ix%i]\n", width, height);
    #endif
    screen_dimensions.x = width;
    screen_dimensions.y = height;
    if(screen_dimensions.y <= 0)
    {
        screen_dimensions.y = 1;
    }
    aspectRatio = ((float) screen_dimensions.x) / ((float) screen_dimensions.y);
    resize_cameras(width, height);
    uis_on_viewport_resized(world, width, height);
}

//! Polls SDL for input events. Also handles resize and window exit events.
void update_sdl(ecs_world_t *world)
{
    input_extract_from_sdl_per_frame(world);
    SDL_Event event = { 0 };
    while (SDL_PollEvent(&event))
    {
        input_extract_from_sdl(world, event);
        int eventType = event.type;
        // handles application close button
        if (eventType == SDL_QUIT)
        {
            exit_game();
        }
        // redo this
        else if (eventType == SDL_KEYUP)
        {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_ESCAPE) 
            {
                exit_game();
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