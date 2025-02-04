void BonePaintSystem(ecs_iter_t *it) {
    zox_field_in(MeshDirty, meshDirtys, 1)
    zox_field_in(BoneIndexes, boneIndexess, 2)
    zox_field_out(MeshColorRGBs, meshColorRGBss, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MeshDirty, meshDirtys, meshDirty)
        if (meshDirty->value != mesh_state_generate) continue;
        zox_field_i(BoneIndexes, boneIndexess, boneIndexes)
        zox_field_o(MeshColorRGBs, meshColorRGBss, meshColorRGBs)
        for (int j = 0; j < meshColorRGBs->length; j++) {
            const unsigned char bone = boneIndexes->value[j];
            color_rgb bone_color = (color_rgb) { 255, 0, 0 };
            if (bone) bone_color.g = 255;
            bone_color.b += 16 * bone;
            bone_color.g -= 16 * bone;
            meshColorRGBs->value[j] = bone_color;
        }
    }
} zox_declare_system(BonePaintSystem)
