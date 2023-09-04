void set_mouse_constrained(unsigned char constrain_mouse, int2 screen_dimensions) {
    SDL_SetRelativeMouseMode(constrain_mouse);  //! Locks Main Mouse.
    if (constrain_mouse) SDL_WarpMouseInWindow(main_window, screen_dimensions.x / 2, screen_dimensions.y / 2);
    // SDL_SetWindowGrab(main_window, constrain_mouse);
}