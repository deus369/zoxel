#ifndef zoxel_weather
#define zoxel_weather

zox_declare_tag(Weather)
#include "shaders/skybox.c"
#include "prefabs/skybox.c"

void spawn_weather(ecs_world_t *world) {
    #ifndef zox_disable_skybox
        spawn_skybox(world);
    #endif
}

void spawn_prefabs_weather(ecs_world_t *world) {
    spawn_prefab_skybox(world);
}

zox_begin_module(Weathers)
zox_define_tag(Weather)
// systems
zoxel_end_module(Weathers)

#endif