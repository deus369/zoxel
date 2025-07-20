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
#include "systems/skybox_set_time_system.c"

void spawn_shaders_weather(ecs_world_t *world) {
    shader_skybox = spawn_shader_skybox(world);
}

zox_begin_module(Weathers)
    add_hook_load_shader(&spawn_shaders_weather);
    zox_define_tag(Weather)
    zox_define_tag(Skybox)
    if (!headless) {
        zox_gpu_restore_system(SkyboxRestoreSystem,
            [in] rendering.MaterialGPULink,
            [in] colorz.ColorRGB,
            [in] colorz.SecondaryColorRGB,
            [none] Skybox)
        zox_system_1(SkyboxSetTimeSystem, EcsOnUpdate,
            [in] rendering.MaterialGPULink,
            [none] Skybox)
    }
    spawn_prefabs_weather(world);
zox_end_module(Weathers)

#endif
