#ifdef zox_lib_sdl
zox_component(SDLGamepad, SDL_Joystick*)

void free_sdl_gamepad(SDLGamepad *ptr) {
    if (ptr->value) {
        SDL_JoystickClose(ptr->value);
    }
} ECS_DTOR(SDLGamepad, ptr, { free_sdl_gamepad(ptr); })

#endif
