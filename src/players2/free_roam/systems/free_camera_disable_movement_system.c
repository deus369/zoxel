/*
 void FreeCameraDisableMovementSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(DeviceLinks, deviceLinkss, 2)
    zox_field_in(CharacterLink, characterLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CharacterLink, characterLinks, characterLink)
        const ecs_entity_t character = characterLink->value;
        if (!character || !zox_has(character, DisableMovement)) continue;
        byte toggle_disable_movement = 0;
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has(device_entity, Mouse)) {
                const Mouse *mouse = zox_get(device_entity, Mouse)
                if (mouse->left.pressed_this_frame) toggle_disable_movement = 1;
            }
        }
        if (toggle_disable_movement) {
            DisableMovement *disableMovement = zox_get_mut(character, DisableMovement)
            disableMovement->value = !disableMovement->value;
            zox_modified(character, DisableMovement);
            zox_log(" > disable movement Toggled [%s]\n", disableMovement->value ? "true" : "false")
        }
    }
} zox_declare_system(FreeCameraDisableMovementSystem)
*/
