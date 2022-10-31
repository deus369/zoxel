//! Basic noise texture.
ecs_entity_t noiseTexturePrefab;

void AddSeedComponent(ecs_world_t *world, ecs_entity_t prefab, int seed)
{
    ecs_add(world, prefab, Seed);
    ecs_override(world, prefab, Seed);
    ecs_set(world, prefab, Seed, { seed });
}

void AddTextureComponents(ecs_world_t *world, ecs_entity_t prefab, int2 textureSize)
{
    ecs_add(world, prefab, Texture);
    ecs_add(world, prefab, TextureSize);
    ecs_add(world, prefab, Seed);
    ecs_override(world, prefab, Texture);
    ecs_override(world, prefab, Seed);
    ecs_set(world, prefab, TextureSize, { textureSize });
}

void AddTextureNoiseComponents(ecs_world_t *world, ecs_entity_t prefab)
{
    ecs_add(world, prefab, NoiseTexture);
    ecs_add(world, prefab, EntityDirty);
    ecs_override(world, prefab, EntityDirty);
    ecs_set(world, prefab, EntityDirty, { 0 });
    ecs_add(world, prefab, GenerateTexture);
    ecs_override(world, prefab, GenerateTexture);
    ecs_set(world, prefab, GenerateTexture, { 1 });
    ecs_add(world, prefab, AnimateTexture);
    ecs_override(world, prefab, AnimateTexture);
    ecs_set(world, prefab, AnimateTexture, { 0.0 });
}

void InitializeNoiseTexturePrefab(ecs_world_t *world)
{
    const int2 textureSize = { 16, 16 };
    ecs_entity_t texturePrefab = ecs_new_prefab(world, "Noise Texture");
    AddSeedComponent(world, texturePrefab, 666);
    AddTextureComponents(world, texturePrefab, textureSize);
    AddTextureNoiseComponents(world, texturePrefab);
    noiseTexturePrefab = texturePrefab;
}