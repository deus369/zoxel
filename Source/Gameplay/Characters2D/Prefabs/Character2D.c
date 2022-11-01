//! Basic noise texture.
ecs_entity_t character2DPrefab;
extern void AddSeedComponent(ecs_world_t *world, ecs_entity_t prefab, int seed);
extern void AddTextureComponents(ecs_world_t *world, ecs_entity_t prefab, int2 textureSize);
extern void AddTextureNoiseComponents(ecs_world_t *world, ecs_entity_t prefab);

void InitializeCharacter2DPrefab(ecs_world_t *world)
{
    const int2 textureSize = { 16, 16 };
    character2DPrefab = ecs_new_prefab(world, "Character2D");
    ecs_set(world, character2DPrefab, Position2D, { { 0, 0 } });
    ecs_set(world, character2DPrefab, Velocity2D, { { 0, 0 } });
    ecs_set(world, character2DPrefab, Scale1D, { 1 });
    ecs_override(world, character2DPrefab, Position2D);
    ecs_override(world, character2DPrefab, Rotation2D);
    ecs_override(world, character2DPrefab, Scale1D);
    // Rendering
    ecs_add(world, character2DPrefab, Brightness);
    ecs_override(world, character2DPrefab, Brightness);
    AddGPUMaterialComponents(world, character2DPrefab);
    // Textures
    AddSeedComponent(world, character2DPrefab, 444);
    AddTextureComponents(world, character2DPrefab, textureSize);
    AddTextureNoiseComponents(world, character2DPrefab);
    AddGPUTextureComponents(world, character2DPrefab);
    #ifdef Zoxel_Physics2D
    ecs_set(world, character2DPrefab, Acceleration2D, { { 0, 0 } });
    ecs_set(world, character2DPrefab, Rotation2D, { 0 });
    ecs_set(world, character2DPrefab, Torque2D, { 0 });
    ecs_override(world, character2DPrefab, Velocity2D);
    ecs_override(world, character2DPrefab, Acceleration2D);
    ecs_override(world, character2DPrefab, Torque2D);
    ecs_add(world, character2DPrefab, Frictioned);
    #endif
}