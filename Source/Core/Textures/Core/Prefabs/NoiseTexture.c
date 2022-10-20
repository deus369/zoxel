//! Basic noise texture.
ecs_entity_t noiseTexturePrefab;

void InitializeNoiseTexturePrefab(ecs_world_t *world)
{
    const int2 textureSize = { 16, 16 };
    ecs_entity_t texturePrefab = ecs_new_prefab(world, "Noise Texture");
    ecs_add(world, texturePrefab, NoiseTexture);
    ecs_add(world, texturePrefab, EntityDirty);
    ecs_add(world, texturePrefab, GenerateTexture);
    ecs_add(world, texturePrefab, Seed);
    ecs_add(world, texturePrefab, TextureSize);
    ecs_add(world, texturePrefab, Texture);
    ecs_override(world, texturePrefab, Seed);
    ecs_override(world, texturePrefab, Texture);
    ecs_override(world, texturePrefab, EntityDirty);
    ecs_override(world, texturePrefab, GenerateTexture);
    ecs_set(world, texturePrefab, Seed, { 666 });
    ecs_set(world, texturePrefab, EntityDirty, { 0 });
    ecs_set(world, texturePrefab, TextureSize, { textureSize });
    ecs_set(world, texturePrefab, GenerateTexture, { 1 });
    noiseTexturePrefab = texturePrefab;
}