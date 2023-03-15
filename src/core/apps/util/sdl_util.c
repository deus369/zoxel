// sdl util things
const char *iconFilename = resources_folder_name"textures/game_icon.png";
int2 screen_dimensions = { 720, 480 };
float aspectRatio = 1;
float fov = 60;
// unsigned long window_flags;
// SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN

//! Print debug info!
void print_sdl() {
    #ifdef zoxel_debug_sdl
        zoxel_log(" > sdl stats\n");
        zoxel_log("     + platform:     %s\n", SDL_GetPlatform());
        zoxel_log("     + cpu count:    %d\n", SDL_GetCPUCount());
        zoxel_log("     + ram:          %d MB\n", SDL_GetSystemRAM());
        zoxel_log("     + screen:       %ix%i\n", screen_dimensions.x, screen_dimensions.y);
        zoxel_log("     + sse:          %s\n", (SDL_HasSSE() ? "true" : "false"));
        zoxel_log("     + sse2:         %s\n", (SDL_HasSSE2() ? "true" : "false"));
        zoxel_log("     + sse3:         %s\n", (SDL_HasSSE3() ? "true" : "false"));
        zoxel_log("     + sse4.1:       %s\n", (SDL_HasSSE41() ? "true" : "false"));
        zoxel_log("     + sse4.2:       %s\n", (SDL_HasSSE42() ? "true" : "false"));
    #endif
}

int2 get_sdl_screen_size() {
    int2 screen_size = int2_zero;
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    screen_size.x = displayMode.w;
    screen_size.y = displayMode.h;
    if (!(screen_size.x > 0 && screen_size.x < 8000 && screen_size.y > 0 && screen_size.y < 8000)) {
        zoxel_log(" - screen size is wrong [%ix%i]\n", screen_size.x, screen_size.y);
        zoxel_log(" > setting to 480x480\n");
        return (int2) { 480, 480 };
    }
    return screen_size;
}

void set_screen_size() {
    #ifdef WEB_BUILD
        screen_dimensions = get_webasm_screen_size();
    #else
        screen_dimensions = get_sdl_screen_size();
    #endif
    if (halfscreen) {
        screen_dimensions.x /= 2;
        screen_dimensions.y /= 2;
    }
}

void sdl_toggle_fullscreen(SDL_Window* window) {
    #ifndef ANDROID_BUILD
        Uint32 fullscreen_flag = SDL_WINDOW_FULLSCREEN_DESKTOP; // SDL_WINDOW_FULLSCREEN;
    #else
        Uint32 fullscreen_flag = SDL_WINDOW_FULLSCREEN;
    #endif
    unsigned char isFullscreen = SDL_GetWindowFlags(window) & fullscreen_flag;
    SDL_SetWindowFullscreen(window, isFullscreen ? 0 : fullscreen_flag);
    // SDL_ShowCursor(isFullscreen);
}

// checks es is supported
int opengl_es_supported() {
    int num_render_drivers = SDL_GetNumRenderDrivers();
    for (int i = 0; i < num_render_drivers; i++) {
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i, &info);
        zoxel_log(" > checking driver [%s]\n", info.name);
        if (strstr(info.name, "opengles")) {
            return 1; 
        }
    }
    return 0;
}

int init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        // zoxel_log(stderr, "Failed to Initialize SDL2: %s\n", SDL_GetError());
        zoxel_log("Failed to Initialize SDL2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}

//! Initialize SDL things, thingy things.
int set_sdl_attributes(unsigned char vsync) {
    // Request at least 32-bit color
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // Request a double-buffered, OpenGL 3.0 ES (or higher) profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, sdl_gl_major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, sdl_gl_minor);
    if (opengl_es_supported()) {
        zoxel_log(" > GL_ES detected\n");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    } else {
        zoxel_log(" > GL_ES unavilable\n");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    }
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // SDL_RENDERER_SOFTWARE SDL_RENDERER_ACCELERATED
    SDL_GL_SetSwapInterval(vsync); //  ? 1 : 0);
    return EXIT_SUCCESS;
}

//! Loads a Game Icon from the ui-icons folder.
void load_app_icon(SDL_Window* window) {
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
SDL_Window* spawn_sdl_window() {
    set_screen_size();
    unsigned char is_resizeable = 1;
    unsigned long window_flags = SDL_WINDOW_OPENGL;
    #ifdef ANDROID_BUILD
        window_flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
        is_resizeable = false;
    #endif
    int2 app_position = (int2) { 0, 0 };
    /*int displays = SDL_GetNumVideoDisplays();
    if (displays > 1 && window_index != -1 && window_index < displays) {
        app_position.x = screen_dimensions.x * window_index;
    }*/
    SDL_Window* window = SDL_CreateWindow("Zoxel", app_position.x, app_position.y,
        screen_dimensions.x, screen_dimensions.y, window_flags);
    if (window == NULL) {
        zoxel_log(" - failed to create sdl window [%s]\n", SDL_GetError());
        return window;
    }
    int didFail = set_sdl_attributes(vsync);
    print_sdl();
    if (didFail == EXIT_FAILURE) {
        zoxel_log("Failed to set_sdl_attributes.");
        return NULL;
    }
    load_app_icon(window);
    SDL_GL_SetSwapInterval(1);
    SDL_SetWindowResizable(window, is_resizeable);
    SDL_GL_SwapWindow(window);
    return window;
}

SDL_GLContext* create_sdl_context(SDL_Window* window) {
    if (window == NULL) {
        return NULL;
    }
    SDL_GLContext* context = SDL_GL_CreateContext(window);
    if (context == NULL) {
        zoxel_log(" - failed to create opengl context [%s]\n", SDL_GetError());
        zoxel_log(" > falling back to opengl core profile\n");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        context = SDL_GL_CreateContext(window);
    }
    if (context == NULL) {
        // zoxel_log(stderr, "Failed to Create OpenGL Context: %s\n", SDL_GetError());
        zoxel_log(" - failed again to create opengl context [%s]\n", SDL_GetError());
    }
    return context;
}

extern void input_extract_from_sdl(ecs_world_t *world, SDL_Event event);
extern void input_extract_from_sdl_per_frame(ecs_world_t *world);
extern void resize_cameras(int width, int height);
extern void uis_on_viewport_resized(ecs_world_t *world, int width, int height);

void on_viewport_resized(ecs_world_t *world, int width, int height) {
    #ifdef debug_viewport_resize
    zoxel_log("Viewport was resized [%ix%i]\n", width, height);
    #endif
    screen_dimensions.x = width;
    screen_dimensions.y = height;
    if(screen_dimensions.y <= 0) {
        screen_dimensions.y = 1;
    }
    aspectRatio = ((float) screen_dimensions.x) / ((float) screen_dimensions.y);
    resize_cameras(width, height);
    uis_on_viewport_resized(world, width, height);
}

//! Polls SDL for input events. Also handles resize and window exit events.
void update_sdl(ecs_world_t *world) {
    input_extract_from_sdl_per_frame(world);
    SDL_Event event = { 0 };
    while (SDL_PollEvent(&event)) {
        input_extract_from_sdl(world, event);
        int eventType = event.type;
        // handles application close button
        if (eventType == SDL_QUIT) {
            exit_game();
        } else if (eventType == SDL_WINDOWEVENT) {
            if(event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                on_viewport_resized(world, event.window.data1, event.window.data2);
            }
        }
        // todo: move this to engine code
        else if (eventType == SDL_KEYUP) {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_ESCAPE) {
                exit_game();
            }
        }
    }
}