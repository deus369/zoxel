//! A basic 2D particle prefab.
ecs_entity_t particle2DPrefab;

//! Spawns a Particle2D Prefab.
void SpawnPrefabParticle2D(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "particle2D_prefab");
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab particle2D_prefab [%lu].\n", (long int) (e));
    #endif
    zoxel_add_tag(world, e, Particle2D);
    #ifdef zoxel_transforms2D
    add_transform2Ds(world, e);
    #endif
    #ifdef zoxel_physics2D
    add_physics2D(world, e);
    #endif
    zoxel_add(world, e, Brightness);
    zoxel_add(world, e, DestroyInTime);
    particle2DPrefab = e;
    ecs_defer_end(world);
}