SDL_Joystick *joystick;
int joysticks_count;

void initialize_sdl_gamepads() {
    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0) {
        fprintf(stderr, "Error: Unable to initialize SDL joystick subsystem: %s\n", SDL_GetError());
    }
    joysticks_count = SDL_NumJoysticks();
    #ifdef zoxel_debug_input
        zoxel_log(" > joysticks connected [%d]\n", joysticks_count);
    #endif
    for (int i = 0; i < joysticks_count; i++) {
        joystick = SDL_JoystickOpen(i);
        if (!joystick) {
            fprintf(stderr, "Error: Unable to open joystick: %s\n", SDL_GetError());
        }
    }
}

void set_gamepad_button(PhysicalButton *key, SDL_Joystick *joystick, int index) {
    unsigned char is_pressed = SDL_JoystickGetButton(joystick, index);
    if (!key->is_pressed && is_pressed) {
        key->pressed_this_frame = 1;
    }
    if (key->is_pressed && !is_pressed) {
        key->released_this_frame = 1;
    }
    key->is_pressed = is_pressed;
}

#define key_case(sdl_event, key)\
            case sdl_event:\
                set_key(key, eventType);\
                break;

void input_extract_from_sdl_per_frame(ecs_world_t *world) {
    if (gamepad_entity == 0 || joystick == NULL) {
        return;
    }
    if (!SDL_JoystickGetAttached(joystick)) {
        int joystick_id = SDL_JoystickInstanceID(joystick);
        fprintf(stderr, "Joystick [%d] has been disconnected.\n", joystick_id);
        SDL_JoystickClose(joystick);
        joystick = NULL;
        // \todo add disconnection event to gamepad_entity
        // - next, add a disconnection ui until reconnected
        return;
    }
    ecs_defer_begin(world);
    // Read joystick input
    // Gamepad gamepad = { }
    Gamepad *gamepad = ecs_get_mut(world, gamepad_entity, Gamepad);
    // left joystick axis
    //int left_x_axis = SDL_JoystickGetAxis(joystick, 0);
    //int left_y_axis = SDL_JoystickGetAxis(joystick, 1);
    // right joystick axis
    //int right_x_axis = SDL_JoystickGetAxis(joystick, 2);
    //int right_y_axis = SDL_JoystickGetAxis(joystick, 3);
    // triggers
    //int left_trigger = SDL_JoystickGetAxis(joystick, 4);
    //int right_trigger = SDL_JoystickGetAxis(joystick, 5);
    set_gamepad_button(&gamepad->a, joystick, 0);
    set_gamepad_button(&gamepad->b, joystick, 1);
    set_gamepad_button(&gamepad->x, joystick, 2);
    set_gamepad_button(&gamepad->y, joystick, 3);
    set_gamepad_button(&gamepad->lb, joystick, 4);
    set_gamepad_button(&gamepad->rb, joystick, 5);
    set_gamepad_button(&gamepad->select, joystick, 6);
    set_gamepad_button(&gamepad->start, joystick, 7);
    set_gamepad_button(&gamepad->left_joystick_push, joystick, 9);
    set_gamepad_button(&gamepad->right_joystick_push, joystick, 10);
    ecs_modified(world, gamepad_entity, Gamepad);
    ecs_defer_end(world);
    /*for (int i = 0; i < 12; i++)
    {
        if (SDL_JoystickGetButton(joystick, i))
        {
            printf("Button pushed at [%i]\n", i);
        }
    }*/
    if (gamepad->select.pressed_this_frame) {
        zoxel_log("Select Button Pushed.\n");
    }
    if (gamepad->select.released_this_frame) {
        zoxel_log("Select Button Released.\n");
    }
}

void reset_gamepad(ecs_world_t *world, ecs_entity_t gamepad_entity) {
    if (!gamepad_entity || !ecs_is_alive(world, gamepad_entity)) {
        return;
    }
    ecs_defer_begin(world);
    Gamepad *gamepad = ecs_get_mut(world, gamepad_entity, Gamepad);
    reset_key(&gamepad->a);
    reset_key(&gamepad->b);
    reset_key(&gamepad->x);
    reset_key(&gamepad->y);
    reset_key(&gamepad->lb);
    reset_key(&gamepad->rb);
    reset_key(&gamepad->select);
    reset_key(&gamepad->start);
    ecs_modified(world, gamepad_entity, Gamepad);
    ecs_defer_end(world);
}

/*gamepad->a.is_pressed = SDL_JoystickGetButton(joystick, 0);
gamepad->b.is_pressed = SDL_JoystickGetButton(joystick, 1);
gamepad->x.is_pressed = SDL_JoystickGetButton(joystick, 2);
gamepad->y.is_pressed = SDL_JoystickGetButton(joystick, 3);
gamepad->lb.is_pressed = SDL_JoystickGetButton(joystick, 4);
gamepad->rb.is_pressed = SDL_JoystickGetButton(joystick, 5);
gamepad->select.is_pressed = SDL_JoystickGetButton(joystick, 6);
gamepad->start.is_pressed = SDL_JoystickGetButton(joystick, 7);
gamepad->left_joystick_push.is_pressed = SDL_JoystickGetButton(joystick, 9);
gamepad->right_joystick_push.is_pressed = SDL_JoystickGetButton(joystick, 10);*/