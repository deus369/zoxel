// #define zox_log_gamepad_button_pressed
SDL_Joystick *joystick;         // todo: connect this to gamepad
int joysticks_count;

unsigned char is_steamdeck_gamepad(SDL_Joystick *joystick) {
    const char* joystickName = SDL_JoystickName(joystick);
    return strstr(joystickName, "X-Box") != NULL;
}

unsigned char is_xbox_gamepad(SDL_Joystick *joystick) {
    const char* joystickName = SDL_JoystickName(joystick);
    return strstr(joystickName, "Xbox") != NULL || strstr(joystickName, "X360") != NULL || strstr(joystickName, "X-Box") != NULL;
}

void initialize_sdl_gamepads() {
    // SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0) fprintf(stderr, "  ! failed SDL joystick subsystem: %s\n", SDL_GetError());
    joysticks_count = SDL_NumJoysticks();
    #ifdef zoxel_debug_input
        zoxel_log(" > joysticks connected [%d]\n", joysticks_count);
    #endif
    for (int i = 0; i < joysticks_count; i++) {
        joystick = SDL_JoystickOpen(i);
        if (!joystick) {
            fprintf(stderr, "   ! joystick error: %s\n", SDL_GetError());
        } else {
            const char* joystick_name = SDL_JoystickName(joystick);
            zoxel_log(" > joystick [%i:%s] has initialized\n", i, joystick_name);
            // if (is_xbox_gamepad(joystick)) zoxel_log("     + xbox controller detected\n");
            break; 
        }
    }
}

float get_gamepad_axis(SDL_Joystick *joystick, int index) {
    if (index < 0 || index > 10) return 0;
    float axis_value = SDL_JoystickGetAxis(joystick, index) / 32768.0f;
    if (axis_value >= -joystick_min_cutoff && axis_value <= joystick_min_cutoff) axis_value = 0.0f;
    if (axis_value < -1.0f || axis_value > 1.0f) axis_value = 0;
    axis_value = -axis_value;
    axis_value = apply_joystick_deadzone(index, axis_value);
    return axis_value; // invert as sdl inverts it first?
}

void set_gamepad_dpad(SDL_Joystick *joystick, int index) {
    Uint8 hatState = SDL_JoystickGetHat(joystick, 0);
    // Check the state of the D-pad
    switch (hatState) {
        case SDL_HAT_UP:
            // Handle up input
            break;
        case SDL_HAT_DOWN:
            // Handle down input
            break;
        case SDL_HAT_LEFT:
            // Handle left input
            break;
        case SDL_HAT_RIGHT:
            // Handle right input
            break;
        case SDL_HAT_LEFTUP:
            // Handle diagonal input
            break;
        case SDL_HAT_RIGHTUP:
            // Handle diagonal input
            break;
        case SDL_HAT_LEFTDOWN:
            // Handle diagonal input
            break;
        case SDL_HAT_RIGHTDOWN:
            // Handle diagonal input
            break;
        case SDL_HAT_CENTERED:
            // Handle no input
            break;
        // Handle other diagonal and invalid input states here
    }
}

void set_gamepad_button(PhysicalButton *key, SDL_Joystick *joystick, int index) {
    unsigned char is_pressed = SDL_JoystickGetButton(joystick, index);
    if (!key->is_pressed && is_pressed) key->pressed_this_frame = 1;
    if (key->is_pressed && !is_pressed) key->released_this_frame = 1;
    key->is_pressed = is_pressed;
}

void set_gamepad_axis(PhysicalStick *stick, SDL_Joystick *joystick, int index) {
    stick->value.x = get_gamepad_axis(joystick, index);
    stick->value.y = get_gamepad_axis(joystick, index + 1);
}

unsigned char set_gamepad_axis2(ZeviceStick *zeviceStick, SDL_Joystick *joystick, int index) {
    float2 previous_value = zeviceStick->value;
    zeviceStick->value.x = get_gamepad_axis(joystick, index);
    zeviceStick->value.y = get_gamepad_axis(joystick, index + 1);
    // if (!(zeviceStick->value.x == 0 && zeviceStick->value.y == 0)) zoxel_log(" > stick: %fx%f\n", zeviceStick->value.x, zeviceStick->value.y);
    // else zoxel_log("no input for joystick [%i]\n", index);
    return !(zeviceStick->value.x == previous_value.x && zeviceStick->value.y == previous_value.y);
}

