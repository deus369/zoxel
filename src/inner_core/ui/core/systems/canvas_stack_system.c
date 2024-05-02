void set_element_layers(ecs_world_t *world, const ecs_entity_t e, const unsigned char layer) {
    if (zox_has(e, Layer2D)) zox_set(e, Layer2D, { layer })
    if (!zox_has(e, Children)) return;
    const Children *children = zox_get(e, Children)
    for (int j = 0; j < children->length; j++) {
        const ecs_entity_t child = children->value[j];
        set_element_layers(world, child, layer + 1);
    }
}

// count the highest children count so we can dynamically set layers_per_window
// int count_window_children();
// todo: also remember WindowLayer's set, so we can keep stack organized and just move window up
// todo: fix window headers, make body a child, atm clicking header over another window breaks, because it restacks the window under the header ui

void CanvasStackSystem(ecs_iter_t *it) {
    const unsigned char layers_per_window = 6;
    zox_iter_world()
    zox_field_in(Children, childrens, 1)
    zox_field_out(WindowToTop, windowToTops, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(WindowToTop, windowToTops, windowToTop)
        if (!windowToTop->value) continue;
        zox_field_i_in(Children, childrens, children)
        unsigned char windows_count = 0; // maybe count windows first
        for (int j = 0; j < children->length; j++) {
            const ecs_entity_t child = children->value[j];
            if (!zox_valid(child) || !zox_has(child, Window)) continue;
            windows_count++;
        }
        unsigned char window_layer = 1;
        for (int j = 0; j < children->length; j++) {
            const ecs_entity_t child = children->value[j];
            if (!zox_valid(child) || !zox_has(child, Window)) continue;
            if (windowToTop->value == child) set_element_layers(world, child, windows_count * layers_per_window);
            else {
                set_element_layers(world, child, window_layer * layers_per_window);
                window_layer++;
            }
        }
        windowToTop->value = 0;
    }
} zox_declare_system(CanvasStackSystem)
