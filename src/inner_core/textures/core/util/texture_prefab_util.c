void prefab_add_texture(ecs_world_t *world, const ecs_entity_t e, const int2 size) {
    zox_add_tag(e, Texture)
    zox_add(e, TextureData)
    zox_prefab_set(e, TextureSize, { size })
    zox_prefab_set(e, TextureDirty, { 0 })
}


void prefab_add_texture_generated(ecs_world_t *world, const ecs_entity_t e, const int2 size, const unsigned char is_generate) {
    prefab_add_texture(world, e, size);
    add_seed(world, e, 666);
    zox_prefab_set(e, GenerateTexture, { is_generate })
}
