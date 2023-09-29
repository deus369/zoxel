const unsigned char realm_voxels = 5;
ecs_entity_t prefab_realm;
ecs_entity_t local_realm;

ecs_entity_t spawn_prefab_realm(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_realm")
    zox_add_tag(e, Realm);
    zox_set(e, VoxelLinks, { 0, NULL })
    prefab_realm = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" + spawn_prefab realm [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_realm(ecs_world_t *world) {
    zox_instance(prefab_realm)
    zox_name("realm")
    // spawn voxels
    // todo: rename VoxelLinks to Voxels for realm, signifying parent relationship
    VoxelLinks *voxelLinks = ecs_get_mut(world, e, VoxelLinks);
    resize_memory_component(VoxelLinks, voxelLinks, ecs_entity_t, realm_voxels)
    for (unsigned char i = 0; i < voxelLinks->length; i++) {
        ecs_entity_t voxel_entity = spawn_voxel(world, i);
        voxelLinks->value[i] = voxel_entity;
    }
    ecs_modified(world, e, VoxelLinks);
    local_realm = e;
    #ifdef zoxel_debug_spawns
        zoxel_log(" + spawned realm [%lu]\n", (long int) e);
    #endif
    return e;
}