unsigned char set_gamepad_button2(ZeviceButton *zeviceButton, SDL_Joystick *joystick, int index) {
    unsigned char old_value = zeviceButton->value;
    unsigned char new_is_pressed = SDL_JoystickGetButton(joystick, index);
    unsigned char is_pressed = devices_get_is_pressed(zeviceButton->value);
    #ifdef zox_log_gamepad_button_pressed
        if (!is_pressed && new_is_pressed) zoxel_log("  [%i] is pressed this frame\n", index);
    #endif
    if (!is_pressed && new_is_pressed) devices_set_pressed_this_frame(&zeviceButton->value, 1);
    if (is_pressed && !new_is_pressed) devices_set_released_this_frame(&zeviceButton->value, 1);
    devices_set_is_pressed(&zeviceButton->value, new_is_pressed);
    /*#ifdef zox_log_gamepad_button_pressed
        if (new_is_pressed) zoxel_log("  [%i] new_is_pressed? [%i]\n", index, devices_get_is_pressed(zeviceButton->value));
    #endif*/
    // 
    /*if (!key->is_pressed && is_pressed) key->pressed_this_frame = 1;
    if (key->is_pressed && !is_pressed) key->released_this_frame = 1;
    key->is_pressed = is_pressed;*/
    #ifdef zox_log_gamepad_button_pressed
        if (zeviceButton->value != old_value) zoxel_log("  [%i] has updated state\n", index);
    #endif
    return zeviceButton->value != old_value;
}

void sdl_gamepad_handle_disconnect(SDL_Joystick *joystick) {
    if (joystick == NULL) return;
    if (!SDL_JoystickGetAttached(joystick)) {
        int joystick_id = SDL_JoystickInstanceID(joystick);
        fprintf(stderr, "   > gamepad [%d] has disconnected\n", joystick_id);
        SDL_JoystickClose(joystick);
        joystick = NULL;
    }
}

void sdl_extract_gamepad(SDL_Joystick *joystick, ecs_world_t *world, const Children *children) {
    if (joystick == NULL) return;
    for (int i = 0; i < children->length; i++) {
        ecs_entity_t e = children->value[i];
        const RealButtonIndex *realButtonIndex = ecs_get(world, e, RealButtonIndex);
        if (zox_has(e, ZeviceStick)) {
            ZeviceStick *zeviceStick = zox_get_mut(e, ZeviceStick);
            if (set_gamepad_axis2(zeviceStick, joystick, realButtonIndex->value)) zox_modified(e, ZeviceStick);
        } else if (zox_has(e, ZeviceButton)) {
            ZeviceButton *zeviceButton = zox_get_mut(e, ZeviceButton);
            if (set_gamepad_button2(zeviceButton, joystick, realButtonIndex->value)) zox_modified(e, ZeviceButton);
        }
    }
}

void debug_button(const PhysicalButton *button, const char *button_name) {
    if (button->pressed_this_frame) {
        zoxel_log(" > [%s] button pushed\n", button_name);
    } else if (button->released_this_frame) {
        zoxel_log(" > [%s] button released\n", button_name);
    }
}

void debug_stick(const PhysicalStick *physical_stick, const char *button_name) {
    if (float_abs(physical_stick->value.x) > joystick_cutoff_buffer && float_abs(physical_stick->value.y) > joystick_cutoff_buffer) {
        zoxel_log(" > [%s] stick pushed [%fx%f]\n", button_name, physical_stick->value.x, physical_stick->value.y);
    }
}

