//! Basic noise texture.
ecs_entity_t noiseTexturePrefab;

void AddSeedComponent(ecs_world_t *world, ecs_entity_t prefab, int seed)
{
    zoxel_set_component(world, prefab, Seed, { seed });
}

void AddTextureComponents(ecs_world_t *world, ecs_entity_t prefab, int2 textureSize)
{
    zoxel_add_component(world, prefab, Seed);
    zoxel_add_component(world, prefab, Texture);
    zoxel_set_component(world, prefab, TextureSize, { textureSize });
}

void AddTextureNoiseComponents(ecs_world_t *world, ecs_entity_t prefab)
{
    zoxel_add_tag(world, prefab, NoiseTexture);
    zoxel_set_component(world, prefab, EntityDirty, { 0 });
    zoxel_set_component(world, prefab, GenerateTexture, { 1 });
    zoxel_set_component(world, prefab, AnimateTexture, { 0.0 });
}

void SpawnTexturePrefab(ecs_world_t *world)
{
    const int2 textureSize = { 16, 16 };
    ecs_entity_t texturePrefab = ecs_new_prefab(world, "texture_prefab");
    AddSeedComponent(world, texturePrefab, 666);
    AddTextureComponents(world, texturePrefab, textureSize);
    AddTextureNoiseComponents(world, texturePrefab);
    noiseTexturePrefab = texturePrefab;
}