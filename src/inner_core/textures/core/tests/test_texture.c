
ecs_entity_t testTextureEntity;

//! Spawn a Player character.
ecs_entity_t SpawnTexture(ecs_world_t *world, ecs_entity_t prefab)
{
    ecs_entity_t textureEntity = ecs_new_w_pair(world, EcsIsA, prefab);
    printf("Spawned Texture [%lu]\n", (long unsigned int) textureEntity);
    return textureEntity;
}

void TestDestroyTexture(ecs_world_t *world)
{
    if (testTextureEntity && ecs_is_alive(world, testTextureEntity))
    {
        printf("Deleting Texture.\n");
        ecs_delete(world, testTextureEntity);
    }
    else
    {
        printf("Spawning Texture.\n");
        testTextureEntity = SpawnTexture(world, noise_texture_prefab);
    }
}
