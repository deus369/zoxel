#ifndef zox_rendering_cameras
#define zox_rendering_cameras

#include "data/frame_buffer.c"
#include "data/render_buffer.c"
#include "util/render_camera.c"
#include "util/camera_render_update.c"
#include "systems/restore_render_buffer_system.c"
#include "systems/render_texture_restore_system.c"
#include "systems/camera_render3D_system.c"
#include "systems/camera_render_ui_system.c"

zox_begin_module(RenderingCameras)
    zox_define_component_w_dest(RenderBufferLink)
    zox_define_component_w_dest(FrameBufferLink)
    zox_gpu_restore_system(RenderBufferRestoreSystem, [in] ScreenDimensions, [out] FrameBufferLink, [out] RenderBufferLink)
    zox_gpu_restore_system(RenderTextureRestoreSystem, [in] TextureGPULink, [in] PixelSize, [in] CameraLink, [none] cameras.RenderTexture)
    // rendering
    zox_system_1(CameraRender3DSystem, zox_pipelines_rendering, [in] cameras.ViewMatrix, [in] cameras.FieldOfView, [in] cameras.ScreenPosition, [in] ScreenDimensions, [none] !cameras.CameraUI)
    zox_system_1(CameraRenderUISystem, zox_pipelines_rendering, [in] cameras.ViewMatrix, [in] cameras.FieldOfView, [in] cameras.ScreenPosition, [in] ScreenDimensions, [none] cameras.CameraUI)
zox_end_module(RenderingCameras)

#endif