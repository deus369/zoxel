int joysticks_count;
// debug purposes
int joystick_axes;
int last_axis_index;
int last_clicked_index = 0;

#ifdef zox_sdl

float get_gamepad_axis(SDL_Joystick *joystick, const int index) {
    if (index < 0 || index > 10) return 0; // deadzone limits
    int raw_value = SDL_JoystickGetAxis(joystick, index);
    raw_value = apply_joystick_deadzone(index, raw_value);
    float axis_value = raw_value / 32768.0f;
    if (float_abs(axis_value) <= joystick_min_cutoff) axis_value = 0.0f;
    if (axis_value < -1.0f || axis_value > 1.0f) axis_value = 0;
    axis_value = -axis_value;
    return axis_value; // invert as sdl inverts it first?
}

void check_axis(SDL_Joystick *joystick, int index) {
    float2 axis = (float2) { get_gamepad_axis(joystick, index), get_gamepad_axis(joystick, index + 1) };
    if (float_abs(axis.x) >= 0.05f || float_abs(axis.y) >= 0.05f) last_axis_index = index;
}

const char* get_joystick_name(SDL_Joystick *joystick) {
    if (joystick == NULL) return "";
    return SDL_JoystickName(joystick);
}

int debug_joystick(SDL_Joystick *joystick, char buffer[], int buffer_size, int buffer_index) {
    if (!joystick) return buffer_index;
    for (int i = 0; i < joystick_axes; i += 2) {
        check_axis(joystick, i);
    }
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "joystick [%s]\n", get_joystick_name(joystick));
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "max axis [%i]\n", joystick_axes);
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " index clicked [%i]\n", last_clicked_index);
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " index axis [%i]\n", last_axis_index);
    /*for (int i = 0; i < joystick_axes; i++) {
        int raw_value = SDL_JoystickGetAxis(joystick, i);
        raw_value = apply_joystick_deadzone(i, raw_value);
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "  axis %i value [%i] - deadzone [%i]\n", i, raw_value, joystick_deadzones_values[i]);
    }*/
    /*const Children *children = zox_get(gamepad_entity, Children)
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t e = children->value[i];
        if (zox_has(e, ZeviceButton)) {
            const byte value = zox_get_value(e, ZeviceButton)
            buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "  button %i value [%i]\n", i, value);
        }
    }*/
    return buffer_index;
}

byte is_steamdeck_gamepad(SDL_Joystick *joystick) {
    const char* joystickName = SDL_JoystickName(joystick);
    return strstr(joystickName, "Steam Deck Controller") != NULL;
}

byte is_xbox_gamepad(SDL_Joystick *joystick) {
    const char* joystickName = SDL_JoystickName(joystick);
    return strstr(joystickName, "Xbox") != NULL || strstr(joystickName, "X360") != NULL || strstr(joystickName, "X-Box") != NULL;
}

byte get_gamepad_type(SDL_Joystick *joystick) {
    byte gamepad_type = 0;
    if (is_xbox_gamepad(joystick)) gamepad_type = zox_gamepad_layout_type_xbox;
    if (is_steamdeck_gamepad(joystick)) gamepad_type = zox_gamepad_layout_type_steamdeck;
    return gamepad_type;
}

ecs_entity_t spawn_gamepad_from_sdl(ecs_world_t *world, SDL_Joystick *joystick) {
    const byte gamepad_type = get_gamepad_type(joystick);
    const ecs_entity_t e = spawn_gamepad(world, gamepad_type);
    zox_set(e, SDLGamepad, { joystick })
    zox_log_input("   + gamepad [%s]", SDL_JoystickName(joystick))
    return e;
}

void handle_new_sdl_gamepad(ecs_world_t *world, const SDL_Event event) {
    SDL_Joystick *joystick = SDL_JoystickOpen(event.jdevice.which);
    if (!joystick) {
        fprintf(stderr, "   ! joystick error: %s\n", SDL_GetError());
        return;
    }
    zox_log_input(" + new gamepad [%d] has connected", SDL_JoystickInstanceID(joystick))
    spawn_gamepad_from_sdl(world, joystick);
}

void initialize_sdl_gamepads(ecs_world_t *world) {
    // SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    joysticks_count = SDL_NumJoysticks();
    if (joysticks_count == 0) {
        return;
    }
    zox_log_input(" > gamepads connected [%d]", joysticks_count)
    for (int i = 0; i < joysticks_count; i++) {
        SDL_Joystick *joystick = SDL_JoystickOpen(i);
        if (!joystick) {
            fprintf(stderr, "   ! joystick error: %s\n", SDL_GetError());
        } else {
            spawn_gamepad_from_sdl(world, joystick);
        }
    }
}

byte process_byte(const byte old_byte, const byte raw_value) {
    const byte was_pressed = devices_get_is_pressed(old_byte);
    const byte pressed_this_frame = !was_pressed && raw_value;
    const byte released_this_frame = was_pressed && !raw_value;
    if (pressed_this_frame) zox_log_input("  [%i] is pressed this frame", index)
    if (released_this_frame) zox_log_input("  [%i] is released this frame", index)
    byte new_value = 0;
    if (pressed_this_frame) devices_set_pressed_this_frame(&new_value, 1);
    if (released_this_frame) devices_set_released_this_frame(&new_value, 1);
    if (raw_value) devices_set_is_pressed(&new_value, raw_value);
    if (new_value != old_byte) zox_log_input("   - [%i] has updated [%i > %i]", index, old_value, new_value)
    return new_value;
}

