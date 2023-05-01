//! Adds texture and size components.
void add_texture(ecs_world_t *world, ecs_entity_t e, int2 textureSize, unsigned char generate) {   // 1
    //zoxel_add_tag(world, e, Texture);
    zoxel_add(world, e, Texture);   // TextureData
    zoxel_set(world, e, TextureSize, { textureSize });
    zoxel_set(world, e, TextureDirty, { 0 });
    zoxel_set(world, e, GenerateTexture, { generate });
}

//! Adds texture and size components.
/*void add_texture_frame(ecs_world_t *world, ecs_entity_t e) {
    zoxel_add_tag(world, e, FrameTexture);
}*/

/*void initialize_texture(ecs_world_t *world, ecs_entity_t e, int2 textureSize) {
    Texture texture = { };
    initialize_memory_component_non_pointer(texture, ecs_entity_t, textureSize.x * textureSize.y);
    ecs_set(world, e, Texture, { texture.length, texture.value });
}*/