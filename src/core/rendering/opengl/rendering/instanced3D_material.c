// RenderParticle

const char* basicRender3DVertFilepath = resources_folder_name"shaders/3D/BasicRender3D.vert";
const char* basicRender3DFragFilepath = resources_folder_name"shaders/3D/BasicRender3D.frag";
GLuint2 instanceShader3D;
GLuint materialInstance3D;
Material3D material3D;
GLuint2 materialInstance3D_mesh;

void DisposeInstanced3DMaterial()
{
    glDeleteShader(instanceShader3D.x);
    glDeleteShader(instanceShader3D.y);
    glDeleteBuffers(1, &materialInstance3D_mesh.x);
    glDeleteBuffers(1, &materialInstance3D_mesh.y);
    glDeleteProgram(materialInstance3D);
}

void InitializeCubeMesh(GLuint material)
{
    glGenBuffers(1, &materialInstance3D_mesh.x);
    glGenBuffers(1, &materialInstance3D_mesh.y);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, materialInstance3D_mesh.x);
    glBindBuffer(GL_ARRAY_BUFFER, materialInstance3D_mesh.y);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indicies), square_indicies, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(material3D.vertexPosition);
    glVertexAttribPointer(material3D.vertexPosition, 2, GL_FLOAT, GL_FALSE, 8, 0);
    // printf("Setting Vertex Attribute Pointer for [%ix%i] Mesh.\n", materialInstance3D_mesh.x, materialInstance3D_mesh.y);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int LoadInstance3DMaterial()
{
    materialInstance3D = load_gpu_shader(&instanceShader3D, basicRender3DVertFilepath, basicRender3DFragFilepath);
    material3D = spawn_material3D_properties(materialInstance3D);
    InitializeCubeMesh(materialInstance3D);
    return 0;
}

void OpenGLBeginInstancing3D(const float4x4 viewMatrix)
{
    //! This sets the materials actually, would be best to group entities per material here?
    glUseProgram(materialInstance3D);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, materialInstance3D_mesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, materialInstance3D_mesh.y);            // for vertex coordinates
    glEnableVertexAttribArray(material3D.vertexPosition);
    glVertexAttribPointer(material3D.vertexPosition, 2, GL_FLOAT, GL_FALSE, 8, 0);
    glUniformMatrix4fv(material3D.view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
}

//! Set variables, can this be done using a filtered / system ?
void RenderEntity3D(float3 position, float4 rotation, float scale1D, float brightness)
{
    glUniform3f(material3D.position, position.x, position.y, position.z);
    glUniform4f(material3D.rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    glUniform1f(material3D.scale, scale1D);
    glUniform1f(material3D.brightness, brightness);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

//! Set the mesh on the gpu by uploading indicies and vert buffers.
void set_gpu_mesh(GLuint2 mesh, GLuint material, const int *indicies, int indicies_length, const float *verts, int verts_length) // const float3 *verts)
{
    Material3D material3D = spawn_material3D_properties(material);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);
    glEnableVertexAttribArray(material3D.vertexPosition);
    glVertexAttribPointer(material3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 12, 0); // 4 * 3
    // printf("Binding Data %i %i\n", indicies_length, verts_length);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * 4, indicies, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, verts_length * 4, verts, GL_STATIC_DRAW);
    // printf("Setting Vertex Attribute Pointer for [%ix%i] Mesh.\n", mesh.x, mesh.y);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}