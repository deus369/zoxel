void add_noise_texture(ecs_world_t *world, ecs_entity_t e) {
    zox_add_tag(e, NoiseTexture)
}

void add_animated_noise_texture(ecs_world_t *world, ecs_entity_t e) {
    zox_add_tag(e, NoiseTexture)
    zox_prefab_set(e, AnimateTexture, { 0 })
}

ecs_entity_t spawn_prefab_texture_noise(ecs_world_t *world, const int2 texture_size) {
    zox_prefab()
    zox_prefab_name("texture")
    zox_add_tag(e, Texture)
    zox_prefab_set(e, TextureData, { 0, NULL })
    zox_prefab_set(e, TextureSize, { texture_size })
    zox_prefab_set(e, TextureDirty, { 0 })
    zox_prefab_set(e, Seed, { 666 })
    zox_prefab_set(e, GenerateTexture, { zox_generate_texture_trigger })
    add_noise_texture(world, e);
    zox_prefab_set(e, Color, { color_red })
    return e;
}
