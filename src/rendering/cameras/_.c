#ifndef zox_rendering_cameras
#define zox_rendering_cameras

#include "data/frame_buffer.c"
#include "data/render_buffer.c"
#include "util/render_camera.c"
#include "util/camera_render_update.c"
#include "systems/_.c"

zox_begin_module(RenderingCameras)
    zox_define_component_w_dest(RenderBufferLink)
    zox_define_component_w_dest(FrameBufferLink)
    define_systems_rendering_cameras(world);
zox_end_module(RenderingCameras)

#endif