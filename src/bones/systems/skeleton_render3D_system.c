void Skeleton3RenderSystem(iter *it) {
    if (!material_bone) {
        return;
    }
    byte has_set_material = 0;
    int rendered_count = 0;
    zox_sys_world()
    zox_geter_value(material_bone, MaterialGPULink, uint, material_link)
    zox_geter(material_bone, MaterialBone, material_attributes)
    zox_sys_begin()
    zox_sys_in(MeshIndicies)
    zox_sys_in(MeshGPULink)
    zox_sys_in(ColorsGPULink)
    zox_sys_in(BoneIndexGPULink)
    zox_sys_in(TransformMatrix)
    zox_sys_in(RenderDisabled)
    zox_sys_in(BoneLinks)
    for (int i = 0; i < it->count; i++) {
        // zox_sys_e()
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_i(MeshIndicies, meshIndicies)
        zox_sys_i(MeshGPULink, meshGPULink)
        zox_sys_i(ColorsGPULink, colorsGPULink)
        zox_sys_i(BoneIndexGPULink, boneIndexGPULink)
        zox_sys_i(BoneLinks, boneLinks)
        zox_sys_i(TransformMatrix, transformMatrix)
        if (renderDisabled->value || !meshIndicies->length || !meshGPULink->value.x || !meshGPULink->value.y || !colorsGPULink->value || !boneIndexGPULink->value || !boneLinks->length) {
            continue;
        }
        if (!has_set_material) {
            has_set_material = 1;
#ifdef zox_transparent_skeletons
            zox_gpu_blend_enable();
            glDisable(GL_CULL_FACE);
#endif
            zox_gpu_material(material_link);
            zox_gpu_float4x4(material_attributes->camera_matrix, render_camera_matrix);
            zox_gpu_float4(material_attributes->fog_data, get_fog_value());
            zox_gpu_float(material_attributes->brightness, 1);
        }
        // get local bone matrix, local to transform
        const float4x4 inverse = float4x4_inverse(transformMatrix->value);
        // zox_set(e, Scale1D, { 1 })
        float4x4 bones[boneLinks->length];
        float3 bone_positions[boneLinks->length];
        for (int j = 0; j < boneLinks->length; j++) {
            const entity bone = boneLinks->value[j];
            zox_geter_value(bone, TransformMatrix, float4x4, bone_matrix)
            bones[j] = float4x4_multiply(bone_matrix, inverse);
            bone_positions[j] = zox_get_value(bone, BonePosition)
        }
        zox_gpu_float4x4_array(material_attributes->bone_matrix, bones, boneLinks->length);
        zox_gpu_float3_array(material_attributes->bone_positions, bone_positions, boneLinks->length);
        zox_gpu_buffer_byte(material_attributes->bone_index, boneIndexGPULink->value);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
        opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);
        zox_gpu_float4x4(material_attributes->transform_matrix, transformMatrix->value);
        zox_gpu_render(meshIndicies->length);
#ifdef zox_catch_opengl_errors
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
} zox_declare_system(Skeleton3RenderSystem)