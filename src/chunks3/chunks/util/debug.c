void add_to_labels_voxel_links(
    ecs *world,
    const entity e,
    text_group_dynamic_array_d* labels,
    entity_array_d* entities,
    int tree_level
) {
    if (!(e && zox_has(e, VoxelLinks))) {
        return;
    }
    tree_level++;
    const VoxelLinks *component = zox_get(e, VoxelLinks)
    for (int i = 0; i < component->length; i++) {
        const entity e2 = component->value[i];
        add_entity_to_labels(world, e2, labels, entities, tree_level);
        add_to_labels_textures(world, e2, labels, entities, tree_level);
    }
}

void key_down_toggle_debug_chunks(ecs *world, int32_t keycode) {
    if (keycode == SDLK_F4) {
        is_render_chunk_edges = !is_render_chunk_edges;
    }
}