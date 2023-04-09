extern float4x4 main_camera_matrix;

void Render3DColoredSystem(ecs_iter_t *it) {
    const Position3D *positions = ecs_field(it, Position3D, 1);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 2);
    const Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    const Brightness *brightnesses = ecs_field(it, Brightness, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 6);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 7);
    unsigned char has_set_single_material = 0;
    MaterialColored3D materialColored3D;
    for (int i = 0; i < it->count; i++) {
        const Position3D *position = &positions[i];
        const Rotation3D *rotation = &rotations[i];
        const Scale1D *scale1D = &scale1Ds[i];
        const Brightness *brightness = &brightnesses[i];
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        if (!has_set_single_material) {
            has_set_single_material = 1;
            opengl_set_material(materialGPULink->value);
            materialColored3D = spawn_material3D_colored_properties(materialGPULink->value);
            // opengl_set_camera_view_matrix(materialGPULink->value, main_camera_matrix);
            glUniformMatrix4fv(materialColored3D.view_matrix, 1, GL_FALSE, (float*) &main_camera_matrix);
            glUniform1f(materialColored3D.scale, scale1D->value);
            glUniform1f(materialColored3D.brightness, brightness->value);
            // set_color_vertex_layout(materialGPULink->value);
            // zoxel_log(" - Rendering 3D Colored Mesh [%lu]\n", (long int) it->entities[i]);
        }
        opengl_set_mesh(meshGPULink->value);
        set_color_vertex_layout(&materialColored3D);
        opengl_set_material3D_colors_properties(&materialColored3D, position->value, rotation->value);
        opengl_draw_triangles(meshIndicies2->length);
    }
    opengl_unset_mesh();
    opengl_disable_opengl_program();
}
zoxel_declare_system(Render3DColoredSystem)

/*if (!has_mesh_colors) {
    if (opengl_set_material3D_properties(materialGPULink->value,
        position->value, rotation->value, scale1D->value, brightness->value) == -1) {
        return;
    }
} else {
    if (opengl_set_material3D_colors_properties(materialGPULink->value,
        position->value, rotation->value, scale1D->value, brightness->value) == -1) {
        return;
    }
}*/
//if (opengl_set_material(materialGPULink->value)) {
// unsigned char has_mesh_colors = ecs_has(world, it->entities[i], MeshColors);
// set_color_vertex_layout(materialGPULink->value);
/*if (opengl_set_material3D_properties(materialGPULink->value,
position->value, rotation->value, scale1D->value, brightness->value) == -1) {
return;
}*/
// opengl_set_camera_view_matrix(materialGPULink->value, main_camera_matrix);
//}
        // glBindBuffer(GL_ARRAY_BUFFER, meshGPULink->value.y);
        // opengl_set_mesh_indicies(meshGPULink->value.x);