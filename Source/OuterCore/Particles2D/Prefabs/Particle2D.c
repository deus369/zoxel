//! A basic 2D particle prefab.
ecs_entity_t particle2DPrefab;

//! Spawns a Particle2D Prefab.
void SpawnPrefabParticle2D(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "particle2D_prefab");
    zoxel_add_tag(world, e, Particle2D);
    #ifdef Zoxel_Transforms2D
    AddTransforms2DComponents(world, e);
    #endif
    #ifdef Zoxel_Physics2D
    AddPhysics2DComponents(world, e);
    #endif
    zoxel_add_component(world, e, Brightness);
    zoxel_add_component(world, e, DestroyInTime);
    particle2DPrefab = e;
}