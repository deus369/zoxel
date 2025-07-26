void WindowLayerSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(SetWindowLayer)
    zox_sys_in(CanvasLink)
    zox_sys_in(Children)
    zox_sys_out(WindowLayer)
    zox_sys_out(Layer2D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(SetWindowLayer, setWindowLayer)
        zox_sys_i(CanvasLink, canvasLink)
        zox_sys_i(Children, children)
        zox_sys_o(WindowLayer, windowLayer)
        zox_sys_o(Layer2D, layer2D)
        if (windowLayer->value == setWindowLayer->value) {
            continue;
        }
        if (!zox_valid(canvasLink->value) || !zox_has(canvasLink->value, WindowsLayers)) {
            continue;
        }
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
