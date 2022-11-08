//! Basic noise texture.
ecs_entity_t noiseTexturePrefab;

void add_noise_texture(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_add_tag(world, e, NoiseTexture);
}

void add_animated_noise_texture(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_add_tag(world, e, NoiseTexture);
    zoxel_set_component(world, e, AnimateTexture, { 0.0 });
}

void SpawnTexturePrefab(ecs_world_t *world)
{
    const int2 textureSize = { 16, 16 };
    ecs_entity_t e = ecs_new_prefab(world, "texture_prefab");
    printf("Spawned character2D_prefab [%lu].\n", (long int) (e));
    add_seed(world, e, 666);
    add_texture(world, e, textureSize);
    add_dirty(world, e);
    add_animated_noise_texture(world, e);
    noiseTexturePrefab = e;
}