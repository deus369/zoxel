
ecs_entity_t testTextureEntity;

//! Spawn a Player character.
ecs_entity_t SpawnTexture(ecs_world_t *world, ecs_entity_t prefab) {
    ecs_defer_begin(world);
    // ecs_entity_t textureEntity = ecs_new_w_pair(world, EcsIsA, prefab);
    zox_instance(prefab)
    zoxel_log(" > spawned texture data [%lu]\n", e);
    ecs_defer_end(world);
    return e;
}

void TestDestroyTexture(ecs_world_t *world) {
    if (testTextureEntity && ecs_is_alive(world, testTextureEntity)) {
        zoxel_log("Deleting TextureData.\n");
        zox_delete(testTextureEntity)
    } else {
        zoxel_log("Spawning TextureData.\n");
        testTextureEntity = SpawnTexture(world, noise_texture_prefab);
    }
}
