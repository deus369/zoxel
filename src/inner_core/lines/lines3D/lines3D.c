#ifndef zoxel_lines3D
#define zoxel_lines3D

long int line3D_render_system_id;
zoxel_declare_tag(Line3D)
zoxel_component(LineData3D, float6)     //! The two points in a line3D.
#include "prefabs/line3D.c"
#include "systems/line3D_render_system.c"

void Lines3DImport(ecs_world_t *world) {
    zoxel_module(Lines3D)
    zoxel_define_tag(Line3D)
    zoxel_define_component(LineData3D)
    // systems
    if (!headless) {
        zoxel_system_main_thread(world, Line3DRenderSystem, 0, //EcsOnStore,
            [none] Line3D, [in] LineData3D, [in] LineThickness, [in] Color)
        line3D_render_system_id = ecs_id(Line3DRenderSystem);
    }
    if (!headless) {
        initialize_shader_line3D();
    }
    spawn_prefab_line3D(world);
    // test lines
    #ifdef zoxel_test_lines3D
        float voxel_scale = 4.0f; // overall_voxel_scale;
        int terrain_spawn_distance = 8;
        float thickness = voxel_scale; //  2.0f;
        float bottom = - (voxel_scale / 2.0f) + 1.0f; // voxel_scale; //  * (1.0f / 2.0f); // 2.0f; // 0.5f;
        float height = voxel_scale * 4.0f;
        float radius = thickness * 0.01f + (terrain_spawn_distance + 0.5f) * (voxel_scale / 2.0f); // 8.5f;
        float spacing = 1.0f; // / 2.0f;
        spawn_line3D(world, (float3) { -radius, bottom, -radius }, (float3) { -radius, bottom, radius }, thickness, 0);
        spawn_line3D(world, (float3) { -radius, bottom, radius }, (float3) { radius, bottom, radius }, thickness, 0);
        spawn_line3D(world, (float3) { radius, bottom, radius }, (float3) { radius, bottom, -radius }, thickness, 0);
        spawn_line3D(world, (float3) { radius, bottom, -radius }, (float3) { -radius, bottom, -radius }, thickness, 0);
        spawn_line3D(world, (float3) { -radius, height, -radius }, (float3) { -radius, height, radius }, thickness, 0);
        spawn_line3D(world, (float3) { -radius, height, radius }, (float3) { radius, height, radius }, thickness, 0);
        spawn_line3D(world, (float3) { radius, height, radius }, (float3) { radius, height, -radius }, thickness, 0);
        spawn_line3D(world, (float3) { radius, height, -radius }, (float3) { -radius, height, -radius }, thickness, 0);
        for (float i = -radius; i <= radius; i += spacing) {
            spawn_line3D(world, (float3) { i, bottom, radius }, (float3) { i, height, radius }, thickness, 0);
        }
        for (float i = -radius; i <= radius; i += spacing) {
            spawn_line3D(world, (float3) { i, bottom, -radius }, (float3) { i, height, -radius }, thickness, 0);
        }
        for (float i = -radius; i <= radius; i += spacing) {
            spawn_line3D(world, (float3) { radius, bottom, i }, (float3) { radius, height, i }, thickness, 0);
        }
        for (float i = -radius; i <= radius; i += spacing) {
            spawn_line3D(world, (float3) { -radius, bottom, i }, (float3) { -radius, height, i }, thickness, 0);
        }
        /*for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                spawn_line3D(world, 
                    (float3) { i, 0, j }, (float3) { i + 1, 0, j + 1 },
                    thickness, 32);
            }
        }*/
    #endif
}
#endif