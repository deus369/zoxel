void BonePaintSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(MeshDirty)
    zox_sys_in(BoneIndexes)
    zox_sys_out(MeshColorRGBs)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MeshDirty, meshDirty)
        zox_sys_i(BoneIndexes, boneIndexes)
        zox_sys_o(MeshColorRGBs, meshColorRGBs)
        if (meshDirty->value != mesh_state_generate) {
            continue;
        }
        for (int j = 0; j < meshColorRGBs->length; j++) {
            const byte bone = boneIndexes->value[j];
            color_rgb bone_color = (color_rgb) { 255, 0, 0 };
            if (bone) bone_color.g = 255;
            bone_color.b += 16 * bone;
            bone_color.g -= 16 * bone;
            meshColorRGBs->value[j] = bone_color;
        }
    }
} zoxd_system(BonePaintSystem)