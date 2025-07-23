void Player3DTriggerSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_in(CharacterLink, characterLinks, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CharacterLink, characterLinks, characterLink)
        ecs_entity_t character = characterLink->value;
        if (!character || !zox_has(character, Character3)) {
            continue;
        }
        const DisableMovement *disableMovement = zox_get(character, DisableMovement)
        if (disableMovement->value) {
            continue;
        }
        byte is_triggered_a = 0;
        // byte is_triggered_b = 0;
        zox_field_i(DeviceMode, deviceModes, deviceMode)
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!device) continue;
            if (deviceMode->value == zox_device_mode_keyboardmouse && zox_has(device, Mouse)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    if (zox_has(zevice, ZevicePointer)) {
                        const byte click = zox_get_value(zevice, ZevicePointer)
                        if (devices_get_pressed_this_frame(click)) is_triggered_a = 1;
                    }
                    /*if (zox_has(zevice, ZevicePointerRight)) {
                        const byte click = zox_get_value(zevice, ZevicePointerRight)
                        if (devices_get_pressed_this_frame(click)) is_triggered_b = 1;
                    }*/
                }
            } else if (deviceMode->value == zox_device_mode_gamepad && zox_has(device, Gamepad)) {
                const Children *zevices = zox_get(device, Children)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice = zevices->value[k];
                    if (zox_has(zevice, ZeviceButton)) {
                        const DeviceButtonType *deviceButtonType = zox_get(zevice, DeviceButtonType)
                        if (deviceButtonType->value == zox_device_button_x || deviceButtonType->value == zox_device_button_rt) {
                            const ZeviceDisabled *zeviceDisabled = zox_get(zevice, ZeviceDisabled)
                            if (zeviceDisabled->value) {
                                continue;
                            }
                            const ZeviceButton *zeviceButton = zox_get(zevice, ZeviceButton)
                            if (devices_get_pressed_this_frame(zeviceButton->value)){
                                is_triggered_a = 1;
                                // zox_log(" x pressed\n")
                            }
                        } else if (deviceButtonType->value == zox_device_button_y || deviceButtonType->value == zox_device_button_lt) {
                            const ZeviceDisabled *zeviceDisabled = zox_get(zevice, ZeviceDisabled)
                            if (zeviceDisabled->value) {
                                continue;
                            }
                            const ZeviceButton *zeviceButton = zox_get(zevice, ZeviceButton)
                            if (devices_get_pressed_this_frame(zeviceButton->value)) {
                                 // is_triggered_b = 1;
                                 // zox_log(" y pressed\n")
                            }
                        }
                    }
                }
            }
        }
        if (is_triggered_a) zox_set(character, TriggerActionB, { 1 })
        // if (is_triggered_b) zox_set(character, TriggerActionA, { 1 })
    }
} zox_declare_system(Player3DTriggerSystem)