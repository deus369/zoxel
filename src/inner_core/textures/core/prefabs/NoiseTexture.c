//! Basic noise texture.
ecs_entity_t noiseTexturePrefab;

void add_texture(ecs_world_t *world, ecs_entity_t prefab, int2 textureSize)
{
    //zoxel_add_component(world, prefab, Texture);
    zoxel_set_component(world, prefab, Texture, { 0, NULL });
    zoxel_set_component(world, prefab, TextureSize, { textureSize });
}

void add_noise_texture(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_add_tag(world, e, NoiseTexture);
    zoxel_set_component(world, e, EntityDirty, { 0 });
    zoxel_set_component(world, e, GenerateTexture, { 1 });
    zoxel_set_component(world, e, AnimateTexture, { 0.0 });
}

void SpawnTexturePrefab(ecs_world_t *world)
{
    const int2 textureSize = { 16, 16 };
    ecs_entity_t e = ecs_new_prefab(world, "texture_prefab");
    printf("Spawned character2D_prefab [%lu].\n", (long int) (e));
    add_seed(world, e, 666);
    add_texture(world, e, textureSize);
    add_noise_texture(world, e);
    noiseTexturePrefab = e;
}