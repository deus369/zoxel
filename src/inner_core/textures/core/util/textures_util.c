void add_texture(ecs_world_t *world, ecs_entity_t e, int2 textureSize, unsigned char is_generate) {
    zox_add_tag(e, Texture);
    zox_add(e, TextureData);
    zox_set(e, TextureSize, { textureSize });
    zox_set(e, TextureDirty, { 0 });
    zox_set(e, GenerateTexture, { is_generate });
}