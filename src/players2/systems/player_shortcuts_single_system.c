// Shortcuts for player that require main thread
void PlayerShortcutsMainThreadSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    //zox_field_in(CanvasLink, canvasLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        //zox_field_i(CanvasLink, canvasLinks, canvasLink)
        //const ecs_entity_t canvas = canvasLink->value;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!device) continue;
            if (zox_has(device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard)
                if (keyboard->k.pressed_this_frame) {
                    const ecs_entity_t character = zox_get_value(it->entities[i], CharacterLink)
                    if (!character) continue;
                    if (zox_has(character, Aura)) {
                        zox_remove_tag(character, Aura)
                        zox_log(" > removed Aura from character\n")
                    } else {
                        zox_add_tag(character, Aura)
                        zox_log(" > added Aura to character\n")
                    }
                }
            }
        }
    }
} zox_declare_system(PlayerShortcutsMainThreadSystem)
