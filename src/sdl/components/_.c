zox_component(SDLWindow, SDL_Window*)
zox_component(Renderer, SDL_Renderer*)
zox_component(Context, SDL_GLContext*)

ECS_DTOR(SDLWindow, ptr, {
    if (ptr->value != 0) {
        SDL_DestroyWindow(ptr->value);
    }
})

ECS_DTOR(Renderer, ptr, {
    if (ptr->value != 0) {
        SDL_DestroyRenderer(ptr->value);
    }
})

ECS_DTOR(Context, ptr, {
    if (ptr->value != 0) {
        SDL_GL_DeleteContext(ptr->value);
    }
})

#include "mix_chunk.c"

void define_components_sdl(ecs_world_t *world) {
    zox_define_component_w_dest(SDLWindow)
    zox_define_component_w_dest(Context)
    zox_define_component_w_dest(Renderer)
    zox_define_component_w_dest(SDLMixChunk)
}