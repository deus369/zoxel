// todo: Shapes on bones used for setting verts, spheres of influence

void BoneIndexGenerateSystem(ecs_iter_t *it) {
    zox_field_in(MeshDirty, meshDirtys, 1)
    zox_field_in(MeshVertices, meshVerticess, 2)
    zox_field_out(BoneIndexes, boneIndexess, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MeshDirty, meshDirtys, meshDirty)
        if (meshDirty->value != mesh_state_generate) continue;
        zox_field_i(MeshVertices, meshVerticess, meshVertices)
        zox_field_o(BoneIndexes, boneIndexess, boneIndexes)
        resize_memory_component(BoneIndexes, boneIndexes, unsigned char, meshVertices->length)
        for (int j = 0; j < meshVertices->length; j++) {
            const float3 position = meshVertices->value[j];
            if (position.y >= 0.12f) boneIndexes->value[j] = 1;
            else boneIndexes->value[j] = 0;
            // if (position.y >= 0.12f) zox_log("setting bone 1")
        }
        zox_log(" + generated bone indexes!\n")
    }
} zox_declare_system(BoneIndexGenerateSystem)
