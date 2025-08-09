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

extern entity prefab_chunk_height;
extern ecs_entity_t get_linked_terrain(ecs_world_t*, ecs_entity_t);

void toggle_debug_bounds_terrain(ecs_world_t *world) {

    const ecs_entity_t realm = local_realm;
    if (!zox_valid(realm)) return;
    const ecs_entity_t terrain = get_linked_terrain(world, realm);
    if (!zox_valid(terrain)) return;

    byte mode = zox_get_value(prefab_chunk_height, DebugCubeLines);
    cycle_cubeline_debug(&mode);
    zox_set(prefab_chunk_height, DebugCubeLines, { mode });
    zox_geter(terrain, ChunkLinks, chunkLinks);
    for (uint i = 0; i < chunkLinks->value->size; i++) {
        int3_hashmap_pair* pair = chunkLinks->value->data[i];
        uint checks = 0;
        while (pair != NULL && checks < max_safety_checks_hashmap) {
            ecs_entity_t c = pair->value;
            if (zox_valid(c)) {
                zox_set(c, DebugCubeLines, { mode });
            }
            pair = pair->next;
            checks++;
        }
    }
}

void key_down_toggle_debug_chunks(ecs *world, int32_t keycode) {
    if (keycode == SDLK_F4) {
        is_render_chunk_edges = !is_render_chunk_edges;
        toggle_debug_bounds_terrain(world);
    }
}