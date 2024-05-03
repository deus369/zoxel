// #define zox_debug_canvas_stack

unsigned char get_highest_layer(ecs_world_t *world, const ecs_entity_t e, const unsigned char layer) {
    if (!zox_has(e, Children)) return layer;
    const unsigned child_layer = layer + 1;
    unsigned highest_layer = layer;
    const Children *children = zox_get(e, Children)
    for (int j = 0; j < children->length; j++) {
        const unsigned char new_layer = get_highest_layer(world, children->value[j], child_layer);
        // if (new_layer > highest_layer) zox_log("    > [%lu] layers_per_window at %i / %i [%i]\n", e, j, children->length, new_layer)
        if (new_layer > highest_layer) highest_layer = new_layer;
    }
    return highest_layer;
}

void CanvasStackSystem(ecs_iter_t *it) {
    unsigned char has_changed = 0;
    zox_iter_world()
    zox_field_in(Children, childrens, 1)
    zox_field_out(WindowToTop, windowToTops, 2)
    zox_field_out(WindowsLayers, windowsLayerss, 3)
    zox_field_out(WindowsCount, windowsCounts, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(WindowToTop, windowToTops, windowToTop)
        if (!windowToTop->value) continue;
        if (!zox_has(windowToTop->value, Window)) {
            windowToTop->value = 0;
            // zox_log(" > windowToTop->value set wrongly\n")
            continue;
        }
        zox_field_i_in(Children, childrens, children)
        zox_field_i_out(WindowsLayers, windowsLayerss, windowsLayers)
        zox_field_i_out(WindowsCount, windowsCounts, windowsCount)
        unsigned char windows_count = 0; // maybe count windows first
        unsigned char layers_per_window = 1;
        for (int j = 0; j < children->length; j++) {
            const ecs_entity_t child = children->value[j];
            if (!zox_valid(child) || !zox_has(child, Window)) continue;
            windows_count++;
            unsigned char window_layers = get_highest_layer(world, child, 1);
            // if (window_layers > layers_per_window) zox_log(" > layers_per_window %i [%i]\n", j, window_layers)
            if (window_layers > layers_per_window) layers_per_window = window_layers;
        }
        // zox_log(" > windows_count [%i]\n", windows_count)
        // zox_log(" > layers_per_window [%i]\n", layers_per_window)
        // gett previous window layer of moving to top window
        const unsigned char old_window_layer = zox_get_value(windowToTop->value, WindowLayer)
        if (old_window_layer == windows_count) { // skip event, same window clicked as already on top
            windowToTop->value = 0;
            continue;
        }
        zox_set(windowToTop->value, SetWindowLayer, { windows_count })
        windowsLayers->value = layers_per_window;
        unsigned char old_windows_count = windowsCount->value;
        unsigned char not_assigned_index = windowsCount->value + 1; // start on top of stack, but below latest
        if (old_windows_count > windows_count) not_assigned_index = 1;  // temporary fixed deletion just be reassigning new stack indexes lol
        windowsCount->value = windows_count;
#ifdef zox_debug_canvas_stack
        zox_log(" >  canvas stack system refreshing [%i] out of [%i]\n", windows_count, children->length)
        zox_log("   - [%i] event WindowLayer [%lu]\n", windows_count, windowToTop->value)
#endif
        for (int j = 0; j < children->length; j++) {
            const ecs_entity_t child = children->value[j];
            if (!zox_valid(child) || !zox_has(child, Window)) continue;
            if (windowToTop->value == child) continue;
            const unsigned char child_window_layer = zox_get_value(child, WindowLayer)
            if (old_window_layer != 0 && child_window_layer < old_window_layer) continue;
            if (child_window_layer == 0 || old_windows_count > windows_count) {
#ifdef zox_debug_canvas_stack
                zox_log("   - [%i] setting new child WindowLayer [%lu]\n", not_assigned_index, child)
#endif
                zox_set(child, SetWindowLayer, { not_assigned_index })
                not_assigned_index++;
            } else if (old_window_layer == 0) {
#ifdef zox_debug_canvas_stack
                zox_log("   - [%i] keeping WindowLayer [%lu]\n", child_window_layer, child)
#endif
                continue;
            } else {
                zox_set(child, SetWindowLayer, { child_window_layer - 1 })
#ifdef zox_debug_canvas_stack
                zox_log("   - [%i] setting old child WindowLayer [%lu]\n", (child_window_layer - 1), child)
#endif
            }
        }
        windowToTop->value = 0;
        has_changed = 1;
    }
    if (!has_changed) ecs_query_skip(it);
} zox_declare_system(CanvasStackSystem)
