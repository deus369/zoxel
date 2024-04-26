void toggle_ui(ecs_world_t *world, ecs_entity_t *e, ecs_entity_t (*spawn_ui)(ecs_world_t*, const ecs_entity_t)) {
    if (*e == 0) {
        const ecs_entity_t e2 = (*spawn_ui)(world, main_canvas);
        *e = e2;
    } else {
        zox_delete(*e)
        *e = 0;
    }
}

// if player device mode is gamepad, select pause ui
#ifdef zoxel_include_players
extern void raycaster_select_ui_mut(ecs_world_t *world, ecs_entity_t raycaster_entity, ecs_entity_t ui_entity);

void select_first_button(ecs_world_t *world, const ecs_entity_t first_button, const ecs_entity_t player) {
    const DeviceMode *deviceMode = zox_get(player, DeviceMode)
    if (deviceMode->value == zox_device_mode_gamepad) {
        zox_log(" > selecting first pause ui button [%lu]\n", first_button)
        raycaster_select_ui_mut(world, player, first_button);
    }
}
#endif
