#ifndef zox_rendering_basics3D
#define zox_rendering_basics3D

zox_declare_tag(TexturedMesh3D)
zox_declare_tag(ColorRenderer)
#include "shaders/colored3D.c"
#include "shaders/instanced3D.c"
#include "shaders/textured3D.c"
#include "components/material3D.c"
#include "components/material3D_textured.c"
#include "components/material3D_colored.c"
#include "util/instanced3D_material.c"
#include "util/unique3D_material.c"
#include "util/textured3D_shader.c"
#include "util/shader3D_colored.c"
#include "systems/render3D_system.c"
#include "systems/render3D_instance_system.c"
#include "systems/render_characters3D_system.c"
#include "systems/mesh_update_system.c"
#include "systems/mesh_update_textured3D_system.c"
#include "systems/mesh_update_characters3D_system.c"
#include "systems/textured_render_system.c"

void spawn_shaders_basics3D(ecs_world_t *world) {
    if (load_shader3D_basic()) zoxel_log("    ! error loading [shader3D_basic]\n");
    spawn_material_colored3D(world);
    spawn_material_textured3D(world);
}

zox_begin_module(RenderingBasics3D)
zox_define_tag(TexturedMesh3D)
zox_define_tag(ColorRenderer)
add_load_shader_function(&spawn_shaders_basics3D);
zox_define_component(MaterialTextured3D)
zox_define_component(MaterialColored3D)
// skybox
zox_render3D_system(Render3DSystem, [in] Position3D, [in] Rotation3D, [in] Scale1D, [in] Brightness, [in] MeshGPULink, [in] MaterialGPULink, [in] MeshIndicies, [none] !UvsGPULink, [none] !MeshColorRGBs)
// idk
zox_system_1(InstanceRender3DSystem, 0, [in] Position3D, [in] Rotation3D, [in] Scale1D, [in] Brightness, [none] !MaterialGPULink, [none] !MeshGPULink)
// unique textured meshes
zox_render3D_plus_system(TexturedRenderSystem, [in] TransformMatrix, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshIndicies, [in] RenderDisabled, [in] MaterialGPULink, [in] TextureGPULink, [in] MaterialTextured3D, [none] TexturedMesh3D)
// characters
zox_render3D_plus_system(RenderCharacters3DSystem, [in] MeshIndicies, [in] MeshGPULink, [in] ColorsGPULink, [in] TransformMatrix, [in] RenderDisabled, [none] MeshColorRGBs, [none] !UvsGPULink, [none] ColorRenderer)
// upload gpu
zox_system_1(MeshUpdateSystem, zox_pip_mainthread, [out] MeshDirty, [in] MeshIndicies, [in] MeshVertices, [in] MeshGPULink, [in] MaterialGPULink, [none] !MeshUVs, [none] !MeshColorRGBs)
zox_system_1(Mesh3DTexturedUploadSystem, zox_pip_mainthread, [in] MeshIndicies, [in] MeshVertices, [in] MeshUVs, [in] MeshColorRGBs, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [out] MeshDirty)
zox_system_1(MeshUpdateCharacters3DSystem, zox_pip_mainthread, [in] MeshIndicies, [in] MeshVertices, [in] MeshColorRGBs, [out] MeshDirty, [out] MeshGPULink, [out] ColorsGPULink, [none] MeshColorRGBs, [none] !MeshUVs)
zoxel_end_module(RenderingBasics3D)

#endif
