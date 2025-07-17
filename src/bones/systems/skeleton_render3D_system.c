void opengl_enable_bone_buffer(uint shader_index, uint buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glEnableVertexAttribArray(shader_index);
    glVertexAttribPointer(shader_index, 1, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SkeletonRender3DSystem(ecs_iter_t *it) {
#ifdef zox_disable_skeleton_rendering
    return;
#endif
    if (!material_bone) return;
    zox_field_world()
    byte has_set_material = 0;
    int rendered_count = 0;
    const uint material_link = zox_get_value(material_bone, MaterialGPULink)
    const MaterialBone *material_attributes = zox_get(material_bone, MaterialBone)
    zox_field_in(MeshIndicies, meshIndiciess, 1)
    zox_field_in(MeshGPULink, meshGPULinks, 2)
    zox_field_in(ColorsGPULink, colorsGPULinks, 3)
    zox_field_in(BoneIndexGPULink, boneIndexGPULinks, 4)
    zox_field_in(TransformMatrix, transformMatrixs, 5)
    zox_field_in(RenderDisabled, renderDisableds, 6)
    zox_field_in(BoneLinks, boneLinkss, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value) continue;
        zox_field_i(MeshIndicies, meshIndiciess, meshIndicies)
        if (meshIndicies->length == 0) continue;
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) continue;
        zox_field_i(ColorsGPULink, colorsGPULinks, colorsGPULink)
        if (colorsGPULink->value == 0) continue;
        zox_field_i(BoneIndexGPULink, boneIndexGPULinks, boneIndexGPULink)
        if (boneIndexGPULink->value == 0) continue;
        zox_field_i(BoneLinks, boneLinkss, boneLinks)
        if (boneLinks->length == 0) continue;
        zox_field_i(TransformMatrix, transformMatrixs, transformMatrix)
        if (!has_set_material) {
            has_set_material = 1;
#ifdef zox_transparent_skeletons
            zox_gpu_blend_enable();
            glDisable(GL_CULL_FACE);
#endif
            zox_enable_material(material_link);
            opengl_set_matrix(material_attributes->camera_matrix, render_camera_matrix);
            zox_gpu_float4(material_attributes->fog_data, get_fog_value());
            zox_gpu_float(material_attributes->brightness, 1);
        }
        // get local bone matrix, local to transform
        const float4x4 inverse = float4x4_inverse(transformMatrix->value);
        zox_set(it->entities[i], Scale1D, { 1 })
        float4x4 bones[boneLinks->length];
        float3 bone_positions[boneLinks->length];
        for (int j = 0; j < boneLinks->length; j++) {
            float4x4 bone_matrix = zox_get_value(boneLinks->value[j], TransformMatrix)
            bone_matrix = float4x4_multiply(bone_matrix, inverse);
            bones[j] = bone_matrix;
            bone_positions[j] = zox_get_value(boneLinks->value[j], BonePosition)
        }
        opengl_set_matrix_array(material_attributes->bone_matrix, bones, boneLinks->length);
        zox_gpu_float3_array(material_attributes->bone_positions, bone_positions, boneLinks->length);
        opengl_enable_bone_buffer(material_attributes->bone_index, boneIndexGPULink->value);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
        opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);
        opengl_set_matrix(material_attributes->transform_matrix, transformMatrix->value);
        zox_gpu_render(meshIndicies->length);
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zox_log(" > could not render character [%i]: indicies [%i] - [%ix%i:%i]\n", rendered_count, meshIndicies->length, meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value)
            break;
        }
#endif
        rendered_count++;
        zox_statistics_characters_rendered++;
    }
    if (has_set_material) {
        zox_gpu_disable_buffer(material_attributes->vertex_color);
        zox_gpu_disable_buffer(material_attributes->vertex_position);
        opengl_unset_mesh();
        zox_disable_material();
#ifdef zox_transparent_skeletons
        zox_gpu_blend_disable();
        glEnable(GL_CULL_FACE);
#endif
    }
} zox_declare_system(SkeletonRender3DSystem)
