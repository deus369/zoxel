void SkeletonRender3DSystem(ecs_iter_t *it) {
    if (!material_colored3D) return;
    zox_iter_world()
    unsigned char has_set_material = 0;
    int rendered_count = 0;
    const GLuint material_link = zox_get_value(material_colored3D, MaterialGPULink)
    const MaterialColored3D *material_attributes = zox_get(material_colored3D, MaterialColored3D)
    zox_field_in(MeshIndicies, meshIndiciess, 1)
    zox_field_in(MeshGPULink, meshGPULinks, 2)
    zox_field_in(ColorsGPULink, colorsGPULinks, 3)
    zox_field_in(TransformMatrix, transformMatrixs, 4)
    zox_field_in(RenderDisabled, renderDisableds, 5)
    zox_field_in(BoneLinks, boneLinkss, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value) continue;
        zox_field_i(MeshIndicies, meshIndiciess, meshIndicies)
        if (meshIndicies->length == 0) continue;
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        zox_field_i(ColorsGPULink, colorsGPULinks, colorsGPULink)
        zox_field_i(TransformMatrix, transformMatrixs, transformMatrix)
        zox_field_i(BoneLinks, boneLinkss, boneLinks)
        if (!has_set_material) {
            has_set_material = 1;
#ifdef zox_transparent_voxes
            opengl_enable_blend();
            glDisable(GL_CULL_FACE);
#endif
            opengl_set_material(material_link);
            opengl_set_matrix(material_attributes->camera_matrix, render_camera_matrix);
            opengl_set_float4(material_attributes->fog_data, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
            opengl_set_float(material_attributes->brightness, 1);
        }
        // get local bone matrix, local to transform
        const float4x4 inverse = float4x4_inverse(transformMatrix->value);
        zox_set(it->entities[i], Scale1D, { 1 })
        float4x4 bones[boneLinks->length];
        for (int j = 0; j < boneLinks->length; j++) {
            float4x4 bone_matrix = zox_get_value(boneLinks->value[j], TransformMatrix)
            bone_matrix = float4x4_multiply(bone_matrix, inverse);
            //bone_matrix = float4x4_multiply(transformMatrix->value, bone_matrix);
            bones[j] = bone_matrix;
        }
        opengl_set_matrix_array(material_attributes->bone_matrix, bones, boneLinks->length);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
        opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);
        opengl_set_matrix(material_attributes->transform_matrix, transformMatrix->value);
        opengl_render(meshIndicies->length);
        #ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zoxel_log(" > could not render character [%i]: indicies [%i] - [%ix%i:%i]\n", rendered_count, meshIndicies->length, meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value);
            break;
        }
        #endif
        rendered_count++;
        zox_statistics_characters_rendered++;
    }
    if (has_set_material) {
        opengl_disable_buffer(material_attributes->vertex_color);
        opengl_disable_buffer(material_attributes->vertex_position);
        opengl_unset_mesh();
        opengl_disable_opengl_program();
#ifdef zox_transparent_voxes
        opengl_disable_blend();
        glEnable(GL_CULL_FACE);
#endif
    }
} zox_declare_system(SkeletonRender3DSystem)
