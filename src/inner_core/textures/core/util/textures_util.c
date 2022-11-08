//! Adds texture and size components.
void add_texture(ecs_world_t *world, ecs_entity_t e, int2 textureSize)
{
    //zoxel_add_tag(world, e, Texture);
    zoxel_add_component(world, e, Texture); // , { 0, NULL });
    zoxel_set_component(world, e, TextureSize, { textureSize });
    zoxel_set_component(world, e, GenerateTexture, { 1 });
}

//! Adds texture and size components.
void add_texture_frame(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_add_tag(world, e, FrameTexture);
}