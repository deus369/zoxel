void set_element_layers_auto(ecs_world_t *world, const ecs_entity_t e, const byte layer) {
    if (!zox_valid(e)) return;
    const byte new_layer = layer + 1;
    if (zox_has(e, Layer2D)) zox_set(e, Layer2D, { new_layer })
    if (!zox_has(e, Children)) return;
    const Children *children = zox_get(e, Children)
    for (int j = 0; j < children->length; j++) {
        const ecs_entity_t child = children->value[j];
        set_element_layers_auto(world, child, new_layer);
    }
}

void set_element_layers(ecs_world_t *world, const ecs_entity_t e, const byte window_layer) {
    if (!zox_valid(e)) return;
    if (zox_has(e, ElementLayer) && zox_has(e, Layer2D)) {
        const byte element_layer = zox_get_value(e, ElementLayer)
        const byte new_layer = window_layer + element_layer;
        zox_set(e, Layer2D, { new_layer })
    }
    if (!zox_has(e, Children)) return;
    const Children *children = zox_get(e, Children)
    for (int j = 0; j < children->length; j++) {
        const ecs_entity_t child = children->value[j];
        set_element_layers(world, child, window_layer);
    }
}


// todo: implement localLayer2D's here for elements'
byte get_highest_layer(ecs_world_t *world, const ecs_entity_t e, const byte layer) {
    if (!e || !zox_has(e, Children)) return layer;
    const unsigned child_layer = layer + 1;
    unsigned highest_layer = layer;
    const Children *children = zox_get(e, Children)
    for (int j = 0; j < children->length; j++) {
        const ecs_entity_t child = children->value[j];
        const byte new_layer = get_highest_layer(world, child, child_layer);
        // if (new_layer > highest_layer) zox_log("    > [%lu] layers_per_window at %i / %i [%i]\n", e, j, children->length, new_layer)
        if (new_layer > highest_layer) highest_layer = new_layer;
    }
    return highest_layer;
}
