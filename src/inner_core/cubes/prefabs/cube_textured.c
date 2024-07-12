extern void prefab_add_texture_generated(ecs_world_t *world, ecs_entity_t e, int2 textureSize, unsigned char generate);

ecs_entity_t spawn_prefab_cube_textured(ecs_world_t *world, const ecs_entity_t prefab) {
    const int2 texture_size = { 16, 16 };
    zox_prefab_child(prefab)
    prefab_add_texture_generated(world, e, texture_size, zox_generate_texture_trigger);
    add_noise_texture(world, e);
    add_gpu_texture(world, e);
    return e;
}

ecs_entity_t spawn_cube_textured(ecs_world_t *world, const ecs_entity_t prefab, const float3 position) {
    const ecs_entity_t e = spawn_cube(world, prefab, position);
    if (!headless) {
        spawn_gpu_uvs(world, e);
        spawn_gpu_texture(world, e);
    }
    return e;
}
