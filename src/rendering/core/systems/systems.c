#include "dispose_mesh_system.c"
#include "dispose_colors_system.c"
#include "dispose_uvs_system.c"
#include "dispose_texture_system.c"
#include "dispose_shader_system.c"
#include "dispose_material_system.c"

#include "restore_mesh_system.c"
#include "restore_colors_system.c"
#include "restore_uvs_system.c"
#include "restore_texture_system.c"
#include "restore_shader_system.c"
#include "restore_materials_system.c"
#include "restore_meshdirty_system.c"

void define_systems_rendering(ecs_world_t *world) {
    // dispose
    zox_gpu_dispose_system(MeshGPUDisposeSystem, [in] MeshGPULink)
    zox_gpu_dispose_system(MeshUvsGPUDisposeSystem, [in] UvsGPULink)
    zox_gpu_dispose_system(MeshColorsGPUDisposeSystem, [in] ColorsGPULink)
    zox_gpu_dispose_system(TextureGPUDisposeSystem, [in] TextureGPULink)
    zox_gpu_dispose_system(ShaderDisposeSystem, [in] ShaderGPULink)
    zox_gpu_dispose_system(MaterialDisposeSystem, [in] MaterialGPULink)
    // restore
    zox_gpu_restore_system(MeshGPURestoreSystem, [out] MeshGPULink)
    zox_gpu_restore_system(UvsGPULinkRestoreSystem, [out] UvsGPULink)
    zox_gpu_restore_system(ColorsGPULinkRestoreSystem, [out] ColorsGPULink)
    zox_gpu_restore_system(TextureRestoreSystem, [out] TextureGPULink)
    zox_gpu_restore_system(TextureDirtyRestoreSystem, [out] TextureDirty)
    zox_gpu_restore_system(ShaderRestoreSystem, [in] ShaderSourceIndex, [out] ShaderGPULink)
    zox_gpu_restore_system(MaterialRestoreSystem, [in] ShaderLink, [out] MaterialGPULink)
    zox_gpu_restore_system(MeshDirtyRestoreSystem, [out] MeshDirty)
}