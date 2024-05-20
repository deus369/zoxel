ecs_entity_t testTextureEntity;

//! Spawn a Player character.
ecs_entity_t spawn_texture(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    zoxel_log(" > spawned texture data [%lu]\n", e);
    return e;
}

void TestDestroyTexture(ecs_world_t *world) {
    if (testTextureEntity && zox_alive(testTextureEntity)) {
        zoxel_log("Deleting TextureData.\n");
        zox_delete(testTextureEntity)
    } else {
        zoxel_log("Spawning TextureData.\n");
        testTextureEntity = spawn_texture(world, prefab_texture_noise);
    }
}
