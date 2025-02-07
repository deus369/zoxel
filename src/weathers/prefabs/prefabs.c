#include "skybox.c"

void spawn_prefabs_weather(ecs_world_t *world) {
    prefab_skybox = spawn_prefab_skybox(world);
}

void spawn_weather(ecs_world_t *world) {
    #ifndef zox_disable_skybox
    spawn_skybox(world, shader_skybox);
    #endif
}