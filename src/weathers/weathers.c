#ifndef zox_mod_weathers
#define zox_mod_weathers

ecs_entity_t prefab_skybox;
ecs_entity_t shader_skybox; // shaders global
ecs_entity_t skybox; // remove this, link to realm/game
#include "data/settings.c"
zox_declare_tag(Weather)
zox_declare_tag(Skybox)
#include "shaders/skybox.c"
#include "prefabs/prefabs.c"
#include "systems/skybox_restore_system.c"

void spawn_shaders_weather(ecs_world_t *world) {
    shader_skybox = spawn_shader_skybox(world);
}

zox_begin_module(Weathers)
    add_load_shader_function(&spawn_shaders_weather);
    zox_define_tag(Weather)
    zox_define_tag(Skybox)
    if (!headless) {
        zox_gpu_restore_system(SkyboxRestoreSystem, [in] MaterialGPULink, [in] ColorRGB, [in] SecondaryColorRGB, [none] Skybox)
        zox_system_1(SkyboxSetTimeSystem, EcsOnUpdate, [in] MaterialGPULink, [none] Skybox)
    }
    spawn_prefabs_weather(world);
zoxel_end_module(Weathers)

#endif
