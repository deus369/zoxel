// uploads bon indexes to shader
void BoneIndexUploadSystem(iter *it) {
    if (disable_bone_rendering) {
        return;
    }
    zox_sys_begin()
    zox_sys_in(MeshDirty)
    zox_sys_in(BoneIndexes)
    zox_sys_out(BoneIndexGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MeshDirty, meshDirty)
        zox_sys_i(BoneIndexes, boneIndexes)
        zox_sys_o(BoneIndexGPULink, boneIndexGPULink)
        if (meshDirty->value != mesh_state_upload) {
            continue;
        }
        if (boneIndexes->length == 0) {
            // zox_log(" ! boneIndexes 0\n")
            if (boneIndexGPULink->value != 0) {
                clear_regular_buffer(&boneIndexGPULink->value);
            }
            continue;
        }
        if (boneIndexGPULink->value == 0) {
            boneIndexGPULink->value = spawn_gpu_generic_buffer();
        }
        glBindBuffer(GL_ARRAY_BUFFER, boneIndexGPULink->value);
        glBufferData(GL_ARRAY_BUFFER, boneIndexes->length * sizeof(byte), boneIndexes->value, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
} zox_declare_system(BoneIndexUploadSystem)
