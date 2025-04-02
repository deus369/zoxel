GLuint materialInstance3D;
GLuint2 materialInstance3D_mesh;

void dispose_shader3D_instance_material() {
    glDeleteShader(shader3D.x);
    glDeleteShader(shader3D.y);
    glDeleteBuffers(1, &materialInstance3D_mesh.x);
    glDeleteBuffers(1, &materialInstance3D_mesh.y);
    glDeleteProgram(materialInstance3D);
}

int load_shader3D_basic() {
    shader3D = spawn_gpu_shader_inline(shader3D_vert_buffer, shader3D_frag_buffer);
    materialInstance3D = spawn_gpu_material_program((const GLuint2) { shader3D.x, shader3D.y });
    return 0;
}

/*void opengl_instance3D_begin(const float4x4 viewMatrix) {
    //! This sets the materials actually, would be best to group entities per material here?
    glUseProgram(materialInstance3D);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, materialInstance3D_mesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, materialInstance3D_mesh.y);            // for vertex coordinates
    glEnableVertexAttribArray(material3D.vertex_position);
    glVertexAttribPointer(material3D.vertex_position, 2, GL_FLOAT, GL_FALSE, 8, 0);
    glUniformMatrix4fv(material3D.camera_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
}*/

//! Set variables, can this be done using a filtered / system ?