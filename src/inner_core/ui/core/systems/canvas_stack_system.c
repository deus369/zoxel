// #define zox_debug_canvas_stack

void CanvasStackSystem(ecs_iter_t *it) {
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
            if (!child|| !zox_has(child, Window)) continue;
            const unsigned char window_layers = get_highest_layer(world, child, 1);
            if (window_layers > layers_per_window) layers_per_window = window_layers;
            windows_count++;
        }
        // gett previous window layer of moving to top window
        const unsigned char old_window_layer = zox_get_value(windowToTop->value, WindowLayer)
        if (windows_count == windowsCount->value && old_window_layer == windows_count) { // skip event, same window clicked as already on top
            windowToTop->value = 0;
#ifdef zox_debug_canvas_stack
            zox_log(" > skipping stack refresh as same window as last selected\n", old_window_layer)
#endif
            continue;
        }
        zox_set(windowToTop->value, SetWindowLayer, { windows_count })
        windowsLayers->value = layers_per_window;
        unsigned char old_windows_count = windowsCount->value;
        unsigned char not_assigned_index = windowsCount->value + 1; // start on top of stack, but below latest
        // if (old_windows_count > windows_count) not_assigned_index = 1;  // temporary fixed deletion just be reassigning new stack indexes lol
        const int max_checks = 255;
        windowsCount->value = windows_count;
        int_hashmap *windows = create_int_hashmap(windows_count);
        int_hashmap_add(windows, windows_count, windowToTop->value);
#ifdef zox_debug_canvas_stack
        zox_log(" >  canvas stack system refreshing [%i] out of [%i]\n", windows_count, children->length)
        zox_log("   - [%i] event WindowLayer [%lu]\n", windows_count, windowToTop->value)
#endif
        for (int j = 0; j < children->length; j++) {
            const ecs_entity_t child = children->value[j];
            if (!zox_valid(child) || !zox_has(child, Window)) continue;
            if (windowToTop->value == child) continue;
            unsigned char child_window_layer = zox_get_value(child, WindowLayer)
            if (child_window_layer == 0) {
                // if (int_hashmap_has(windows, not_assigned_index)) zox_log("   ! issue with index, possible removal\n")
                unsigned char new_layer = not_assigned_index;
                int checks = 0;
                while (int_hashmap_has(windows, new_layer)) {
                    if (new_layer == 1) new_layer = old_windows_count;
                    else new_layer--;
#ifdef zox_debug_canvas_stack
                    zox_log("   ! issue with index, lowering [%i]\n", new_layer)
#endif
                    checks++;
                    if (checks > max_checks) return; // failure!
                }
                int_hashmap_add(windows, new_layer, windowToTop->value);
                zox_set(child, SetWindowLayer, { new_layer })
                not_assigned_index++;
#ifdef zox_debug_canvas_stack
                zox_log("   - [%i] setting new child WindowLayer [%lu]\n", new_layer, child)
#endif
            } else if (old_window_layer != 0 && child_window_layer > old_window_layer) {
                unsigned char new_layer = child_window_layer - 1;
                if (new_layer > windows_count - 1) new_layer = windows_count - 1;
                int checks = 0;
                while (int_hashmap_has(windows, new_layer)) {
                    if (new_layer == 1) new_layer = old_windows_count;
                    else new_layer--;
#ifdef zox_debug_canvas_stack
                    zox_log("   ! issue with index, lowering [%i]\n", new_layer)
#endif
                    checks++;
                    if (checks > max_checks) return; // failure!
                }
                int_hashmap_add(windows, new_layer, child);
                zox_set(child, SetWindowLayer, { new_layer })
#ifdef zox_debug_canvas_stack
                zox_log("   - [%i] decreasing WindowLayer [%lu]\n", new_layer, child)
#endif
            } else {
                if (int_hashmap_has(windows, child_window_layer)) {
                    unsigned char new_layer = child_window_layer;
                    int checks = 0;
                    while (int_hashmap_has(windows, new_layer)) {
                        if (new_layer == 1) new_layer = old_windows_count;
                        else new_layer--;
    #ifdef zox_debug_canvas_stack
                        zox_log("   ! issue with index, lowering [%i]\n", new_layer)
    #endif
                        checks++;
                        if (checks > max_checks) return; // failure!
                    }
                    int_hashmap_add(windows, new_layer, child);
                    zox_set(child, SetWindowLayer, { new_layer })
    #ifdef zox_debug_canvas_stack
                    zox_log("   - [%i] anew WindowLayer [%lu]\n", new_layer, child)
    #endif
                } else {
                    int_hashmap_add(windows, child_window_layer, child);
#ifdef zox_debug_canvas_stack
                    zox_log("   - [%i] keeping WindowLayer [%lu]\n", child_window_layer, child)
#endif
                }
            }
        }
        // ecs_entity_t window = int3_hashmap_get(windows, j);
        int_hashmap_dispose(windows);
        windowToTop->value = 0;
        // has_changed = 1;
    }
    // what does ecs_query_skip acttuauauaallly do
    // if (!has_changed) ecs_query_skip(it);
} zox_declare_system(CanvasStackSystem)