/*gamepad->a.is_pressed = SDL_JoystickGetButton(joystick, 0);
gamepad->b.is_pressed = SDL_JoystickGetButton(joystick, 1);
gamepad->x.is_pressed = SDL_JoystickGetButton(joystick, 2);
gamepad->y.is_pressed = SDL_JoystickGetButton(joystick, 3);
gamepad->lb.is_pressed = SDL_JoystickGetButton(joystick, 4);
gamepad->rb.is_pressed = SDL_JoystickGetButton(joystick, 5);
gamepad->select.is_pressed = SDL_JoystickGetButton(joystick, 6);
gamepad->start.is_pressed = SDL_JoystickGetButton(joystick, 7);
gamepad->left_stick_push.is_pressed = SDL_JoystickGetButton(joystick, 9);
gamepad->right_stick_push.is_pressed = SDL_JoystickGetButton(joystick, 10);*/
//if (axisValue != 0)
//    zoxel_log(" > joystick [%i]: %i\n", index, axisValue);
// zoxel_log("+ checking joystick!\n");
// Read joystick input
// Gamepad gamepad = { }
// left joystick axis
//int left_x_axis = SDL_JoystickGetAxis(joystick, 0);
//int left_y_axis = SDL_JoystickGetAxis(joystick, 1);
// right joystick axis
//int right_x_axis = SDL_JoystickGetAxis(joystick, 2);
//int right_y_axis = SDL_JoystickGetAxis(joystick, 3);
// triggers
//int left_trigger = SDL_JoystickGetAxis(joystick, 4);
//int right_trigger = SDL_JoystickGetAxis(joystick, 5);
/*int x_axis = SDL_JoystickGetAxis(joystick, index);
int y_axis = SDL_JoystickGetAxis(joystick, index + 1);
stick->value.x = x_axis / 32768.0f;
stick->value.y = y_axis / 32768.0f;*/

/*if (!(gamepad->left_stick.value.x == 0 && gamepad->left_stick.value.y == 0)) {
    zoxel_log(" > left_stick [%fx%f]\n", gamepad->left_stick.value.x, gamepad->left_stick.value.y);
}*/
/*if (!(float_abs(gamepad->left_stick.value.x) < 0.1f && float_abs(gamepad->left_stick.value.y) < 0.1f)) {
    zoxel_log(" > joystick l [%fx%f]\n", gamepad->left_stick.value.x, gamepad->left_stick.value.y);
}
if (!(float_abs(gamepad->right_stick.value.x) < 0.1f && float_abs(gamepad->right_stick.value.y) < 0.1f)) {
    zoxel_log(" > joystick r [%fx%f]\n", gamepad->right_stick.value.x, gamepad->right_stick.value.y);
}*/
    /*if (joystick_deadzone_times[index] - zox_current_time >= joystick_deadzone_time) {
        joystick_deadzone_times[index] = zox_current_time;
        joystick_deadzones[index] = axis_value;
        zoxel_log("new deadzone set: %i\n", axis_value);
    }
    // initialize deadzone checking
    else if (axis_value != joystick_deadzones_previous[index]) {
        joystick_deadzone_times[index] = zox_current_time;
    }*/

    // zoxel_log(" > Joystick Name: %s\n", SDL_JoystickName(joystick));
    // zoxel_log(" > Number of Axes: %d\n", SDL_JoystickNumAxes(joystick));
    /*Gamepad *gamepad = ecs_get_mut(world, gamepad_entity, Gamepad);
    if (is_xbox_gamepad(joystick)) {
        set_gamepad_button(&gamepad->a, joystick, 0);
        set_gamepad_button(&gamepad->b, joystick, 1);
        set_gamepad_button(&gamepad->x, joystick, 2);
        set_gamepad_button(&gamepad->y, joystick, 3);
        set_gamepad_button(&gamepad->lb, joystick, 4);
        set_gamepad_button(&gamepad->rb, joystick, 5);
        set_gamepad_button(&gamepad->select, joystick, 6);
        set_gamepad_button(&gamepad->start, joystick, 7);
        set_gamepad_button(&gamepad->left_stick_push, joystick, 9);
        set_gamepad_button(&gamepad->right_stick_push, joystick, 10);
        set_gamepad_button(&gamepad->lt, joystick, 11);
        set_gamepad_button(&gamepad->rt, joystick, 12);
    } else {
        set_gamepad_button(&gamepad->a, joystick, 0);
        set_gamepad_button(&gamepad->b, joystick, 1);
        set_gamepad_button(&gamepad->x, joystick, 3);
        set_gamepad_button(&gamepad->y, joystick, 4);
        set_gamepad_button(&gamepad->lb, joystick, 6);
        set_gamepad_button(&gamepad->rb, joystick, 7);
        set_gamepad_button(&gamepad->lt, joystick, 8);
        set_gamepad_button(&gamepad->rt, joystick, 9);
        set_gamepad_button(&gamepad->select, joystick, 10);
        set_gamepad_button(&gamepad->start, joystick, 11);
        set_gamepad_button(&gamepad->left_stick_push, joystick, 13);
        set_gamepad_button(&gamepad->right_stick_push, joystick, 14);
    }
    set_gamepad_axis(&gamepad->left_stick, joystick, 0);
    if (!is_steamdeck_gamepad(joystick)) {
        set_gamepad_axis(&gamepad->right_stick, joystick, 2);
    } else {
        set_gamepad_axis(&gamepad->right_stick, joystick, 3);
    }
    set_gamepad_dpad(joystick, 0);
    ecs_modified(world, gamepad_entity, Gamepad);
    #ifdef zoxel_inputs_debug_gamepad
        debug_button(&gamepad->select, "select");
        debug_button(&gamepad->start, "start");
        debug_button(&gamepad->a, "a");
        debug_button(&gamepad->b, "b");
        debug_button(&gamepad->x, "x");
        debug_button(&gamepad->y, "y");
        debug_button(&gamepad->lb, "lb");
        debug_button(&gamepad->rb, "rb");
        debug_button(&gamepad->lt, "lt");
        debug_button(&gamepad->rt, "rt");
        debug_button(&gamepad->left_stick_push, "left_stick_push");
        debug_button(&gamepad->right_stick_push, "right_stick_push");
        debug_stick(&gamepad->left_stick, "left_stick");
        debug_stick(&gamepad->right_stick, "right_stick");
    #endif
    #ifdef zoxel_inputs_debug_gamepad_sos
        for (int i = 0; i < 32; i++) {
            if (SDL_JoystickGetButton(joystick, i)) {
                zoxel_log(" > button [%i] pushed\n", i);
            }
        }
        for (int i = 0; i < 12; i++) {
            float value = get_gamepad_axis(joystick, i);
            // if (value != 0) 
            zoxel_log(" > joystick [%i] [%f]\n", i, value);
        }
    #endif*/

