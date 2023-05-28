ecs_entity_t noise_texture_prefab;

void add_noise_texture(ecs_world_t *world, ecs_entity_t e) {
    zox_add_tag(e, NoiseTexture)
}

void add_animated_noise_texture(ecs_world_t *world, ecs_entity_t e) {
    zox_add_tag(e, NoiseTexture)
    zox_set(e, AnimateTexture, { 0 })
}

void spawn_prefab_noise_texture(ecs_world_t *world) {
    /*const int2 textureSize = { 16, 16 };
    zox_prefab()
    printf("Spawned texture_prefab [%lu].\n", (long int) (e));
    add_seed(world, e, 666);
    add_texture(world, e, textureSize);
    add_dirty(world, e);
    add_animated_noise_texture(world, e);
    noise_texture_prefab = e;*/
}