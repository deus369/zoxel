ecs_entity_t particle2DPrefab;

void spawn_prefab_particle2D(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_particle2D")
    zox_add_tag(e, Particle2D)
    #ifdef zoxel_transforms2D
        add_transform2Ds(world, e);
    #endif
    #ifdef zoxel_physics2D
        add_physics2D(world, e);
    #endif
    zox_add(e, Brightness)
    zox_add(e, DestroyInTime)
    ecs_defer_end(world);
    particle2DPrefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab particle2D_prefab [%lu].\n", (long int) (e));
    #endif
}