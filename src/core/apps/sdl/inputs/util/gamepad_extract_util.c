// #define zox_log_gamepad_button_pressed // debug button presses
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
    joysticks_count = SDL_NumJoysticks();
    //#ifdef zoxel_debug_input
    zox_log(" > gamepads connected [%d]\n", joysticks_count)
    //#endif
    for (int i = 0; i < joysticks_count; i++) {
        joystick = SDL_JoystickOpen(i);
        if (!joystick) {
            fprintf(stderr, "   ! joystick error: %s\n", SDL_GetError());
        } else {
            const char* joystick_name = SDL_JoystickName(joystick);
            zox_log("   > [%s]\n", joystick_name)
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
#ifdef zox_log_gamepad_button_pressed
    if (float_abs(zeviceStick->value.x) > 0.06f || float_abs(zeviceStick->value.y) > 0.06f) zox_log(" > stick: %fx%f\n", zeviceStick->value.x, zeviceStick->value.y)
    // else zoxel_log("no input for joystick [%i]\n", index);
#endif
    return !(zeviceStick->value.x == previous_value.x && zeviceStick->value.y == previous_value.y);
}

unsigned char set_gamepad_button2(ZeviceButton *zeviceButton, SDL_Joystick *joystick, int index) {
    unsigned char old_value = zeviceButton->value;
    unsigned char new_is_pressed = SDL_JoystickGetButton(joystick, index);
    unsigned char is_pressed = devices_get_is_pressed(zeviceButton->value);
#ifdef zox_log_gamepad_button_pressed
    // zox_log("   > new_is_pressed [%i] index [%i]\n", new_is_pressed, index)
    if (!is_pressed && new_is_pressed) zox_log("  [%i] is pressed this frame\n", index)
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
    if (!joystick) return;
    for (int i = 0; i < children->length; i++) {
        ecs_entity_t e = children->value[i];
        const RealButtonIndex *realButtonIndex = zox_get(e, RealButtonIndex)
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