byte get_gamepad_dpad(const byte old_value, SDL_Joystick *joystick, int index) {
    byte is_pressed_down = 0;
    byte is_pressed_up = 0;
    byte is_pressed_left = 0;
    byte is_pressed_right = 0;
    Uint8 hatState = SDL_JoystickGetHat(joystick, 0);
    // Check the state of the D-pad
    switch (hatState) {
        case SDL_HAT_UP:
            is_pressed_up = 1;
            break;
        case SDL_HAT_DOWN:
            is_pressed_down = 1;
            break;
        case SDL_HAT_LEFT:
            is_pressed_left = 1;
            break;
        case SDL_HAT_RIGHT:
            is_pressed_right = 1;
            break;
        case SDL_HAT_LEFTUP:
            is_pressed_left = 1;
            is_pressed_up = 1;
            break;
        case SDL_HAT_RIGHTUP:
            is_pressed_right = 1;
            is_pressed_up = 1;
            break;
        case SDL_HAT_LEFTDOWN:
            is_pressed_left = 1;
            is_pressed_down = 1;
            break;
        case SDL_HAT_RIGHTDOWN:
            is_pressed_right = 1;
            is_pressed_down = 1;
            break;
        case SDL_HAT_CENTERED:
            // Handle no input
            break;
    }
    if (index == zox_device_button_dpad_down) return process_byte(old_value, is_pressed_down);
    else if (index == zox_device_button_dpad_up) return process_byte(old_value, is_pressed_up);
    else if (index == zox_device_button_dpad_left) return process_byte(old_value, is_pressed_left);
    else if (index == zox_device_button_dpad_right) return process_byte(old_value, is_pressed_right);
    return old_value;
}

byte set_gamepad_axis2(ZeviceStick *zeviceStick, SDL_Joystick *joystick, int index) {
    float2 previous_value = zeviceStick->value;
    zeviceStick->value.x = get_gamepad_axis(joystick, index);
    zeviceStick->value.y = get_gamepad_axis(joystick, index + 1);
    if (float_abs(zeviceStick->value.x) > 0.06f || float_abs(zeviceStick->value.y) > 0.06f) zox_log_input(" > stick [%fx%f]", zeviceStick->value.x, zeviceStick->value.y)
    return !(zeviceStick->value.x == previous_value.x && zeviceStick->value.y == previous_value.y);
}

byte set_gamepad_button(const byte old_value, SDL_Joystick *joystick, int index) {
    byte raw_value = SDL_JoystickGetButton(joystick, index);
    return process_byte(old_value, raw_value);
    /*byte was_pressed = devices_get_is_pressed(old_value);
    byte pressed_this_frame = !was_pressed && raw_value;
    byte released_this_frame = was_pressed && !raw_value;
#ifdef zox_log_gamepad_button_pressed
    if (pressed_this_frame) zox_log("  [%i] is pressed this frame\n", index)
    if (released_this_frame) zox_log("  [%i] is released this frame\n", index)
#endif
    byte new_value = 0;
    if (pressed_this_frame) devices_set_pressed_this_frame(&new_value, 1);
    if (released_this_frame) devices_set_released_this_frame(&new_value, 1);
    if (raw_value) devices_set_is_pressed(&new_value, raw_value);
#ifdef zox_log_gamepad_button_pressed
    if (new_value != old_value) zox_log("   - [%i] has updated [%i > %i]\n", index, old_value, new_value)
#endif
    if (pressed_this_frame) last_clicked_index = index;
    return new_value; // button->value != old_value;*/
}

byte sdl_gamepad_handle_disconnect(SDL_Joystick *joystick) {
    if (joystick == NULL) return 0;
    if (!SDL_JoystickGetAttached(joystick)) {
        int joystick_id = SDL_JoystickInstanceID(joystick);
        fprintf(stderr, "   > gamepad [%d] has disconnected\n", joystick_id);
        SDL_JoystickClose(joystick);
        joystick = NULL;
        return 0;
    }
    return 1;
}

// Main Function for Gamepad
void sdl_extract_gamepad(SDL_Joystick *joystick, ecs_world_t *world, const Children *children) {
    if (!joystick) return;
    joystick_axes = SDL_JoystickNumAxes(joystick);
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t e = children->value[i];
        const RealButtonIndex *realButtonIndex = zox_get(e, RealButtonIndex)
        if (zox_has(e, ZeviceStick)) {
            ZeviceStick *zeviceStick = zox_get_mut(e, ZeviceStick);
            if (set_gamepad_axis2(zeviceStick, joystick, realButtonIndex->value)) zox_modified(e, ZeviceStick);
        } else if (zox_has(e, ZeviceButton)) {
            const ZeviceButton *zevice_button = zox_get(e, ZeviceButton)
            byte new_value;
            if (is_dpad_button(realButtonIndex->value)) new_value = get_gamepad_dpad(zevice_button->value, joystick, realButtonIndex->value);
            else new_value = set_gamepad_button(zevice_button->value, joystick, realButtonIndex->value);
            if (new_value != zevice_button->value) zox_set(e, ZeviceButton, { new_value })
        }
    }
}

void debug_button(const PhysicalButton *button, const char *button_name) {
    if (button->pressed_this_frame) {
        zox_log(" > [%s] button pushed\n", button_name)
    } else if (button->released_this_frame) {
        zox_log(" > [%s] button released\n", button_name)
    }
}

void debug_stick(const PhysicalStick *physical_stick, const char *button_name) {
    if (float_abs(physical_stick->value.x) > joystick_cutoff_buffer && float_abs(physical_stick->value.y) > joystick_cutoff_buffer) {
        zox_log(" > [%s] stick pushed [%fx%f]\n", button_name, physical_stick->value.x, physical_stick->value.y)
    }
}
#else

void initialize_sdl_gamepads(ecs_world_t *world) { }

void handle_new_sdl_gamepad(ecs_world_t *world, const SDL_Event event) { }

#endif