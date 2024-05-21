// skybox render system
void Render3DSystem(ecs_iter_t *it) {
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(Rotation3D, rotation3Ds, 2)
    zox_field_in(Scale1D, scale1Ds, 3)
    zox_field_in(Brightness, brightnesses, 4)
    zox_field_in(MeshGPULink, meshGPULinks, 5)
    zox_field_in(MaterialGPULink, materialGPULinks, 6)
    zox_field_in(MeshIndicies, meshIndiciess, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(MeshIndicies, meshIndiciess, meshIndicies)
        if (meshIndicies->length == 0) continue;
        zox_field_i_in(Position3D, position3Ds, position3D)
        zox_field_i_in(Rotation3D, rotation3Ds, rotation3D)
        zox_field_i_in(Scale1D, scale1Ds, scale1D)
        zox_field_i_in(Brightness, brightnesses, brightness)
        zox_field_i_in(MeshGPULink, meshGPULinks, meshGPULink)
        zox_field_i_in(MaterialGPULink, materialGPULinks, materialGPULink)
        Material3D attributes = spawn_material3D_properties(materialGPULink->value);
        opengl_set_material(materialGPULink->value);
        opengl_bind_mesh(meshGPULink->value);
        set_basic_vert_layout(&attributes);
        if (opengl_set_material3D_properties(&attributes, position3D->value, rotation3D->value, scale1D->value, brightness->value) == -1) return;
        // opengl_set_camera_view_matrix(materialGPULink->value, render_camera_matrix);
        glUniformMatrix4fv(glGetUniformLocation(materialGPULink->value, "camera_matrix"), 1, GL_FALSE, (float*) &render_camera_matrix);
        opengl_render(meshIndicies->length);
    }
    opengl_unset_mesh();
    opengl_disable_opengl_program();
} zox_declare_system(Render3DSystem)
