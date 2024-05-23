extern void opengl_dispose_resources(ecs_world_t *world);
extern void opengl_restore_resources(ecs_world_t *world);
extern void engine_end(); // engine
extern void resize_cameras(const int2 screen_size); // cameras, make camera just resize on viewport resize instead of extern

void print_sdl() {
#ifdef zox_print_sdl
    zox_logg(" > sdl stats\n")
    zox_log("     + platform:     %s\n", SDL_GetPlatform())
    zox_log("     + cpu count:    %d\n", SDL_GetCPUCount())
    zox_log("     + ram:          %d MB\n", SDL_GetSystemRAM())
    zox_log("     + screen:       %ix%i\n", screen_dimensions.x, screen_dimensions.y)
    /*zoxel_log("     + sse:          %s\n", (SDL_HasSSE() ? "true" : "false"));
    zoxel_log("     + sse2:         %s\n", (SDL_HasSSE2() ? "true" : "false"));
    zoxel_log("     + sse3:         %s\n", (SDL_HasSSE3() ? "true" : "false"));
    zoxel_log("     + sse4.1:       %s\n", (SDL_HasSSE41() ? "true" : "false"));
    zoxel_log("     + sse4.2:       %s\n", (SDL_HasSSE42() ? "true" : "false"));*/
    SDL_version compiled;
    SDL_version linked;
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    zox_log("     + compiled SDL version [%d.%d.%d]\n", compiled.major, compiled.minor, compiled.patch)
    zox_log("     + linking SDL version [%d.%d.%d]\n", linked.major, linked.minor, linked.patch)
#endif
}

unsigned char opengl_es_supported() {
    unsigned char is_supported = 0;
    int num_render_drivers = SDL_GetNumRenderDrivers();
#ifdef zoxel_debug_opengl
    zox_log(" > found [%i] render drivers\n", num_render_drivers)
#endif
    for (int i = 0; i < num_render_drivers; i++) {
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i, &info);
        if (strstr(info.name, "opengles")) {
#ifdef zoxel_debug_opengl
            zox_log("     + render driver [%s]\n", info.name)
#endif
            is_supported = 1;
        } else {
#ifdef zoxel_debug_opengl
            zox_log("     - render driver [%s]\n", info.name)
#endif
        }
    }
    return is_supported;
}

void set_sdl_attributes() {
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // 24 | 32
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, sdl_gl_major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, sdl_gl_minor);
    if (override_opengl_es) {
        if (opengl_es_supported()) {
#ifdef zoxel_debug_opengl
            zox_logg(" + GL_ES detected\n")
#endif
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        } else {
#ifdef zoxel_debug_opengl
            zox_logg(" - GL_ES unavilable\n")
#endif
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        }
    }
}

int2 get_sdl_screen_size() {
    int2 screen_size = int2_zero;
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    screen_size.x = displayMode.w;
    screen_size.y = displayMode.h;
    if (!(screen_size.x > 0 && screen_size.x < 22000 && screen_size.y > 0 && screen_size.y < 22000)) {
        zox_log(" - screen size is wrong [%ix%i]\n", screen_size.x, screen_size.y)
        zox_logg(" > setting to 480x480\n")
        return (int2) { 480, 480 };
    }
    return screen_size;
}

int2 get_screen_size() {
#ifdef zoxel_on_web
    return get_webasm_screen_size();
#else
    return get_sdl_screen_size();
#endif
}

void on_viewport_resized(ecs_world_t *world, const int2 new_size) {
    if (int2_equals(new_size, viewport_dimensions)) return;
    viewport_dimensions = new_size;
    if(viewport_dimensions.y <= 0) viewport_dimensions.y = 1;
    resize_cameras(viewport_dimensions); // set viewport size - triggers canvas resizing
}

void sdl_set_fullscreen(SDL_Window* window, unsigned char is_fullscreen) {
    SDL_SetWindowFullscreen(window, is_fullscreen ? sdl_fullscreen_byte : 0);
}

void on_sdl_window_restored(ecs_world_t *world, ecs_entity_t e) {
    if (!zox_has(e, WindowSize)) {
        zox_log(" ! no WindowSize on app [%lu]\n", e)
        return;
    }
    SDL_Window* window = zox_get_value(e, SDLWindow)
    const int2 window_size = zox_get_value(e, WindowSize)
    const int2 window_position = zox_get_value(e, WindowPosition)
    SDL_SetWindowSize(window, window_size.x, window_size.y);
    SDL_SetWindowPosition(window, window_position.x, window_position.y);
    // zox_log(" > setting to windowed [%ix%i]\n", window_size.x, window_size.y)
}

