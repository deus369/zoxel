void on_element_clicked(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t ui) {
    if (zox_has(ui, Clickable)) {
        // zox_set(ui, ClickState, { 1 }) // i made it like this due to some complication
        ClickState *clickState = zox_get_mut(ui, ClickState)
        clickState->value = 1;
        zox_modified(ui, ClickState)
        Clicker *clicker = zox_get_mut(ui, Clicker)
        clicker->value = player;
        zox_modified(ui, Clicker)
    }
}


void set_element_brightness_mut(ecs_world_t *world, const ecs_entity_t e, const float value) {
    if (!e) return;
    Brightness *brightness = zox_get_mut(e, Brightness)
    if (brightness->value != value) {
        brightness->value = value;
        zox_modified(e, Brightness);
    }
}

void set_selectable_state_mut(ecs_world_t *world, const ecs_entity_t ui_entity, const unsigned char state) {
    if (ui_entity != 0) { // && ecs_is_alive(world, ui_entity) && zox_has(ui_entity, SelectState)) {
        SelectState *selectState = zox_get_mut(ui_entity, SelectState)
        if (selectState->value != state) {
            selectState->value = state;
            zox_modified(ui_entity, SelectState);
            // zoxel_log(" > setting [%lu]'s state %i\n", ui_entity, state);
        }
#ifdef zoxel_debug_ui_selectable_states
        else {
            zox_log(" ! [%lu]'s state was already %i\n", ui_entity, state)
        }
#endif
    }
#ifdef zoxel_debug_ui_selectable_states
    else {
        zox_log(" ! [%lu]'s ui had no selectable state!\n", ui_entity)
    }
#endif
}

void raycaster_select_ui(ecs_world_t *world, RaycasterTarget *raycasterTarget, const ecs_entity_t ui_entity) {
    if (raycasterTarget->value != ui_entity) {
        if (raycasterTarget->value && zox_alive(raycasterTarget->value)) set_selectable_state_mut(world, raycasterTarget->value, 0);
        raycasterTarget->value = ui_entity;
        // zox_log(" ===== UI SELECTED [%lu] =====\n",  ui_entity)
        /*if (raycasterTarget->value != 0) zox_set(raycasterTarget->value, SelectState, { 0 })
        if (ui_entity != 0) zox_set(ui_entity, SelectState, { 1 })*/
    }
}

void raycaster_select_ui_mut(ecs_world_t *world, const ecs_entity_t raycaster_entity, const ecs_entity_t ui_entity) {
    RaycasterTarget *raycasterTarget = zox_get_mut(raycaster_entity, RaycasterTarget)
    if (raycasterTarget->value != ui_entity) {
        raycaster_select_ui(world, raycasterTarget, ui_entity);
        zox_modified(raycaster_entity, RaycasterTarget)
        set_selectable_state_mut(world, ui_entity, 1);
        zox_set(raycaster_entity, RaycasterTarget, { ui_entity })
        // zox_log(" > raycaster_select_ui_mut : selecting [%lu]\n", ui_entity)
    }
#ifdef zoxel_debug_ui_selectable_states
    else zox_log(" ! [%lu]'s was already set\n", ui_entity)
#endif
}

void raycaster_select_element(ecs_world_t *world, const ecs_entity_t raycaster, const ecs_entity_t element) {
    zox_set(raycaster, RaycasterTarget, { element })
    zox_set(element, SelectState, { 1 })
}
