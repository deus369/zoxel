int zox_debug_print_systems(ecs_world_t *world, byte detailed) {
    int count =  zox_count_ids(EcsSystem);
    zox_log("🛠️ Systems: %d", count)
    return count;
}

int zox_debug_print_components(ecs_world_t *world, byte detailed) {
    zox_log("🧠 Components: %d", zox_statistics_components)
    return zox_statistics_components;
}