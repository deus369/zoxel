const unsigned char realm_voxels = 5;
ecs_entity_t prefab_realm;
ecs_entity_t local_realm;

ecs_entity_t spawn_prefab_realm(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_realm")
    zox_add_tag(e, Realm);
    zox_prefab_set(e, VoxelLinks, { 0, NULL })
    prefab_realm = e;
    return e;
}

ecs_entity_t spawn_realm(ecs_world_t *world) {
    zox_instance(prefab_realm)
    zox_name("realm")
    VoxelLinks *voxelLinks = zox_get_mut(e, VoxelLinks)
    resize_memory_component(VoxelLinks, voxelLinks, ecs_entity_t, realm_voxels)
    for (unsigned char i = 0; i < voxelLinks->length; i++) voxelLinks->value[i] = spawn_voxel(world, i);
    zox_modified(e, VoxelLinks)
    local_realm = e;
    return e;
}

void add_to_labels_textures(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int tree_level) {
    if (!(e && zox_has(e, Textures))) return;
    tree_level++;
    const Textures *component = zox_get(e, Textures)
    for (int i = 0; i < component->length; i++) {
        ecs_entity_t texture = component->value[i];
        add_entity_to_labels(world, texture, labels, entities, tree_level);
        // add_entity_children_to_labels(world, component->value[i], labels, entities, tree_level);
    }
}

void add_to_labels_voxel_links(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int tree_level) {
    if (!(e && zox_has(e, VoxelLinks))) return;
    tree_level++;
    const VoxelLinks *component = zox_get(e, VoxelLinks)
    for (int i = 0; i < component->length; i++) {
        ecs_entity_t voxel = component->value[i];
        add_entity_to_labels(world, voxel, labels, entities, tree_level);
        add_to_labels_textures(world, voxel, labels, entities, tree_level);
    }
}
