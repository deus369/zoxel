const char *sdl_window_name = "zoxel";
const char *iconFilename = resources_folder_name"textures/game_icon.png";
int2 screen_dimensions = { 720, 480 };
const int sdl_fullscreen_byte = SDL_WINDOW_FULLSCREEN_DESKTOP; // SDL_WINDOW_FULLSCREEN;
extern void input_extract_from_sdl(ecs_world_t *world, SDL_Event event, int2 screen_dimensions);
extern void input_extract_from_sdl_per_frame(ecs_world_t *world);
extern int2 get_webasm_screen_size();
// todo: find a cleaner way to link to other modules
//  > rendering
extern int check_opengl_error(char* function_name);
extern void delete_all_opengl_resources(ecs_world_t *world);
extern void restore_all_opengl_resources(ecs_world_t *world);
extern void resize_cameras(int2 screen_size);   // > cameras
extern void uis_on_viewport_resized(ecs_world_t *world, int2 screen_size);  // > uis

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
    zoxel_log(" > viewport was resized [%ix%i]\n", screen_dimensions.x, screen_dimensions.y);
    resize_cameras(screen_dimensions);
    uis_on_viewport_resized(world, screen_dimensions);
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
    // todo: restore should set to pre window size
    sdl_set_fullscreen(window, !is_fullscreen);
}

void load_app_icon(SDL_Window* window) {
    #ifdef SDL_IMAGES
        char* fullpath = get_full_file_path(iconFilename);
        SDL_Surface *surface = IMG_Load(iconFilename); // IMG_Load(buffer);
        free(fullpath);
        SDL_SetWindowIcon(window, surface); // The icon is attached to the window pointer
        SDL_FreeSurface(surface);
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

unsigned char vulkan_supported() {
    #ifdef zoxel_include_vulkan
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
        VkExtensionProperties* extensions = (VkExtensionProperties*)malloc(sizeof(VkExtensionProperties) * extensionCount);
        vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, extensions);
        int surfaceExtensionSupported = 0;
        for (uint32_t i = 0; i < extensionCount; ++i) {
            if (strcmp(extensions[i].extensionName, VK_KHR_SURFACE_EXTENSION_NAME) == 0) {
                surfaceExtensionSupported = 1;
                break;
            }
        }
        free(extensions);
        if (surfaceExtensionSupported) {
            zoxel_log(" > vulkan is supported\n");
            return 1;
        } else {
            zoxel_log(" ! vulkan is not supported\n");
            return 0;
        }
    #else
        return 0;
    #endif
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

int init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        zoxel_log(" - failed to initialize sdl [%s]\n", SDL_GetError());
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}

int set_sdl_attributes() {
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
    return EXIT_SUCCESS;
}

SDL_Window* create_sdl_window(unsigned char flags) {
    return SDL_CreateWindow(sdl_window_name,
        SDL_WINDOWPOS_UNDEFINED_DISPLAY(0), SDL_WINDOWPOS_UNDEFINED_DISPLAY(0),
        screen_dimensions.x, screen_dimensions.y, flags);
}

SDL_Window* spawn_sdl_window() {
    set_screen_size();
    unsigned char is_resizeable = 1;
    unsigned long window_flags = SDL_WINDOW_OPENGL;
    #ifdef zoxel_on_android
        window_flags = SDL_WINDOW_FULLSCREEN_DESKTOP; //  | SDL_WINDOW_HIDDEN;
        is_resizeable = 0;
    #endif
    if (is_vulkan) {
        window_flags = SDL_WINDOW_VULKAN;
    }
    SDL_Window* window = create_sdl_window(window_flags);
    if (window == NULL && is_vulkan) {
        zoxel_log(" !!! vulkan is not supported on this device, defaulting to opengl.\n");
        is_vulkan = 0;
        window_flags = SDL_WINDOW_OPENGL;
        window = create_sdl_window(window_flags);
    }
    if (window == NULL) {
        zoxel_log(" ! failed to create sdl window [%s]\n", SDL_GetError());
        return window;
    }
    SDL_SetWindowResizable(window, is_resizeable);
    SDL_GL_SwapWindow(window);
    SDL_GL_SetSwapInterval(vsync);
    load_app_icon(window);
    #ifndef zoxel_on_web
        #ifndef zoxel_on_android
            if (fullscreen) sdl_set_fullscreen(window, 1);
        #endif
    #endif
    return window;
}

SDL_GLContext* create_sdl_context(SDL_Window* window) {
    if (window == NULL) return NULL;
    int didFail = set_sdl_attributes();
    if (didFail == EXIT_FAILURE) {
        zoxel_log("Failed to set_sdl_attributes.");
        return NULL;
    }
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
    if (!is_vulkan) {
        SDL_GLContext* gl_context = create_sdl_context(window);
        spawn_app(world, window, gl_context);
        main_gl_context = gl_context;
        unsigned char app_success = main_gl_context != NULL ? EXIT_SUCCESS : EXIT_FAILURE;
        if (main_gl_context != NULL) running = 1;
        return app_success;
    } else {
        #ifdef zoxel_include_vulkan
            VkInstance* instance;
            VkSurfaceKHR* surface;
            VkInstanceCreateInfo instanceCreateInfo = {};
            instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            vkCreateInstance(&instanceCreateInfo, NULL, instance);
            if (!SDL_Vulkan_CreateSurface(window, *instance, surface)) {
                printf("    !!! failed to create vulkan surface [%s]\n", SDL_GetError());
                return EXIT_FAILURE;
            }
            spawn_app_vulkan(world, window, surface);
            main_vulkan_context = surface;
            main_vulkan_instance = instance;
            return EXIT_SUCCESS;
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
    #ifdef zoxel_inputs
        input_extract_from_sdl_per_frame(world);
    #endif
    SDL_Event event = { 0 };
    while (SDL_PollEvent(&event)) {
        #ifdef zoxel_inputs
            input_extract_from_sdl(world, event, screen_dimensions);
        #endif
        int eventType = event.type;
        if (eventType == SDL_QUIT) {
            zoxel_log(" > window was quit\n");
            exit_game();
        } else if (eventType == SDL_WINDOWEVENT) {
            // handles application resizing
            if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                // zoxel_log(" > window was changed size\n");
                if (rendering) on_viewport_resized(world, (int2) { event.window.data1, event.window.data2 });
            } else if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
                zoxel_log(" > window was minimized\n");
                rendering = 0;
                delete_all_opengl_resources(world);
            } else if (event.window.event == SDL_WINDOWEVENT_RESTORED) {
                zoxel_log(" > window was restored\n");
                rendering = 1;
                restore_all_opengl_resources(world);
            }
        }
    }
}