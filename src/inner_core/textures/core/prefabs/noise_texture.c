void add_noise_texture(ecs_world_t *world, ecs_entity_t e) {
    zox_add_tag(e, NoiseTexture)
}

void add_animated_noise_texture(ecs_world_t *world, ecs_entity_t e) {
    zox_add_tag(e, NoiseTexture)
    zox_prefab_set(e, AnimateTexture, { 0 })
}

ecs_entity_t spawn_prefab_texture_noise(ecs_world_t *world, const int2 texture_size) {
    zox_prefab()
    zox_prefab_name("prefab_texture")
    prefab_add_texture_generated(world, e, texture_size, 1);
    add_noise_texture(world, e);
    zox_prefab_set(e, Color, {{ 255, 0, 0, 255 }})
    return e;
}
