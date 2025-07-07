ecs_entity_t particle2DPrefab;

void spawn_prefab_particle2D(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_particle2D")
    zox_add_tag(e, Particle2D)
    add_transform2Ds(world, e);
    add_physics2D(world, e, 0);
    zox_prefab_add(e, Brightness)
    zox_prefab_add(e, DestroyInTime)
    particle2DPrefab = e;
}
