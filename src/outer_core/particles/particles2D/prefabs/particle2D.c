//! A basic 2D particle prefab.
ecs_entity_t particle2DPrefab;

//! Spawns a Particle2D Prefab.
void SpawnPrefabParticle2D(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "particle2D_prefab");
    printf("spawn_prefab particle2D_prefab [%lu].\n", (long int) (e));
    zoxel_add_tag(world, e, Particle2D);
    #ifdef zoxel_transforms2D
    add_transform2Ds(world, e);
    #endif
    #ifdef zoxel_physics2D
    AddPhysics2DComponents(world, e);
    #endif
    zoxel_add_component(world, e, Brightness);
    zoxel_add_component(world, e, DestroyInTime);
    particle2DPrefab = e;
}