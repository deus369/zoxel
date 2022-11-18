extern void initialize_material2D_textured(GLuint material, MaterialTextured2D *materialTextured2D);

//! Sets material properties
void opengl_set_material3D_properties(GLuint material,
    const float4x4 viewMatrix, float3 position, float4 rotation, float scale, float brightness)
{
    // printf("Rendering Cube [%ix%i]\n", mesh.x, mesh.y);
    // printf("    - Rendering Cube [%ix%i]\n", squareTexturedMesh.x, squareTexturedMesh.y);
    Material3D material3D = spawn_material3D_properties(material);
    glEnableVertexAttribArray(material3D.vertexPosition);
    glVertexAttribPointer(material3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 12, 0); // 4 * 3
    glUniformMatrix4fv(material3D.view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
    glUniform3f(material3D.position, position.x, position.y, position.z);
    glUniform4f(material3D.rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    glUniform1f(material3D.scale, scale);
    glUniform1f(material3D.brightness, brightness);
}

/*GLenum err65 = glGetError();
if (err65 != GL_NO_ERROR)
{
    printf("render_unique3D GLError [%i]: %i\n", material, err65);
    return;
}*/