//! Basic noise texture.
ecs_entity_t character2DPrefab;
extern MaterialTextured2D materialTextured2D;
extern void AddSeedComponent(ecs_world_t *world, ecs_entity_t prefab, int seed);
extern void AddTextureComponents(ecs_world_t *world, ecs_entity_t prefab, int2 textureSize);
extern void AddTextureNoiseComponents(ecs_world_t *world, ecs_entity_t prefab);

void InitializeCharacter2DPrefab(ecs_world_t *world)
{
    const int2 textureSize = { 16, 16 };
    character2DPrefab = ecs_new_prefab(world, "Character2D");
    ecs_set(world, character2DPrefab, Position2D, { { 0, 0 } });
    ecs_set(world, character2DPrefab, Velocity2D, { { 0, 0 } });
    ecs_set(world, character2DPrefab, Scale2D, { 1 });
    ecs_override(world, character2DPrefab, Position2D);
    ecs_override(world, character2DPrefab, Rotation2D);
    ecs_override(world, character2DPrefab, Scale2D);
    // Textures
    AddSeedComponent(world, character2DPrefab, 444);
    AddTextureComponents(world, character2DPrefab, textureSize);
    AddTextureNoiseComponents(world, character2DPrefab);
    // Rendering
    ecs_add(world, character2DPrefab, Brightness);
    ecs_override(world, character2DPrefab, Brightness);
    ecs_add(world, character2DPrefab, Material);
    ecs_override(world, character2DPrefab, Material);
    #ifndef DISABLE_TEXTURES
    ecs_set(world, character2DPrefab, Material, { materialTextured2D.material });
    #else
    ecs_set(world, character2DPrefab, Material, { material });
    #endif
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