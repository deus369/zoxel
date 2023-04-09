void set_basic_vert_layout(GLuint material) {
    Material3D material3D = spawn_material3D_properties(material);
    glEnableVertexAttribArray(material3D.vertexPosition);
    glVertexAttribPointer(material3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 4 * 3, 0);
}

int opengl_set_material3D_properties(GLuint material,
    float3 position, float4 rotation, float scale, float brightness) {
    Material3D material3D = spawn_material3D_properties(material);
    //glEnableVertexAttribArray(material3D.vertexPosition);
    //glVertexAttribPointer(material3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 4 * 3, 0);
    glUniform3f(material3D.position, position.x, position.y, position.z);
    glUniform4f(material3D.rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    glUniform1f(material3D.scale, scale);
    glUniform1f(material3D.brightness, brightness);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("opengl_set_material3D_properties");
    #endif
    return 0;
}