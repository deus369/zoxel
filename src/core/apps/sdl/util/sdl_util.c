// todo: find a cleaner way to link to other modules
// rendering
extern void opengl_delete_resources(ecs_world_t *world);
extern void opengl_load_resources(ecs_world_t *world);
extern void engine_end(); // engine
extern void resize_cameras(int2 screen_size); // cameras
extern void resize_ui_canvases(ecs_world_t *world, int2 screen_size); // uis

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

int2 get_current_screen_size() {
#ifdef zoxel_on_web
    return get_webasm_screen_size();
#else
    return get_sdl_screen_size();
#endif
}

void set_screen_size() {
    screen_dimensions = get_current_screen_size();
    if (halfscreen) {
        screen_dimensions.x /= 2;
        screen_dimensions.y /= 2;
    }
}

void on_viewport_resized(ecs_world_t *world, int2 new_screen_dimensions) {
    if (screen_dimensions.x == new_screen_dimensions.x && screen_dimensions.y == new_screen_dimensions.y) return;
    screen_dimensions = new_screen_dimensions;
    if(screen_dimensions.y <= 0) screen_dimensions.y = 1;
    // zoxel_log(" > viewport was resized [%ix%i]\n", screen_dimensions.x, screen_dimensions.y);
    resize_cameras(screen_dimensions);
    resize_ui_canvases(world, screen_dimensions);
}

void sdl_set_fullscreen(SDL_Window* window, unsigned char is_fullscreen) {
    SDL_SetWindowFullscreen(window, is_fullscreen ? sdl_fullscreen_byte : 0);
}

void sdl_toggle_fullscreen(ecs_world_t *world, ecs_entity_t e) { // SDL_Window* window) {
    unsigned char is_fullscreen = zox_get_value(e, WindowFullscreen)
    SDL_Window* window = zox_get_value(e, SDLWindow)
    // unsigned char is_fullscreen = SDL_GetWindowFlags(window) & sdl_fullscreen_byte;
    is_fullscreen = !is_fullscreen;
    zox_set(e, WindowFullscreen, { is_fullscreen })
    if (is_fullscreen) {
        zox_logg(" > setting to fullscreen\n")
        on_viewport_resized(world, get_current_screen_size());
        SDL_SetWindowSize(window, screen_dimensions.x, screen_dimensions.y);
    }
    sdl_set_fullscreen(window, is_fullscreen);
    if (!is_fullscreen) {
        if (!zox_has(e, WindowSize)) {
            zox_log("no WindowSize on main_app..\n")
            return;
        }
        int2 window_size = zox_get_value(e, WindowSize)
        int2 window_position = zox_get_value(e, WindowPosition)
        zox_log(" > setting to windowed [%ix%i]\n", window_size.x, window_size.y)
        SDL_SetWindowSize(window, window_size.x, window_size.y);
        SDL_SetWindowPosition(window, window_position.x, window_position.y);
    }
}

void print_supported_renderers() {
    int num_render_drivers = SDL_GetNumRenderDrivers();
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
        set_screen_size();
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

SDL_Window* create_sdl_window_basic(unsigned char is_using_vulkan) {
    int flags;
    if (is_using_vulkan) flags = SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP;
    else flags = SDL_WINDOW_OPENGL;
#ifdef zoxel_on_android
    flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE;
#endif
    return SDL_CreateWindow(sdl_window_name, SDL_WINDOWPOS_UNDEFINED_DISPLAY(0), SDL_WINDOWPOS_UNDEFINED_DISPLAY(0), screen_dimensions.x, screen_dimensions.y, flags);
}

SDL_Window* create_sdl_window(unsigned char fullscreen) {
    unsigned char is_resizeable = 1;
#ifdef zoxel_on_android
    is_resizeable = 0;
#endif
    SDL_Window* window = create_sdl_window_basic(is_using_vulkan);
    if (window == NULL && is_using_vulkan) {
        zox_logg(" ! vulkan is not supported on this device, defaulting to [SDL_WINDOW_OPENGL]\n")
        is_using_vulkan = 0;
        window = create_sdl_window_basic(is_using_vulkan);
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

unsigned char is_opengl_running() {
    return main_gl_context != NULL;
}

unsigned char create_main_window(ecs_world_t *world) {
    SDL_Window* window = create_sdl_window(fullscreen);
    main_window = window;
    if (!is_using_vulkan) {
        SDL_GLContext* gl_context = create_sdl_opengl_context(window);
        spawn_app_sdl(world, window, gl_context, fullscreen);
        main_gl_context = gl_context;
        unsigned char app_success = main_gl_context != NULL ? EXIT_SUCCESS : EXIT_FAILURE;
        if (main_gl_context == NULL) zoxel_log("    ! opengl did not create context, exiting zoxel\n");
        if (main_gl_context == NULL) running = 0;
        return app_success;
    } else {
#ifdef zox_include_vulkan
        return create_main_window_vulkan(world, window);
#else
        return EXIT_FAILURE;
#endif
    }
}

void recreate_main_window(ecs_world_t *world) {
    zox_delete(main_app)
    create_main_window(world);
}

void update_sdl(ecs_world_t *world, ecs_entity_t e) {
    SDL_Event event = { 0 };
    while (SDL_PollEvent(&event)) {
        input_extract_from_sdl(world, event, screen_dimensions);
        int eventType = event.type;
        if (eventType == SDL_QUIT) {
            zox_logg(" > window was quit\n")
            engine_end();
        } else if (eventType == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) { // handles application resizing
                if (!rendering) continue;
                int2 new_screen_size = (int2) { event.window.data1, event.window.data2 };
                on_viewport_resized(world, new_screen_size);
                unsigned char is_fullscreen = zox_get_value(e, WindowFullscreen)
                if (!is_fullscreen) {
                    zox_set(e, WindowSize, { new_screen_size.x, new_screen_size.y });
                }
            } else if (event.window.event == SDL_WINDOWEVENT_MOVED) { // handles application resizing
                if (!rendering) continue;
                int2 new_window_position = (int2) { event.window.data1, event.window.data2 };
                unsigned char is_fullscreen = zox_get_value(e, WindowFullscreen)
                if (!is_fullscreen) {
                    zox_set(e, WindowPosition, { new_window_position.x, new_window_position.y });
                }
            } else if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
                zox_logg(" > window was minimized\n")
                opengl_delete_resources(world);
            } else if (event.window.event == SDL_WINDOWEVENT_RESTORED) {
                zox_logg(" > window was restored\n")
                opengl_load_resources(world);
            }
        }
    }
}
