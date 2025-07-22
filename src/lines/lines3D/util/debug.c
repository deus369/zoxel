// debug mode
#define zox_cubeline_debug_none 0
#define zox_cubeline_debug_render_lod 1
#define zox_cubeline_debug_render_disabled 2
#define zox_cubeline_debug_verts 3
#define zox_cubeline_debug_end 4
#define zox_cubeline_debug_transforms 5
#define zox_cubeline_debug_instanced 6

static inline void cycle_cubeline_debug(byte* mode) {
    (*mode)++;
    if (*mode == zox_cubeline_debug_end) {
        (*mode) = 0;
    }
    if ((*mode) == zox_cubeline_debug_render_lod) {
        zox_log("-> debugging render_lods")
    } else if (*mode == zox_cubeline_debug_render_disabled) {
        zox_log("-> debugging render_disabled")
    } else if (*mode == zox_cubeline_debug_verts) {
        zox_log("-> debugging verts")
    }  else if (*mode == zox_cubeline_debug_none) {
        zox_log("-> debugging cubes disabled")
    } else {
        zox_log("-> cubeline_debug_mode is set to [%i]", *mode)
    }
}
