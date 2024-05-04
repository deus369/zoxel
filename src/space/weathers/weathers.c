#ifndef zoxel_weather
#define zoxel_weather

float3 menu_sky_color = (float3) { 0.3f, 0.1f, 0.1f };
float3 menu_sky_bottom_color = (float3) { 0.2f, 0.06f, 0.06f };
float3 game_sky_color = (float3) { 0.2f, 0.6f, 0.9f };
float3 game_sky_bottom_color = (float3) { 0.7f, 0.55f, 0.58f };
zox_declare_tag(Weather)
zox_declare_tag(Skybox)
#include "shaders/skybox.c"
#include "prefabs/skybox.c"
#include "systems/skybox_restore_system.c"

void spawn_weather(ecs_world_t *world) {
#ifndef zox_disable_skybox
    spawn_skybox(world);
#endif
}

void spawn_prefabs_weather(ecs_world_t *world) {
    spawn_prefab_skybox(world);
}

zox_begin_module(Weathers)
add_load_shader_function((funfun) { &spawn_shader_skybox });
// add_restore_shader_function((funfun) { &restore_shader_skybox });
// zox_define_components
zox_define_tag(Weather)
zox_define_tag(Skybox)
// zox_define_systems
zox_gpu_restore_system(SkyboxRestoreSystem, [in] MaterialGPULink, [in] ColorRGB, [in] SecondaryColorRGB, [none] Skybox)
zoxel_end_module(Weathers)

#endif
