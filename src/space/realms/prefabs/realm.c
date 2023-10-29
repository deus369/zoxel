const unsigned char realm_voxels = 5;
ecs_entity_t prefab_realm;
ecs_entity_t local_realm;

ecs_entity_t spawn_prefab_realm(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_realm")
    zox_add_tag(e, Realm);
    zox_prefab_set(e, VoxelLinks, { 0, NULL })
    prefab_realm = e;
    #ifdef zoxel_debug_prefabs
        zox_log(" + spawn_prefab realm [%lu]\n", e)
    #endif
    return e;
}

ecs_entity_t spawn_realm(ecs_world_t *world) {
    zox_instance(prefab_realm)
    zox_name("realm")
    VoxelLinks *voxelLinks = zox_get_mut(e, VoxelLinks) // todo: rename VoxelLinks to Voxels
    resize_memory_component(VoxelLinks, voxelLinks, ecs_entity_t, realm_voxels)
    for (unsigned char i = 0; i < voxelLinks->length; i++) voxelLinks->value[i] = spawn_voxel(world, i);
    zox_modified(e, VoxelLinks)
    local_realm = e;
    #ifdef zoxel_debug_spawns
        zox_log(" + spawned realm [%lu]\n", e)
    #endif
    return e;
}

void add_entity_textures_to_labels(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int tree_level) {
    if (!e) return;
    add_entity_to_labels(world, e, labels, entities, tree_level);
    if (zox_has(e, Textures)) {
        tree_level++;
        const Textures *component = zox_get(e, Textures)
        for (int i = 0; i < component->length; i++) add_entity_children_to_labels(world, component->value[i], labels, entities, tree_level);
    }
}

void add_realm_entity_to_labels(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int tree_level) {
    if (!e) return;
    add_entity_to_labels(world, e, labels, entities, tree_level);
    if (zox_has(e, VoxelLinks)) {
        tree_level++;
        const VoxelLinks *component = zox_get(e, VoxelLinks)
        for (int i = 0; i < component->length; i++) add_entity_textures_to_labels(world, component->value[i], labels, entities, tree_level);
    }
}
