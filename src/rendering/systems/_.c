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

// other
#include "lod_instance_system.c"

zox_increment_system_with_reset(MeshDirty, mesh_state_end);
zox_increment_system_with_reset(RenderLodDirty, zox_dirty_end);
zox_increment_system_with_reset(RenderDistanceDirty, zox_dirty_end);

void define_systems_rendering(ecs *world) {
    zoxd_system_increment(MeshDirty);
    zoxd_system_increment(RenderLodDirty);
    zoxd_system_increment(RenderDistanceDirty);
    // dispose
    zox_gpu_dispose_system(MeshGPUDisposeSystem, [in] MeshGPULink);
    zox_gpu_dispose_system(MeshUvsGPUDisposeSystem, [in] rendering.UvsGPULink);
    zox_gpu_dispose_system(MeshColorsGPUDisposeSystem, [in] rendering.ColorsGPULink);
    zox_gpu_dispose_system(TextureGPUDisposeSystem, [in] TextureGPULink);
    zox_gpu_dispose_system(ShaderDisposeSystem, [in] ShaderGPULink);
    zox_gpu_dispose_system(MaterialDisposeSystem, [in] MaterialGPULink);
    // restore
    zox_gpu_restore_system(MeshGPURestoreSystem, [out] MeshGPULink);
    zox_gpu_restore_system(UvsGPULinkRestoreSystem, [out] rendering.UvsGPULink);
    zox_gpu_restore_system(ColorsGPULinkRestoreSystem, [out] rendering.ColorsGPULink);
    zox_gpu_restore_system(TextureRestoreSystem, [out] TextureGPULink);
    zox_gpu_restore_system(TextureDirtyRestoreSystem, [out] rendering.TextureDirty);
    zox_gpu_restore_system(ShaderRestoreSystem, [in] ShaderSourceIndex, [out] ShaderGPULink);
    zox_gpu_restore_system(MaterialRestoreSystem, [in] ShaderLink, [out] MaterialGPULink);
    zox_gpu_restore_system(MeshDirtyRestoreSystem, [out] rendering.MeshDirty);
    // other
    zox_system(LodInstanceSystem, EcsPostUpdate,
        [in] rendering.RenderLodDirty,
        [in] rendering.RenderLod,
        [in] rendering.ModelLink,
        [out] rendering.InstanceLink)
}