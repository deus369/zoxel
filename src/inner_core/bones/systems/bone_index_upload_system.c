void BoneIndexUploadSystem(ecs_iter_t *it) {
    zox_field_in(MeshDirty, meshDirtys, 1)
    zox_field_in(BoneIndexes, boneIndexess, 2)
    zox_field_out(BoneIndexGPULink, boneIndexGPULinks, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MeshDirty, meshDirtys, meshDirty)
        if (meshDirty->value != mesh_state_upload) continue;
        zox_field_i(BoneIndexes, boneIndexess, boneIndexes)
        zox_field_o(BoneIndexGPULink, boneIndexGPULinks, boneIndexGPULink)
        if (boneIndexes->length == 0) {
            zox_log(" ! boneIndexes 0\n")
            if (boneIndexGPULink->value != 0) {
                clear_regular_buffer(&boneIndexGPULink->value);
            }
            continue;
        }
        if (boneIndexGPULink->value == 0) {
            boneIndexGPULink->value = spawn_gpu_generic_buffer();
        }
        glBindBuffer(GL_ARRAY_BUFFER, boneIndexGPULink->value);
        glBufferData(GL_ARRAY_BUFFER, boneIndexess->length * sizeof(unsigned char), boneIndexess->value, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        zox_log(" + updated bone indexes to gpu\n")
#ifdef zoxel_catch_opengl_errors
        check_opengl_error("BoneIndexUploadSystem");
#endif
    }
} zox_declare_system(BoneIndexUploadSystem)