void sdl_toggle_fullscreen(ecs_world_t *world, ecs_entity_t e) { // SDL_Window* window) {
    unsigned char is_fullscreen = zox_get_value(e, WindowFullscreen)
    SDL_Window* window = zox_get_value(e, SDLWindow)
    // unsigned char is_fullscreen = SDL_GetWindowFlags(window) & sdl_fullscreen_byte;
    is_fullscreen = !is_fullscreen;
    zox_set(e, WindowFullscreen, { is_fullscreen })
    if (is_fullscreen) {
        screen_dimensions = get_screen_size();
        on_viewport_resized(world, screen_dimensions);
        SDL_SetWindowSize(window, screen_dimensions.x, screen_dimensions.y);
    }
    sdl_set_fullscreen(window, is_fullscreen);
    if (!is_fullscreen) on_sdl_window_restored(world, e);
}

void print_supported_renderers() {
    const int num_render_drivers = SDL_GetNumRenderDrivers();
    zox_log(" > found [%i] render drivers\n", num_render_drivers);
    for (int i = 0; i < num_render_drivers; i++) {
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i, &info);
        zox_log("     + render driver [%s]\n", info.name)
    }
}

void close_sdl_video() {
    SDL_VideoQuit();
    // SDL_Quit();
}

int initialize_sdl_video() {
    if (SDL_VideoInit(NULL) != 0) {
        zox_log(" - failed to initialize sdl [%s]\n", SDL_GetError())
        return EXIT_FAILURE;
    } else {
        screen_dimensions = get_screen_size();
        print_sdl();
#ifdef zox_include_vulkan
        if (!load_vulkan_library()) return EXIT_FAILURE;
#else
        is_using_vulkan = 0;
#endif
        if (!is_using_vulkan) set_sdl_attributes();
        return EXIT_SUCCESS;
    }
}

SDL_Window* create_sdl_window_basic(const unsigned char is_using_vulkan, const int2 position, const int2 size) {
    int flags;
    if (is_using_vulkan) flags = SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP;
    else flags = SDL_WINDOW_OPENGL;
#ifdef zoxel_on_android
    flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE;
#endif
    //SDL_Rect screen_bounds;
    //SDL_GetDisplayBounds(screen_index, &screen_bounds);
    zox_log(" + screen %i out of %i\n", (screen_index + 1), screens_count)
    //zox_log(" + screen_bounds: %fx%f\n", screen_bounds.x, screen_bounds.y)
    SDL_Window *window = SDL_CreateWindow(sdl_window_name, position.x, position.y, size.x, size.y, flags);
    if (screen_index == 1) {
        SDL_Rect displayBounds;
        SDL_GetDisplayBounds(1, &displayBounds);
        int xPos, yPos;
        SDL_GetWindowPosition(window, &xPos, &yPos);
        int borderWidth, borderHeight;
        SDL_GetWindowBordersSize(window, &borderWidth, NULL, &borderHeight, NULL);
        xPos += borderWidth;
        yPos += borderHeight;
        SDL_SetWindowPosition(window, displayBounds.x + xPos, displayBounds.y + yPos);
    }
    // return SDL_CreateWindow(sdl_window_name, SDL_WINDOWPOS_CENTERED_DISPLAY(screen_index), SDL_WINDOWPOS_CENTERED_DISPLAY(screen_index), screen_dimensions.x, screen_dimensions.y, flags);
    return window;
}

SDL_Window* create_sdl_window(const int2 position, const int2 size, const unsigned char fullscreen) {
    unsigned char is_resizeable = 1;
#ifdef zoxel_on_android
    is_resizeable = 0;
#endif
    SDL_Window* window = create_sdl_window_basic(is_using_vulkan, position, size);
    if (window == NULL && is_using_vulkan) {
        zox_logg(" ! vulkan is not supported on this device, defaulting to [SDL_WINDOW_OPENGL]\n")
        is_using_vulkan = 0;
        window = create_sdl_window_basic(is_using_vulkan, position, size);
    }
    if (window == NULL) {
        zox_log(" ! failed to create sdl window [%s]\n", SDL_GetError())
        return window;
    }
    // SDL_SetWindowResizable(window, is_resizeable);
    if (!is_using_vulkan) {
        SDL_SetWindowResizable(window, is_resizeable);
        SDL_GL_SwapWindow(window);
        SDL_GL_SetSwapInterval(vsync);
#if !defined(zoxel_on_web) && !defined(zoxel_on_android)
        sdl_set_fullscreen(window, fullscreen);
#endif
    }
    return window;
}

SDL_GLContext* create_sdl_opengl_context(SDL_Window* window) {
    if (window == NULL) return NULL;
    SDL_GLContext* context = SDL_GL_CreateContext(window);
    if (context == NULL) {
        zoxel_log(" - failed to create opengl context [%s]\n", SDL_GetError());
        zoxel_log(" > falling back to opengl core profile\n");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        context = SDL_GL_CreateContext(window);
    }
    if (context == NULL) zoxel_log(" - failed again to create opengl context [%s]\n", SDL_GetError());
    return context;
}
