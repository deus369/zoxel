// zox_flecs_3 | zox_flecs_4
#define zox_flecs_4
// #define zox_enable_log_new_system

byte running = 1;
#include "macros/_.c"
#include "data/_.c"
#include "components/_.c"
#include "util/_.c"
#include "systems/_.c"

ecs_world_t* open_ecs(int argc, char* argv[]) {
    ecs_world_t* new_world = ecs_init_w_args(argc, argv);
    return new_world;
}

ecs_world_t* initialize_ecs(int argc, char* argv[], byte cores) {
    use_cores = cores;
    ecs_world_t *new_world = open_ecs(argc, argv);
    local_world = new_world;
    return new_world;
}