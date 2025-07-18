void set_sdl_attributes() {
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // 24 | 32
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, sdl_gl_major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, sdl_gl_minor);
    if (is_log_sdl) {
        zox_log("+++ SDL OpenGL Version [%i.%i] +++", sdl_gl_major, sdl_gl_minor)
    }
    if (opengl_mode == zox_opengl_es) {
        zox_log("> running with opengl es!")
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    } else if (opengl_mode == zox_opengl_core) {
        zox_log("> running with opengl core!")
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    } else {
        zox_log("> running with opengl compatibility")
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    }
}

SDL_GLContext* create_sdl_opengl_context(SDL_Window* window) {
    if (!window) {
        zox_log_error("SDL_Window is null [%s]", SDL_GetError())
        return NULL;
    }
    SDL_GLContext* context = SDL_GL_CreateContext(window);
    if (!context) {
        zox_log_error("[create_sdl_opengl_context:SDL_GL_CreateContext] [%s]", SDL_GetError())
        return NULL;
    }
    if (SDL_GL_MakeCurrent(window, context) != 0) {
        zox_log(" ! failed to make OpenGL context current: %s\n", SDL_GetError())
        SDL_GL_DeleteContext(context);
        return NULL;
    }
    // SDL_Delay(10000);
    return context;
}
