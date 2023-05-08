#ifndef zoxel_weather
#define zoxel_weather

zoxel_declare_tag(Weather)
#include "shaders/skybox.c"
#include "prefabs/skybox.c"

zoxel_begin_module(Weathers)
zoxel_define_tag(Weather)
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