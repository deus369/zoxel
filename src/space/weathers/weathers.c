#ifndef zoxel_weather
#define zoxel_weather

// const float3 menu_sky_color = (float3) { 0.8f, 0.4f, 0.1f };
const float3 menu_sky_color = (float3) { 0.3f, 0.1f, 0.1f };
const float3 menu_sky_bottom_color = (float3) { 0.2f, 0.06f, 0.06f };
const float3 game_sky_color = (float3) { 0.2f, 0.6f, 0.9f };
const float3 game_sky_bottom_color = (float3) { 0.7f, 0.55f, 0.58f };
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
add_load_shader_function((funfun) { &load_shader_skybox });
add_restore_shader_function((funfun) { &restore_shader_skybox });
// zox_define_components
zox_define_tag(Weather)
// zox_define_systems
zoxel_end_module(Weathers)

#endif
