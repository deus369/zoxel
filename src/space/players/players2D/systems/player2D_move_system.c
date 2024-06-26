void Player2DMoveSystem(ecs_iter_t *it) {
    init_delta_time()
    float2 max_delta_velocity = max_velocity;
    max_delta_velocity.x *= delta_time;
    max_delta_velocity.y *= delta_time;
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(CharacterLink, characterLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(CharacterLink, characterLinks, characterLink)
        const ecs_entity_t character = characterLink->value;
        if (!zox_valid(character) || !zox_has(character, Character2D)) continue;
        if (zox_has(character, DisableMovement)) {
            const DisableMovement *disableMovement = zox_get(character, DisableMovement)
            if (disableMovement->value) continue;
        }
        float2 movement = float2_zero; // { 0, 0 };
        zox_field_i_in(DeviceLinks, deviceLinkss, deviceLinks)
        // get the player input vector
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has(device_entity, Keyboard)) {
                const Keyboard *keyboard = zox_get(device_entity, Keyboard)
                if (keyboard->a.is_pressed) movement.x = -1;
                if (keyboard->d.is_pressed) movement.x = 1;
                if (keyboard->w.is_pressed) movement.y = 1;
                if (keyboard->s.is_pressed) movement.y = -1;
                if (keyboard->left_shift.is_pressed) {
                    movement.x *= run_speed;
                    movement.y *= run_speed;
                }
            } else if (zox_has(device_entity, Gamepad)) {
                float2 left_stick = float2_zero;
                unsigned char is_run = 0;
                const Children *zevices = zox_get(device_entity, Children)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZeviceStick)) {
                        const ZeviceStick *zeviceStick = zox_get(zevice_entity, ZeviceStick)
                        left_stick = zeviceStick->value;
                    } else if (zox_has(zevice_entity, ZeviceButton)) {
                        const DeviceButtonType *deviceButtonType = zox_get(zevice_entity, DeviceButtonType)
                        if (deviceButtonType->value == zox_device_button_lb || deviceButtonType->value == zox_device_button_rb) {
                            const ZeviceButton *zeviceButton = zox_get(zevice_entity, ZeviceButton)
                            if (!is_run && devices_get_is_pressed(zeviceButton->value)) is_run = 1;
                        }
                    }
                }
                if (float_abs(left_stick.x) > joystick_cutoff_buffer) movement.x = left_stick.x;
                if (float_abs(left_stick.y) > joystick_cutoff_buffer) movement.y = left_stick.y;
                if (is_run) { // gamepad->lb.is_pressed || gamepad->rb.is_pressed) {
                    movement.x *= run_speed;
                    movement.y *= run_speed;
                }
            }
        }
        if (!movement.x && !movement.y) continue;
        const Velocity2D *velocity2D = zox_get(character, Velocity2D)
        Acceleration2D *acceleration2D = zox_get_mut(character, Acceleration2D)
        const float2 delta_movement = movement;
        const float2 check_velocity = velocity2D->value;
        if (float_abs(check_velocity.x) < max_delta_velocity.x) acceleration2D->value.x += delta_movement.x * player_movement_power.x;
        if (float_abs(check_velocity.y) < max_delta_velocity.y) acceleration2D->value.y += delta_movement.y * player_movement_power.y;
        zox_modified(character, Acceleration2D)
        // zox_log(" + player movement 2D [%fx%f] acc [%fx%f]\n", movement.x, movement.y, acceleration2D->value.x, acceleration2D->value.y)
    }
} zox_declare_system(Player2DMoveSystem)
