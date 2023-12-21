ecs_entity_t particle2DPrefab;

void spawn_prefab_particle2D(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_particle2D")
    zox_add_tag(e, Particle2D)
#ifdef zoxel_transforms2D
    add_transform2Ds(world, e);
#endif
#ifdef zoxel_physics2D
    add_physics2D(world, e);
#endif
    zox_add(e, Brightness)
    zox_add(e, DestroyInTime)
    particle2DPrefab = e;
#ifdef zoxel_debug_prefabs
    zox_log("spawn_prefab particle2D_prefab [%lu]\n", e)
#endif
}
