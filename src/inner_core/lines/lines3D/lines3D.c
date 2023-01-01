#ifndef zoxel_lines3D
#define zoxel_lines3D

// Tags
zoxel_declare_tag(Line3D)
// components
//! The two points in a line3D.
zoxel_component(LineData3D, float6)
// prefabs
#include "prefabs/line3D.c"
// systems
#include "systems/line3D_render_system.c"

//! Lines2D Module.
void Lines3DImport(ecs_world_t *world)
{
    zoxel_define_module(Lines3D)
    zoxel_define_tag(Line3D)
    zoxel_define_component(LineData3D)
    // systems
    if (!headless)
    {
        initialize_shader_line3D();
        zoxel_system_main_thread(world, Line3DRenderSystem, EcsOnStore, // 0
            [none] Line3D, [in] LineData3D, [in] LineThickness, [in] Color);
    }
    // prefabs
    spawn_prefab_line3D(world);
    // test lines
    #ifdef zoxel_test_lines3D
        float thickness = 0.6f;
        float depth = -16;
        /*for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                spawn_line3D(world, 
                    (float3) { i, 0, j }, (float3) { i + 1, 0, j + 1 },
                    thickness, 32);
            }
        }*/
        for (int i = -16; i <= 16; i++)
        {
            spawn_line3D(world, (float3) { i, 0, depth }, (float3) { i, 128, depth }, thickness, 32);
        }
    #endif
}
#endif