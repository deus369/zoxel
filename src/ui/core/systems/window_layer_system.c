void WindowLayerSystem(ecs_iter_t *it) {
    // zox_change_check()
    zox_field_world()
    zox_field_in(SetWindowLayer, setWindowLayers, 1)
    zox_field_in(CanvasLink, canvasLinks, 2)
    zox_field_in(Children, childrens, 3)
    zox_field_out(WindowLayer, windowLayers, 4)
    zox_field_out(Layer2D, layer2Ds, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(SetWindowLayer, setWindowLayers, setWindowLayer)
        zox_field_o(WindowLayer, windowLayers, windowLayer)
        if (windowLayer->value == setWindowLayer->value) continue;
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        if (!canvasLink->value) continue;
        zox_field_i(Children, childrens, children)
        zox_field_o(Layer2D, layer2Ds, layer2D)
        const byte layers_per_window = zox_get_value(canvasLink->value, WindowsLayers)
        windowLayer->value = setWindowLayer->value;
        const byte window_layer = windowLayer->value;
        layer2D->value = window_layer * layers_per_window;
        for (int j = 0; j < children->length; j++) {
            const ecs_entity_t child = children->value[j];
            set_element_layers_auto(world, child, layer2D->value);
            set_element_layers(world, child, layer2D->value);
        }
    }
} zox_declare_system(WindowLayerSystem)
