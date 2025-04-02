void Render3DSystem(ecs_iter_t *it) {
    zox_field_in(TransformMatrix, transformMatrixs, 1)
    zox_field_in(Brightness, brightnesses, 2)
    zox_field_in(MeshGPULink, meshGPULinks, 3)
    zox_field_in(MeshIndicies, meshIndiciess, 4)
    zox_field_in(MaterialGPULink, materialGPULinks, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MeshIndicies, meshIndiciess, meshIndicies)
        if (meshIndicies->length == 0) continue;
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) continue;
        zox_field_i(MaterialGPULink, materialGPULinks, materialGPULink)
        if (materialGPULink->value == 0) continue;
        zox_field_i(Brightness, brightnesses, brightness)
        zox_field_i(TransformMatrix, transformMatrixs, transformMatrix)
        MaterialBasic3D attributes = create_MaterialBasic3D(materialGPULink->value);

        opengl_set_material(materialGPULink->value);
        opengl_set_matrix(attributes.camera_matrix, render_camera_matrix);
        opengl_set_float4(attributes.fog_data, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
        opengl_set_float(attributes.brightness, brightness->value);
        opengl_set_matrix(attributes.transform_matrix, transformMatrix->value);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(attributes.vertex_position, meshGPULink->value.y);

        opengl_render(meshIndicies->length);

        // disabling
        opengl_disable_buffer(attributes.vertex_position);
        opengl_unset_mesh();
        opengl_disable_opengl_program();

        catch_basic3D_errors("! Render3DSystem");
    }
} zox_declare_system(Render3DSystem)

// skybox render system
/*int opengl_set_material3D_properties(const Material3D *attributes, const float3 position, const float4 rotation, const float scale, const float brightness) {
 *    glUniform3f(attributes->position, position.x, position.y, position.z);
 *    glUniform4f(attributes->rotation, rotation.x, rotation.y, rotation.z, rotation.w);
 *    glUniform1f(attributes->scale, scale);
 *    glUniform1f(attributes->brightness, brightness);
 *    return 0;
 * }
 *
 * void set_basic_vert_layout(const Material3D *attributes) {
 *    glEnableVertexAttribArray(attributes->vertex_position);
 *    glVertexAttribPointer(attributes->vertex_position, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
 * }*/


        // Material3D attributes = spawn_material3D_properties(materialGPULink->value);
        /*opengl_set_material(materialGPULink->value);
        opengl_bind_mesh(meshGPULink->value);
        // set_basic_vert_layout(&attributes);
        opengl_set_matrix(attributes.transform_matrix, transformMatrix->value);
        opengl_enable_vertex_buffer(attributes.vertex_position, meshGPULink->value.y);
        glUniform1f(attributes.brightness, brightness->value);
        //if (opengl_set_material3D_properties(&attributes, position3D->value, rotation3D->value, scale1D->value, brightness->value) == -1) {
        //    break;
        //}
        //  glGetUniformLocation(materialGPULink->value, "camera_matrix")
        glUniformMatrix4fv(attributes.camera_matrix, 1, GL_FALSE, (float*) &render_camera_matrix);
        opengl_render(meshIndicies->length);*/
