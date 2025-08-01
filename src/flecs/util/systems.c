int zox_debug_print_systems(ecs_world_t *world) {
    int checker = zox_count_ids(EcsSystem);
    zox_log("+🛠️   Systems [%i] (query:%i)", zox_statistics_systems, checker)
    return zox_statistics_systems;
}

int zox_debug_print_components() {
    zox_log("+🛠️   Components [%i]", zox_statistics_components)
    return zox_statistics_components;
}

int zox_debug_print_modules() {
    zox_log("+🛠️   Modules [%i]", zox_statistics_modules)
    return zox_statistics_modules;
}