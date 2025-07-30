// need functions:
//      add_taskbar_button
//      - spawn function, component_type, texture_name, etc

typedef struct {
    byte window_type;
    ecs_entity_t component_id;
    char *texture_name;
    ecs_entity_t (*spawn)(ecs_world_t *, const ecs_entity_t);
} hook_taskbar;
zoxel_dynamic_array(hook_taskbar)
hook_taskbar_array_d* hook_taskbars;

void initialize_hook_taskbar() {
    hook_taskbars = create_hook_taskbar_array_d(initial_dynamic_array_size);
}

void dispose_hook_taskbar() {
    dispose_hook_taskbar_array_d(hook_taskbars);
}

void add_taskbar_button(const hook_taskbar data) {
    add_to_hook_taskbar_array_d(hook_taskbars, data);
}

// set active stat based on ui component id
void taskbar_set_icons(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t frame, const int i) {
    hook_taskbar hook = hook_taskbars->data[i];
    if_has_child_with_id(canvas, hook.component_id) {
        zox_set(frame, ActiveState, { 1 })
    }
}

void taskbar_button_click_event(ecs_world_t *world, const ClickEventData *event) {
    const byte index = zox_get_value(event->clicked, IconIndex)
    if (index >= hook_taskbars->size) {
        zox_log_error("taskbar button index [%i] out of bounds [%zu]", index, hook_taskbars->size)
        return;
    }
    hook_taskbar hook = hook_taskbars->data[index];
    const ecs_entity_t window_ui = toggle_ui_with_id(world, *hook.spawn, hook.component_id, event->clicker);
    const ecs_entity_t frame = zox_get_value(event->clicked, ParentLink)
    if (!zox_valid(frame) || !zox_has(frame, ActiveState)) {
        zox_log(" ! invalid frame\n")
        return;
    }
    byte window_state = zox_valid(window_ui);
    zox_set(frame, ActiveState, { window_state })
}

/*for (int i = 0; i < load_shader_functions->size; i++) {
    if (load_shader_functions->data[i].value != NULL) (*load_shader_functions->data[i].value)(world);
 }*/