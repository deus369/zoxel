void on_element_clicked(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t ui) {
    if (zox_has(ui, Clickable)) {
        zox_set(ui, ClickState, { 1 })
        zox_set(ui, Clicker, { player })
    }
}

void raycaster_select_element(ecs_world_t *world, const ecs_entity_t raycaster, const ecs_entity_t element) {
    const ecs_entity_t last_element = zox_get_value(raycaster, RaycasterTarget)
    if (last_element) zox_set(last_element, SelectState, { 0 })
    zox_set(raycaster, RaycasterTarget, { element })
    if (element) zox_set(element, SelectState, { 1 })
}