/*void sdl_extract_gamepad(ecs_world_t *world, ecs_entity_t gamepad) {
    if (gamepad_entity == 0 || joystick == NULL) return;
    // handle disconnection in another system?
    if (!SDL_JoystickGetAttached(joystick)) {
        int joystick_id = SDL_JoystickInstanceID(joystick);
        fprintf(stderr, "   > gamepad [%d] has disconnected\n", joystick_id);
        SDL_JoystickClose(joystick);
        joystick = NULL;
        // \todo add disconnection event to gamepad_entity
        // - next, add a disconnection ui until reconnected
        return;
    }
    const Children *children = ecs_get(world, gamepad, Children);
    for (int i = 0; i < children->length; i++) {
        ecs_entity_t e = children->value[i];
        const RealButtonIndex *realButtonIndex = ecs_get(world, e, RealButtonIndex);
        if (ecs_has(world, e, ZeviceStick)) {
            // zoxel_log(" > device stick found [%i] %lu\n", i, e);
            ZeviceStick *zeviceStick = ecs_get_mut(world, e, ZeviceStick);
            if (set_gamepad_axis2(zeviceStick, joystick, realButtonIndex->value)) ecs_modified(world, e, ZeviceStick);
            // if (ecs_has(world, e, ZeviceButton)) zoxel_log("    ! error with device stick, contains device button data[%i]\n", e);
        } else if (ecs_has(world, e, ZeviceButton)) {
            // zoxel_log(" > device button found [%i] %lu\n", i, e);
            ZeviceButton *zeviceButton = ecs_get_mut(world, e, ZeviceButton);
            if (set_gamepad_button2(zeviceButton, joystick, realButtonIndex->value)) ecs_modified(world, e, ZeviceButton);
        }
    }
}*/