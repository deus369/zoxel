ecs_entity_t particle2DPrefab;

void spawn_prefab_particle2D(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("particle2D")
    zox_add_tag(e, Particle2D)
    zox_prefab_set(e, Position2D, { float2_zero })
    zox_prefab_set(e, Rotation2D, { 0 })
    zox_prefab_set(e, Scale1D, { 1 })
    add_physics2D(world, e, 0);
    zox_prefab_add(e, Brightness)
    zox_prefab_add(e, DestroyInTime)
    particle2DPrefab = e;
}
