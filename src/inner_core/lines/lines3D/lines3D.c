#ifndef zoxel_lines3D
#define zoxel_lines3D

long int line3D_render_system_id;
zoxel_declare_tag(Line3D)
zoxel_component(LineData3D, float6)     //! The two points in a line3D.
#include "prefabs/line3D.c"
#include "systems/line3D_render_system.c"
#include "util/test_lines3D.c"

void Lines3DImport(ecs_world_t *world) {
    zoxel_module(Lines3D)
    zoxel_define_tag(Line3D)
    zoxel_define_component(LineData3D)
    // systems
    if (!headless) {
        if (main_gl_context) {
            initialize_shader_line3D();
        }
        zoxel_system_main_thread(world, Line3DRenderSystem, 0, //EcsOnStore,
            [none] Line3D, [in] LineData3D, [in] LineThickness, [in] Color)
        line3D_render_system_id = ecs_id(Line3DRenderSystem);
    }
    spawn_prefab_line3D(world);
    #ifdef zoxel_test_lines3D
        spawn_test_lines3D();
    #endif
}
#endif