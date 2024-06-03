extern void prefab_add_texture_generated(ecs_world_t *world, ecs_entity_t e, int2 textureSize, unsigned char generate);

ecs_entity_t prefab_cube_textured;

ecs_entity_t spawn_prefab_cube_textured(ecs_world_t *world) {
    int2 texture_size = { 16, 16 };
    // ecs_entity_t e = spawn_prefab_cube(world);
    // ecs_entity_t e = ecs_clone(world, 0, prefab_cube, 1);
    zox_prefab_child(prefab_cube)
    prefab_add_texture_generated(world, e, texture_size, zox_generate_texture_trigger);
    add_noise_texture(world, e);
    add_gpu_texture(world, e);
    prefab_cube_textured = e;
    return e;
}

ecs_entity_t spawn_cube_textured(ecs_world_t *world, float3 position) {
    ecs_entity_t e = spawn_cube(world, prefab_cube_textured, position);
    if (!headless) {
        spawn_gpu_uvs(world, e);
        spawn_gpu_texture(world, e);
    }
    return e;
}
