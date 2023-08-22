void FreeCameraDisableMovementSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    const CharacterLink *characterLinks = ecs_field(it, CharacterLink, 3);
    for (int i = 0; i < it->count; i++) {
        const CharacterLink *characterLink = &characterLinks[i];
        if (characterLink->value == 0) continue;
        unsigned char toggle_disable_movement = 0;
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (ecs_has(world, device_entity, Mouse)) {
                const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                if (mouse->left.pressed_this_frame) toggle_disable_movement = 1;
            }
        }
        if (toggle_disable_movement) {
            DisableMovement *disableMovement = ecs_get_mut(world, characterLink->value, DisableMovement);
            disableMovement->value = !disableMovement->value;
            ecs_modified(world, characterLink->value, DisableMovement);
            zoxel_log(" > disable movement Toggled [%s]\n", disableMovement->value ? "true" : "false");
        }
    }

} zox_declare_system(FreeCameraDisableMovementSystem)

/*ecs_iter_t playerIter = ecs_query_iter(it->world, it->ctx);
ecs_query_next(&playerIter);
if (playerIter.count == 0) return;
Mouse *mouses = ecs_field(it, Mouse, 1);
DisableMovement *disableMovements = ecs_field(&playerIter, DisableMovement, 2);
for (int i = 0; i < it->count; i++) {
    const Mouse *mouse = &mouses[i];
    if (mouse->left.pressed_this_frame) {
        for (int j = 0; j < playerIter.count; j++) {
            DisableMovement *disableMovement = &disableMovements[j];
            disableMovement->value = !disableMovement->value;
            zoxel_log(" > DisableMovement Toggled [%s]\n", disableMovement->value ? "true" : "false");
        }
    }
}*/