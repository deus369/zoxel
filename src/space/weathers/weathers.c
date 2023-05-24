#ifndef zoxel_weather
#define zoxel_weather

zox_declare_tag(Weather)
#include "shaders/skybox.c"
#include "prefabs/skybox.c"

zox_begin_module(Weathers)
zox_define_tag(Weather)
spawn_prefab_skybox(world);
if (!headless) {
    initialize_shader_skybox();
}
#ifndef zox_disable_skybox
    spawn_skybox(world);
#endif
// systems
zoxel_end_module(Weathers)

#endif