void RenderLodColorSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(DebugCubeLines)
    zox_sys_in(RenderLod)
    zox_sys_in(RenderDisabled)
    zox_sys_out(Color)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(DebugCubeLines, debugCubeLines)
        zox_sys_i(RenderLod, renderLod)
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_o(Color, colorr)
        const byte mode = debugCubeLines->value;
        if (!mode) {
            continue;
        }
        color_rgb output = color_rgb_black;
        if (mode == zox_cubeline_debug_render_disabled) {
            if (renderDisabled->value) {
                output = (color_rgb) { 255, 0, 0 };
            } else {
                output = (color_rgb) { 0, 155, 0 };
            }
        } else if (mode == zox_cubeline_debug_verts) {
            if (zox_has(e, MeshIndicies)) {
                zox_geter(e, MeshIndicies, meshIndicies)
                if (meshIndicies->length == 0) {
                    output = (color_rgb) { 255, 0, 0 };
                } else {
                    output = (color_rgb) { 0, 255, 0 };
                }
            } else {
                output = (color_rgb) { 155, 155, 0 };
            }
        } else if (mode == zox_cubeline_debug_render_lod) {
            if (renderLod->value == render_lod_uninitialized) {
                output = (color_rgb) { 0, 0, 0 };
            } else if (renderLod->value == render_lod_invisible) {
                output = (color_rgb) { 255, 0, 0 };
            } else if (renderLod->value == 0) {
                output = (color_rgb) { 0, 255, 0 };
            } else if (renderLod->value == 1) {
                output = (color_rgb) { 0, 0, 255 };
            } else if (renderLod->value == 2) {
                output = (color_rgb) { 255, 255, 0 };
            } else if (renderLod->value == 3) {
                output = (color_rgb) { 255, 0, 255 };
            } else if (renderLod->value == 4) {
                output = (color_rgb) { 0, 255, 255 };
            } else if (renderLod->value == 5) {
                output = (color_rgb) { 122, 122, 122 };
            } else {
                output = (color_rgb) { 255, 255, 255 };
            }
        }
        colorr->value = color_rgb_to_color(output);
    }
} zox_declare_system(RenderLodColorSystem)
