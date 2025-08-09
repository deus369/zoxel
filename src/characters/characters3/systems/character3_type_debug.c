void Character3TypeDebugSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(DebugCubeLines)
    zox_sys_in(Character3Type)
    zox_sys_out(Color)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(DebugCubeLines, debugCubeLines)
        zox_sys_i(Character3Type, character3Type)
        zox_sys_o(Color, colorr)
        const byte mode = debugCubeLines->value;
        if (!mode) {
            continue;
        }
        color_rgb output = color_rgb_black;
        if (mode == zox_cubeline_debug_character_types) {
            if (character3Type->value == zox_character_type_instanced) {
                output = (color_rgb) { 0, 200, 0 };
            } else if (character3Type->value == zox_character_type_unique) {
                output = (color_rgb) { 0, 255, 255 };
            } else if (character3Type->value == zox_character_type_skeleton) {
                output = (color_rgb) { 255, 255, 0 };
            }
        } else {
            continue;
        }
        colorr->value = color_rgb_to_color(output);
    }
} zoxd_system(Character3TypeDebugSystem)
