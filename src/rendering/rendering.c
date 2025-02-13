#ifndef zox_mod_rendering
#define zox_mod_rendering

// #define zox_disable_rendering3D
#define render_lod_invisible 254
#define render_lod_uninitialized 255
byte rendering_initialized = 0;
#include "data/renderer_types.c"
#include "data/mesh_alignment_types.c"
#include "data/settings.c"
#include "data/mesh_states.c"
zox_declare_tag(Mesh)
zox_component_byte(MeshDirty)
zox_component_entity(MeshLink)
zox_component_byte(TextureDirty)
zox_component_byte(MeshAlignment)
zox_component_byte(RenderLod)       // The resolution of each chunk, distance to nearest camera
zox_component_byte(RenderDistance)
zox_component_byte(RenderDisabled)
zox_component_float(Brightness)
zox_component_float(Alpha)
#include "opengl/opengl.c"
#include "vulkan/vulkan.c"
#include "core/core.c"
#include "basics2D/basics2D.c"
#ifndef zox_disable_rendering3D
    #include "basics3D/basics3D.c"
#endif
zox_increment_system_with_reset(MeshDirty, mesh_state_end)

unsigned char initialize_rendering(ecs_world_t *world) {
    rendering_initialized = 1;
    if (headless) return EXIT_SUCCESS;
    else if (is_using_vulkan) return initialize_vulkan(world); // SDL_WINDOW_VULKAN
    else return initialize_opengl(world);
}

void dispose_rendering(ecs_world_t *world, void *ctx) {
    if (headless) return;
    dispose_vulkan(world);
}

zox_begin_module(Rendering)
    zox_module_dispose(dispose_rendering)
    zox_define_tag(Mesh)
    zox_define_component_byte(MeshDirty)
    zox_define_component_byte(MeshAlignment)
    zox_define_component_entity(MeshLink)
    zox_define_component_byte(TextureDirty)
    zox_define_component_byte(RenderLod)
    zox_define_component_byte(RenderDistance)
    zox_define_component_byte(RenderDisabled)
    zox_define_component_float(Brightness)
    zox_define_component_float(Alpha)
    zox_define_increment_system(MeshDirty, EcsOnLoad)
    if (headless) {
        return;
    } else if (is_using_vulkan && check_vulkan_suppport()) {
        zox_import_module(Vulkan)
    } else {
        zox_import_module(OpenGL)
    }
    zox_import_module(RenderingCore)
    zox_import_module(RenderingBasics2D)
    #ifdef zox_mod_rendering_basics3D
        zox_import_module(RenderingBasics3D)
    #endif
zox_end_module(Rendering)

#endif
