// Shader3D Textured

GLuint2 shader3D_textured;
const char* shader3D_textured_filepath_vert = "resources/shaders/3D/BasicRender3D.vert";
const char* shader3D_textured_filepath_frag = "resources/shaders/3D/BasicRender3D.frag";

void dispose_shader3D_textured()
{
    glDeleteShader(shader3D_textured.x);
    glDeleteShader(shader3D_textured.y);
}

int load_shader3D_textured()
{
    shader3D_textured = spawn_gpu_shader(shader3D_textured_filepath_vert, shader3D_textured_filepath_frag);
    return 0;
}

void opengl_set_texture(GLuint texturel_buffer)
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texturel_buffer);
}

void opengl_upload_shader3D_textured(GLuint2 mesh_buffer, GLuint material_buffer,
    const int *indicies, int indicies_length, const float *verts, int verts_length,
    GLuint uv_buffer, const float *uvs, int uvs_length)
{
    Material3DTextured material3D = spawn_material3D_textured(material_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * 4, indicies, GL_STATIC_DRAW);
    // need to combine positions and uvs?
    glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
    glEnableVertexAttribArray(material3D.vertexPosition);
    glVertexAttribPointer(material3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 12, 0);
    glBufferData(GL_ARRAY_BUFFER, verts_length * 4, verts, GL_STATIC_DRAW);
    // uvs - combine with verts... this won't work?
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glEnableVertexAttribArray(material3D.vertexUV);
    glVertexAttribPointer(material3D.vertexUV, 2, GL_FLOAT, GL_FALSE, 8, 0);
    // glVertexAttribPointer(material3D.vertexUV, 2, GL_FLOAT, GL_FALSE, 8, (GLvoid*)(3 * sizeof(float)));
    glBufferData(GL_ARRAY_BUFFER, uvs_length * 4, uvs, GL_STATIC_DRAW);
    // printf("Setting Vertex Attribute Pointer for [%ix%i] Mesh.\n", mesh.x, mesh.y);
    // disable bindings
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // printf("Binding Data %i %i\n", indicies_length, verts_length);
}

void opengl_set_material3D_uvs_properties(GLuint material,
    const float4x4 viewMatrix, float3 position, float4 rotation, float scale, float brightness)
{
    // printf("Rendering Cube [%ix%i]\n", mesh.x, mesh.y);
    // printf("    - Rendering Cube [%ix%i]\n", squareTexturedMesh.x, squareTexturedMesh.y);
    Material3DTextured material3D = spawn_material3D_textured(material);
    glEnableVertexAttribArray(material3D.vertexPosition);
    glVertexAttribPointer(material3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 12, 0); // 4 * 3
    glUniformMatrix4fv(material3D.view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
    glUniform3f(material3D.position, position.x, position.y, position.z);
    glUniform4f(material3D.rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    glUniform1f(material3D.scale, scale);
    glUniform1f(material3D.brightness, brightness);
}