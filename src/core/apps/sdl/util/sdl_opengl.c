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
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    if (override_opengl_es) {
        if (opengl_es_supported()) {
            #ifdef zoxel_debug_opengl
            zox_log(" + GL_ES detected\n")
            #endif
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        } else {
            #ifdef zoxel_debug_opengl
            zox_log(" - GL_ES unavilable\n")
            #endif
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        }
    }
}

SDL_GLContext* create_sdl_opengl_context(SDL_Window* window) {
    if (!window) {
        zox_log(" - SDL_Window is null [%s]\n", SDL_GetError())
        return NULL;
    }
    SDL_GLContext* context = SDL_GL_CreateContext(window);
    if (!context) {
        zox_log(" ! failed to create opengl context [%s]\n", SDL_GetError())
        zox_log(" > falling back to opengl core profile\n");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        context = SDL_GL_CreateContext(window);
    }
    if (!context) {
        zox_log(" !! failed again to create opengl context [%s]\n", SDL_GetError())
        return NULL;
    }
    if (SDL_GL_MakeCurrent(window, context) != 0) {
        zox_log(" ! failed to make OpenGL context current: %s\n", SDL_GetError())
        SDL_GL_DeleteContext(context);
        return NULL;
    }
    zox_log(" + SDL_GL_MakeCurrent succeeded: %s\n", SDL_GetError())
    return context;
}

void print_supported_renderers() {
    const int num_render_drivers = SDL_GetNumRenderDrivers();
    zox_log(" > found [%i] render drivers\n", num_render_drivers)
    for (int i = 0; i < num_render_drivers; i++) {
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i, &info);
        zox_log("     + render driver [%s]\n", info.name)
    }
}