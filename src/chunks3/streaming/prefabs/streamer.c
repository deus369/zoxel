ecs_entity_t spawn_prefab_streamer(ecs_world_t *world) {
    zox_prefab()
    zox_add_tag(e, Streamer)
    zox_prefab_set(e, StreamPoint, { int3_zero })
    zox_prefab_set(e, StreamDirty, { 1 })
    return e;
}

ecs_entity_t spawn_streamer(ecs_world_t *world,
    const ecs_entity_t prefab,
    const int3 point)
{
    zox_instance(prefab)
    zox_set(e, StreamPoint, { point })
    return e;
}