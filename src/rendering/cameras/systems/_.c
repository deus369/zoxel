#include "restore_render_buffer_system.c"
#include "render_texture_restore_system.c"
#include "camera_renderer.c"
#include "camera_render3D_system.c"
#include "camera_render_ui_system.c"

void define_systems_rendering_cameras(ecs *world) {
    // rendering
    zox_system_1(CameraRender3DSystem, zox_pipelines_rendering,
        [in] cameras.ViewMatrix,
        [in] cameras.FieldOfView,
        [in] cameras.ScreenPosition,
        [in] generic.ScreenDimensions,
        [in] colorz.FogColor,
        [none] !cameras.CameraUI)
    zox_system_1(CameraRenderUISystem, zox_pipelines_rendering,
        [in] cameras.ViewMatrix,
        [in] cameras.FieldOfView,
        [in] cameras.ScreenPosition,
        [in] generic.ScreenDimensions,
        [in] colorz.FogColor,
        [none] cameras.CameraUI)
    // restore
    zox_gpu_restore_system(RenderBufferRestoreSystem,
        [in] generic.ScreenDimensions,
        [out] FrameBufferLink,
        [out] RenderBufferLink)
    zox_gpu_restore_system(RenderTextureRestoreSystem,
        [in] rendering.TextureGPULink,
        [in] rendering.TextureSize,
        [in] cameras.CameraLink,
        [none] cameras.RenderTexture)
}