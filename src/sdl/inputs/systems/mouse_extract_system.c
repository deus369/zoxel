/*
    SDL_GetMouseState: Retrieves the current state of the mouse.
    SDL_GetRelativeMouseState: Retrieves the relative state of the mouse.
    SDL_GetMouseFocus: Retrieves the window that currently has mouse focus.
    SDL_GetMouseWheelDirection: Retrieves the current direction of the mouse wheel (if supported)
*/

void MouseExtractSystem(ecs_iter_t *it) {
    zox_sys_world()
    // remember: sdl doesn't do multiple mouses
    zox_geter_value2(main_app, WindowSize, int2, screen_size)
    // zox_log("screen_size.y: %i", screen_size.y)
    if (screen_size.x % 2 != 0) {
        screen_size.x--;
    }
    if (screen_size.y % 2 != 0) {
        screen_size.y--;
    }
    int2 mouse_position;
    Uint32 buttons = SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
    int2_flip_y(&mouse_position, screen_size);
    byte button_pressed_left = 0;
    // byte button_pressed_middle = 0;
    byte button_pressed_right = 0;
    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        button_pressed_left = 1;
    }
    // if (buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE)) button_pressed_middle = 1;
    if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        button_pressed_right = 1;
    }
    zox_sys_begin()
    zox_sys_in(Children)
    zox_sys_in(AppLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Children, children)
        zox_sys_i(AppLink, appLink)
        // using button_pressed_left
        for (int j = 0; j < children->length; j++) {
            const ecs_entity_t zevice = children->value[j];
            if (!zevice) {
                continue;
            }
            if (zox_has(zevice, ZevicePointerPosition)) {
                if (global_any_fingers_down) {
                    zox_geter(zevice, ZevicePointerPosition, position)
                    int2 position2 = position->value;
                    int2_flip_y(&position2, screen_size);
                    SDL_Window* sdl_window = zox_get_value(appLink->value, SDLWindow)
                    SDL_WarpMouseInWindow(sdl_window, position2.x, position2.y);
                } else {
                    zox_get_muter(zevice, ZevicePointerPosition, position)
                    zox_get_muter(zevice, ZevicePointerDelta, delta)
                    delta->value = int2_sub(mouse_position, position->value);
                    // delta->value = int2_sub(position->value, mouse_position);
                    position->value = mouse_position;
                }
            }
            if (global_any_fingers_down) {
                continue;  // does this break it?
            }
            if (zox_has(zevice, ZevicePointer)) {
                zox_get_muter(zevice, ZevicePointer, clicker)
                // convert press state, with previous state, to a proper value that holds press and release data
                clicker->value = get_button_click_state(clicker->value, button_pressed_left);
            }
            if (zox_has(zevice, ZevicePointerRight)) {
                zox_get_muter(zevice, ZevicePointerRight, clicker)
                clicker->value = get_button_click_state(clicker->value, button_pressed_right);
            }
            if (zox_has(zevice, ZeviceWheel)) {
                zox_get_muter(zevice, ZeviceWheel, wheel)
                wheel->value = static_mouse_wheel; // static_mouse_wheel.x != 0 && static_mouse_wheel.y != 0 &&
            }
        }
    }
} zox_declare_system(MouseExtractSystem)
