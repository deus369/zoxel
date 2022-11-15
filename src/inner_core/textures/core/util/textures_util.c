//! Adds texture and size components.
void add_texture(ecs_world_t *world, ecs_entity_t e, int2 textureSize)
{
    //zoxel_add_tag(world, e, Texture);
    zoxel_set(world, e, GenerateTexture, { 1 });
    zoxel_set(world, e, TextureSize, { textureSize });
    zoxel_add(world, e, Texture);
}

//! Adds texture and size components.
void add_texture_frame(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_add_tag(world, e, FrameTexture);
}