//! Basic noise texture.
ecs_entity_t character2DPrefab;

void SpawnCharacter2DPrefab(ecs_world_t *world, int2 textureSize)
{
    ecs_entity_t e = ecs_new_prefab(world, "character2D_prefab");
    printf("Spawned character2D_prefab [%lu].\n", (long int) (e));
    #ifdef Zoxel_Transforms2D
    AddTransforms2DComponents(world, e);
    #endif
    #ifdef Zoxel_Physics2D
    zoxel_add_tag(world, e, Frictioned);
    AddPhysics2DComponents(world, e);
    #endif
    // rendering
    zoxel_add_component(world, e, Brightness);
    AddGPUMaterialComponents(world, e);
    AddSeedComponent(world, e, 444);
    AddTextureComponents(world, e, textureSize);
    AddTextureNoiseComponents(world, e);
    AddGPUTextureComponents(world, e);
    character2DPrefab = e;
}