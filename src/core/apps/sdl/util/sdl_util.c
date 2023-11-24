// todo: find a cleaner way to link to other modules
// rendering
extern void opengl_delete_resources(ecs_world_t *world);
extern void opengl_load_resources(ecs_world_t *world);
extern void engine_end(); // engine
extern void resize_cameras(int2 screen_size); // cameras
extern void resize_ui_canvases(ecs_world_t *world, int2 screen_size); // uis

void print_sdl() {
#ifdef zox_print_sdl
    zoxel_log(" > sdl stats\n");
    zoxel_log("     + platform:     %s\n", SDL_GetPlatform());
    zoxel_log("     + cpu count:    %d\n", SDL_GetCPUCount());
    zoxel_log("     + ram:          %d MB\n", SDL_GetSystemRAM());
    zoxel_log("     + screen:       %ix%i\n", screen_dimensions.x, screen_dimensions.y);
    /*zoxel_log("     + sse:          %s\n", (SDL_HasSSE() ? "true" : "false"));
    zoxel_log("     + sse2:         %s\n", (SDL_HasSSE2() ? "true" : "false"));
    zoxel_log("     + sse3:         %s\n", (SDL_HasSSE3() ? "true" : "false"));
    zoxel_log("     + sse4.1:       %s\n", (SDL_HasSSE41() ? "true" : "false"));
    zoxel_log("     + sse4.2:       %s\n", (SDL_HasSSE42() ? "true" : "false"));*/
#endif
}

unsigned char opengl_es_supported() {
    unsigned char is_supported = 0;
    int num_render_drivers = SDL_GetNumRenderDrivers();
    #ifdef zoxel_debug_opengl
        zoxel_log(" > found [%i] render drivers\n", num_render_drivers);
    #endif
    for (int i = 0; i < num_render_drivers; i++) {
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i, &info);
        if (strstr(info.name, "opengles")) {
            #ifdef zoxel_debug_opengl
                zoxel_log("     + render driver [%s]\n", info.name);
            #endif
            is_supported = 1;
        } else {
            #ifdef zoxel_debug_opengl
                zoxel_log("     - render driver [%s]\n", info.name);
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
                zoxel_log(" + GL_ES detected\n");
            #endif
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        } else {
            #ifdef zoxel_debug_opengl
                zoxel_log(" - GL_ES unavilable\n");
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
        zoxel_log(" - screen size is wrong [%ix%i]\n", screen_size.x, screen_size.y);
        zoxel_log(" > setting to 480x480\n");
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

void sdl_toggle_fullscreen(ecs_world_t *world, SDL_Window* window) {
    unsigned char is_fullscreen = SDL_GetWindowFlags(window) & sdl_fullscreen_byte;
    if (!is_fullscreen) {
        zoxel_log(" > setting to fullscreen\n");
        on_viewport_resized(world, get_current_screen_size());
        SDL_SetWindowSize(window, screen_dimensions.x, screen_dimensions.y);
    }
    sdl_set_fullscreen(window, !is_fullscreen); // todo: restore should set to pre window size
}

void print_supported_renderers() {
    int num_render_drivers = SDL_GetNumRenderDrivers();
    printf(" > found [%i] render drivers\n", num_render_drivers);
    for (int i = 0; i < num_render_drivers; i++) {
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i, &info);
        printf("     + render driver [%s]\n", info.name);
    }
}

void close_sdl_video() {
    SDL_VideoQuit();
    // SDL_Quit();
}

int initialize_sdl_video() {
    // if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    if (SDL_VideoInit(NULL) != 0) {
        zox_log(" - failed to initialize sdl [%s]\n", SDL_GetError())
        return EXIT_FAILURE;
    } else {
        set_screen_size();
        print_sdl();
#ifdef zoxel_include_vulkan
        if (is_using_vulkan) {
            if (SDL_Vulkan_LoadLibrary(NULL) != 0) {
                zoxel_log(" ! failed to load vulkan library [%s]\n", SDL_GetError());
                return EXIT_FAILURE;
            }
        }
#else
        is_using_vulkan = 0;
#endif
        if (!is_using_vulkan) set_sdl_attributes();
        return EXIT_SUCCESS;
    }
}

SDL_Window* create_sdl_window(unsigned char flags) {
    return SDL_CreateWindow(sdl_window_name,
        SDL_WINDOWPOS_UNDEFINED_DISPLAY(0), SDL_WINDOWPOS_UNDEFINED_DISPLAY(0),
        screen_dimensions.x, screen_dimensions.y, flags);
}

SDL_Window* spawn_sdl_window() {
    unsigned char is_resizeable = 1;
    unsigned long window_flags = SDL_WINDOW_OPENGL;
    #ifdef zoxel_on_android
        window_flags = SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE; // SDL_WINDOW_FULLSCREEN_DESKTOP; //  | SDL_WINDOW_HIDDEN;
        is_resizeable = 0;
    #endif
    if (is_using_vulkan) {
        window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN;
        zoxel_log(" > windows_flags is set with [SDL_WINDOW_VULKAN]\n");
    }
    SDL_Window* window = create_sdl_window(window_flags);
    if (window == NULL && is_using_vulkan) {
        zoxel_log(" ! vulkan is not supported on this device, defaulting to [SDL_WINDOW_OPENGL]\n");
        is_using_vulkan = 0;
        window_flags = SDL_WINDOW_OPENGL;
        window = create_sdl_window(window_flags);
    }
    if (window == NULL) {
        zoxel_log(" ! failed to create sdl window [%s]\n", SDL_GetError());
        return window;
    }
    SDL_SetWindowResizable(window, is_resizeable);
    if (!is_using_vulkan) {
        SDL_GL_SwapWindow(window);
        SDL_GL_SetSwapInterval(vsync);
    }
    #if !defined(zoxel_on_web) && !defined(zoxel_on_android)
        sdl_set_fullscreen(window, fullscreen);
    #endif
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
    SDL_Window* window = spawn_sdl_window();
    main_window = window;
    if (!is_using_vulkan) {
        SDL_GLContext* gl_context = create_sdl_opengl_context(window);
        spawn_app(world, window, gl_context);
        main_gl_context = gl_context;
        unsigned char app_success = main_gl_context != NULL ? EXIT_SUCCESS : EXIT_FAILURE;
        if (main_gl_context == NULL) zoxel_log("    ! opengl did not create context, exiting zoxel\n");
        if (main_gl_context == NULL) running = 0;
        return app_success;
    } else {
        #ifdef zoxel_include_vulkan
            return create_main_window_vulkan(world);
        #else
            return EXIT_FAILURE;
        #endif
    }
}

void recreate_main_window(ecs_world_t *world) {
    zox_delete(main_app)
    create_main_window(world);
}

void update_sdl(ecs_world_t *world) {
    SDL_Event event = { 0 };
    while (SDL_PollEvent(&event)) {
        input_extract_from_sdl(world, event, screen_dimensions);
        int eventType = event.type;
        if (eventType == SDL_QUIT) {
            zoxel_log(" > window was quit\n");
            engine_end();
        } else if (eventType == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) { // handles application resizing
                if (!rendering) continue;
                int2 new_screen_size = (int2) { event.window.data1, event.window.data2 };
                on_viewport_resized(world, new_screen_size);
            } else if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
                zoxel_log(" > window was minimized\n");
                opengl_delete_resources(world);
            } else if (event.window.event == SDL_WINDOWEVENT_RESTORED) {
                zoxel_log(" > window was restored\n");
                opengl_load_resources(world);
            }
        }
    }
}
