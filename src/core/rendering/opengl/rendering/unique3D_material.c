extern void InitializeMaterialPropertiesB(GLuint material, MaterialTextured2D *materialTextured2D);
// does this per material!
void render_unique3D(const float4x4 viewMatrix, GLuint2 mesh, GLuint material, float3 position, float4 rotation, float scale, float brightness, int indicies_length)
{
    if (material == 0)
    {
        // printf("render_entity_material2D material is 0.\n");
        return;
    }
    // printf("Rendering Cube [%ix%i]\n", mesh.x, mesh.y);
    // printf("    - Rendering Cube [%ix%i]\n", squareTexturedMesh.x, squareTexturedMesh.y);
    Material3D material3D;
    InitializeInstanced3DProperties(material, &material3D);
    glUseProgram(material);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);            // for vertex coordinates
    glEnableVertexAttribArray(material3D.vertexPosition);
    glVertexAttribPointer(material3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 12, 0); // 4 * 3
    glUniformMatrix4fv(material3D.view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
    glUniform3f(material3D.position, position.x, position.y, position.z);
    glUniform4f(material3D.rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    glUniform1f(material3D.scale, scale);
    glUniform1f(material3D.brightness, brightness);
    glDrawElements(GL_TRIANGLES, indicies_length, GL_UNSIGNED_INT, NULL);
    glUseProgram(0);
    /*GLenum err65 = glGetError();
    if (err65 != GL_NO_ERROR)
    {
        printf("render_unique3D GLError [%i]: %i\n", material, err65);
        return;
    }*/
}