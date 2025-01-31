// skybox render system
int opengl_set_material3D_properties(const Material3D *attributes, const float3 position, const float4 rotation, const float scale, const float brightness) {
    glUniform3f(attributes->position, position.x, position.y, position.z);
    glUniform4f(attributes->rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    glUniform1f(attributes->scale, scale);
    glUniform1f(attributes->brightness, brightness);
    return 0;
}

void Render3DSystem(ecs_iter_t *it) {
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(Rotation3D, rotation3Ds, 2)
    zox_field_in(Scale1D, scale1Ds, 3)
    zox_field_in(Brightness, brightnesses, 4)
    zox_field_in(MeshGPULink, meshGPULinks, 5)
    zox_field_in(MaterialGPULink, materialGPULinks, 6)
    zox_field_in(MeshIndicies, meshIndiciess, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MeshIndicies, meshIndiciess, meshIndicies)
        if (meshIndicies->length == 0) continue;
        zox_field_i(Position3D, position3Ds, position3D)
        zox_field_i(Rotation3D, rotation3Ds, rotation3D)
        zox_field_i(Scale1D, scale1Ds, scale1D)
        zox_field_i(Brightness, brightnesses, brightness)
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        zox_field_i(MaterialGPULink, materialGPULinks, materialGPULink)
        Material3D attributes = spawn_material3D_properties(materialGPULink->value);
        opengl_set_material(materialGPULink->value);
        opengl_bind_mesh(meshGPULink->value);
        set_basic_vert_layout(&attributes);
        if (opengl_set_material3D_properties(&attributes, position3D->value, rotation3D->value, scale1D->value, brightness->value) == -1) break;
        // opengl_set_camera_view_matrix(materialGPULink->value, render_camera_matrix);
        glUniformMatrix4fv(glGetUniformLocation(materialGPULink->value, "camera_matrix"), 1, GL_FALSE, (float*) &render_camera_matrix);
        opengl_render(meshIndicies->length);
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zox_log(" ! Render3DSystem [%lu]: [%i]\n", it->entities[i], meshIndicies->length)
            break;
        }
#endif
    }
    opengl_unset_mesh();
    opengl_disable_opengl_program();
#ifdef zoxel_catch_opengl_errors
    if (check_opengl_error_unlogged() != 0) {
        zox_log(" ! Render3DSystem [%lu]\n", it->count)
    }
#endif
} zox_declare_system(Render3DSystem)
