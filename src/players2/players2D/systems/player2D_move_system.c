void Player2DMoveSystem(ecs_iter_t *it) {
    init_delta_time()
    float2 max_delta_velocity = max_velocity;
    max_delta_velocity.x *= delta_time;
    max_delta_velocity.y *= delta_time;
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(CharacterLink, characterLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CharacterLink, characterLinks, characterLink)
        const ecs_entity_t character = characterLink->value;
        if (!zox_valid(character) || !zox_has(character, Character2D)) continue;
        if (zox_has(character, DisableMovement)) {
            const DisableMovement *disableMovement = zox_get(character, DisableMovement)
            if (disableMovement->value) continue;
        }
        unsigned char is_running = 0;
        float2 movement = float2_zero; // { 0, 0 };
        float2 left_stick = float2_zero;
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        // get the player input vector
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device = deviceLinks->value[j];
            if (!device) continue;
            if (zox_has(device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard)
                if (keyboard->a.is_pressed) movement.x = -1;
                if (keyboard->d.is_pressed) movement.x = 1;
                if (keyboard->w.is_pressed) movement.y = 1;
                if (keyboard->s.is_pressed) movement.y = -1;
                if (keyboard->left_shift.is_pressed) is_running = 1;
            } else if (zox_has(device, Gamepad)) {
                const Children *zevices = zox_get(device, Children)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZeviceStick)) {
                        const ZeviceStick *zeviceStick = zox_get(zevice_entity, ZeviceStick)
                        left_stick = zeviceStick->value;
                    } else if (zox_has(zevice_entity, ZeviceButton)) {
                        const DeviceButtonType *deviceButtonType = zox_get(zevice_entity, DeviceButtonType)
                        if (deviceButtonType->value == zox_device_button_lb || deviceButtonType->value == zox_device_button_rb) {
                            const ZeviceButton *zeviceButton = zox_get(zevice_entity, ZeviceButton)
                            if (!is_running && devices_get_is_pressed(zeviceButton->value)) is_running = 1;
                        }
                    }
                }
            } else if (zox_has(device, Touchscreen)) { // deviceMode->value == zox_device_mode_touchscreen
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    if (zox_has(zevice, Finger)) continue;
                    const ZeviceDisabled *zeviceDisabled = zox_get(zevice, ZeviceDisabled)
                    if (zeviceDisabled->value) continue;
                    if (zox_has(zevice, ZeviceStick)) {
                        const unsigned char joystick_type = zox_get_value(zevice, DeviceButtonType)
                        if (joystick_type == zox_device_stick_left) {
                            const ZeviceStick *zeviceStick = zox_get(zevice, ZeviceStick)
                            left_stick.x += zeviceStick->value.x;
                            left_stick.y += zeviceStick->value.y;
                        }
                    }
                }
            }
        }
        if (float_abs(left_stick.x) > joystick_cutoff_buffer) movement.x = left_stick.x;
        if (float_abs(left_stick.y) > joystick_cutoff_buffer) movement.y = left_stick.y;
        if (!movement.x && !movement.y) continue;
        movement.x *= player_movement_power.x;
        movement.y *= player_movement_power.y;
        if (is_running) { // gamepad->lb.is_pressed || gamepad->rb.is_pressed) {
            movement.x *= run_speed;
            movement.y *= run_speed;
        }
        zox_geter(character, Velocity2D, velocity2D)
        zox_get_muter(character, Acceleration2D, acceleration2D)
        // const float2 check_velocity = velocity2D->value;
        float2 max_speed = max_velocity;
        if (is_running) {
            max_speed.x *= run_speed;
            max_speed.y *= run_speed;
        }

        float2 potential_velocity_left = { velocity2D->value.x + (acceleration2D->value.x + movement.x) * delta_time, 0 };
        float2 potential_velocity_up = { 0, velocity2D->value.y + (acceleration2D->value.y + movement.y) * delta_time };

        if (float_abs(potential_velocity_left.x) < max_speed.x) {
            acceleration2D->value.x += movement.x;
        }
        if (float_abs(potential_velocity_up.y) < max_speed.y) {
            acceleration2D->value.y += movement.y;
        }

        /*if (float_abs(check_velocity.x) < max_delta_velocity.x) acceleration2D->value.x += delta_movement.x * player_movement_power.x;
        if (float_abs(check_velocity.y) < max_delta_velocity.y) acceleration2D->value.y += delta_movement.y * player_movement_power.y;*/
    }
} zox_declare_system(Player2DMoveSystem)
