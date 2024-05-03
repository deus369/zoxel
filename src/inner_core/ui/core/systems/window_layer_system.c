void set_element_layers(ecs_world_t *world, const ecs_entity_t e, const unsigned char layer) {
    const unsigned char new_layer = layer + 1;
    if (zox_has(e, Layer2D)) zox_set(e, Layer2D, { new_layer })
    if (!zox_has(e, Children)) return;
    const Children *children = zox_get(e, Children)
    for (int j = 0; j < children->length; j++) {
        const ecs_entity_t child = children->value[j];
        set_element_layers(world, child, new_layer);
    }
}

void WindowLayerSystem(ecs_iter_t *it) {
    // zox_change_check()
    // zox_log(" window layer changed\n")
    zox_iter_world()
    zox_field_in(SetWindowLayer, setWindowLayers, 1)
    zox_field_in(CanvasLink, canvasLinks, 2)
    zox_field_in(Children, childrens, 3)
    zox_field_out(WindowLayer, windowLayers, 4)
    zox_field_out(Layer2D, layer2Ds, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(SetWindowLayer, setWindowLayers, setWindowLayer)
        zox_field_i_out(WindowLayer, windowLayers, windowLayer)
        if (windowLayer->value == setWindowLayer->value) continue;
        zox_field_i_in(CanvasLink, canvasLinks, canvasLink)
        zox_field_i_in(Children, childrens, children)
        zox_field_i_out(Layer2D, layer2Ds, layer2D)
        const unsigned char layers_per_window = zox_get_value(canvasLink->value, WindowsLayers)
        windowLayer->value = setWindowLayer->value;
        const unsigned char window_layer = windowLayer->value;
        // zox_log(" > window [%lu] layer to [%i]\n", it->entities[i], window_layer)
        layer2D->value = window_layer * layers_per_window;
        for (int j = 0; j < children->length; j++) {
            const ecs_entity_t child = children->value[j];
            if (!zox_valid(child)) continue;
            set_element_layers(world, child, layer2D->value);
        }
    }
} zox_declare_system(WindowLayerSystem)
