void set_basic_vert_layout(const Material3D *attributes) {
    // Material3D material3D = spawn_material3D_properties(material);
    glEnableVertexAttribArray(attributes->vertex_position);
    glVertexAttribPointer(attributes->vertex_position, 3, GL_FLOAT, GL_FALSE, 4 * 3, 0);
}

int opengl_set_material3D_properties(const Material3D *attributes, const float3 position, const float4 rotation, const float scale, const float brightness) {
    // Material3D material3D = spawn_material3D_properties(material);
    //glEnableVertexAttribArray(material3D.vertex_position);
    //glVertexAttribPointer(material3D.vertex_position, 3, GL_FLOAT, GL_FALSE, 4 * 3, 0);
    glUniform3f(attributes->position, position.x, position.y, position.z);
    glUniform4f(attributes->rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    glUniform1f(attributes->scale, scale);
    glUniform1f(attributes->brightness, brightness);
#ifdef zoxel_catch_opengl_errors
    check_opengl_error("opengl_set_material3D_properties");
#endif
    return 0;
}
