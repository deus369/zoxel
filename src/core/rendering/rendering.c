#ifndef zox_rendering
#define zox_rendering

#include "data/renderer_types.c"
#include "data/mesh_alignment_types.c"
#include "data/settings.c"
// zoxel_declare_components
zox_declare_tag(Mesh)
zox_component_byte(MeshDirty)
zox_component_entity(MeshLink)
zox_component_byte(TextureDirty)
zox_component_byte(MeshAlignment)
zox_component_byte(RenderLod)       // The resolution of each chunk, distance to nearest camera
zox_component_byte(RenderDisabled)
zox_component_float(Brightness)
zox_component_float(Alpha)
#include "opengl/opengl.c"
#include "vulkan/vulkan.c"
#include "core/core.c"
#include "basics2D/basics2D.c"
#include "basics3D/basics3D.c"

unsigned char initialize_rendering(ecs_world_t *world) {
    if (headless) return EXIT_SUCCESS;
    else if (is_using_vulkan) return initialize_vulkan(world); // SDL_WINDOW_VULKAN
    else return initialize_opengl(world);
}

void dispose_rendering(ecs_world_t *world, void *ctx) {
    if (headless) return;
    // opengl_dispose_shaders();
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
zox_define_component_byte(RenderDisabled)
zox_define_component_float(Brightness)
zox_define_component_float(Alpha)
if (headless) return;
check_vulkan_suppport();
if (is_using_vulkan) { zox_import_module(Vulkan) }
else { zox_import_module(OpenGL) }
// if (initialize_rendering(world) == EXIT_FAILURE) zox_log(" ! failed to initialize rendering\n")
zox_import_module(RenderingCore)
zox_import_module(RenderingBasics2D)
zox_import_module(RenderingBasics3D)
zoxel_end_module(Rendering)

#endif
