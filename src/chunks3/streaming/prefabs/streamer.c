entity spawn_prefab_streamer(ecs *world) {
    zox_prefab()
    zox_add_tag(e, Streamer)
    zox_prefab_set(e, StreamPoint, { int3_zero })
    zox_prefab_set(e, StreamDirty, { 1 })
    return e;
}

entity spawn_streamer(ecs *world,
    const entity prefab,
    const int3 point)
{
    zox_instance(prefab)
    zox_set(e, StreamPoint, { point })
    return e;
}