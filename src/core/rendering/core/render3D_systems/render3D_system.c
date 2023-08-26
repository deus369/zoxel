void Render3DSystem(ecs_iter_t *it) {
    const Position3D *positions = ecs_field(it, Position3D, 1);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 2);
    const Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    const Brightness *brightnesses = ecs_field(it, Brightness, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 6);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 7);
    for (int i = 0; i < it->count; i++) {
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        if (meshIndicies2->length == 0) continue;
        const Position3D *position = &positions[i];
        const Rotation3D *rotation = &rotations[i];
        const Scale1D *scale1D = &scale1Ds[i];
        const Brightness *brightness = &brightnesses[i];
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        opengl_set_material(materialGPULink->value);
        opengl_bind_mesh(meshGPULink->value);
        set_basic_vert_layout(materialGPULink->value);
        if (opengl_set_material3D_properties(materialGPULink->value, position->value, rotation->value, scale1D->value, brightness->value) == -1) return;
        // opengl_set_camera_view_matrix(materialGPULink->value, render_camera_matrix);
        glUniformMatrix4fv(glGetUniformLocation(materialGPULink->value, "camera_matrix"), 1, GL_FALSE, (float*) &render_camera_matrix);
        opengl_render(meshIndicies2->length);
    }
    opengl_unset_mesh();
    opengl_disable_opengl_program();
} zox_declare_system(Render3DSystem)