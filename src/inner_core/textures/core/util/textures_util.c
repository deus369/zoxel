void add_texture(ecs_world_t *world, ecs_entity_t e, int2 textureSize, unsigned char is_generate) {
    zoxel_add_tag(world, e, Texture);
    zoxel_add(world, e, TextureData);
    zoxel_set(world, e, TextureSize, { textureSize });
    zoxel_set(world, e, TextureDirty, { 0 });
    zoxel_set(world, e, GenerateTexture, { is_generate });
}