// RenderParticle

const char* basicRender3DVertFilepath = "resources/shaders/3D/BasicRender3D.vert";
const char* basicRender3DFragFilepath = "resources/shaders/3D/BasicRender3D.frag";
GLuint materialInstance3D;
Material3D material3D;
GLuint materialInstance3D_indicies;
GLuint materialInstance3D_vertices;

void DisposeInstanced3DMaterial()
{
    glDeleteBuffers(1, &materialInstance3D_indicies);
    glDeleteBuffers(1, &materialInstance3D_vertices);
    glDeleteProgram(materialInstance3D);
}

GLuint2 spawn_gpu_mesh()
{
    GLuint2 mesh;
    glGenBuffers(1, &mesh.x);
    glGenBuffers(1, &mesh.y);
    return mesh;
}

void set_gpu_mesh(GLuint2 mesh, GLuint material, float verts[])
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareTexturedIndicies), squareTexturedIndicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    // do i need this here?
    GLint vertexPosition = glGetAttribLocation(material, "vertexPosition");
    glEnableVertexAttribArray(vertexPosition);
    glVertexAttribPointer(vertexPosition, 2, GL_FLOAT, GL_FALSE, 8, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InitializeCubeMesh(GLuint material)
{
    glGenBuffers(1, &materialInstance3D_indicies);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, materialInstance3D_indicies);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareTexturedIndicies), squareTexturedIndicies, GL_STATIC_DRAW);
    glGenBuffers(1, &materialInstance3D_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, materialInstance3D_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVerts), squareVerts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(material3D.vertexPosition);
    glVertexAttribPointer(material3D.vertexPosition, 2, GL_FLOAT, GL_FALSE, 8, 0);
    // reset
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InitializeInstanced3DProperties(GLuint material)
{
    material3D.view_matrix = glGetUniformLocation(material, "viewMatrix");
    material3D.position = glGetUniformLocation(material, "position");
    material3D.rotation = glGetUniformLocation(material, "rotation");
    material3D.scale = glGetUniformLocation(material, "scale");
    material3D.brightness = glGetUniformLocation(material, "brightness");
    material3D.vertexPosition = glGetAttribLocation(material, "vertexPosition");
}

int LoadInstance3DMaterial()
{
    materialInstance3D = LoadMaterial(basicRender3DVertFilepath, basicRender3DFragFilepath);
    InitializeInstanced3DProperties(materialInstance3D);
    InitializeCubeMesh(materialInstance3D);
    return 0;
}

void OpenGLBeginInstancing3D(const float4x4 viewMatrix)
{
    //! This sets the materials actually, would be best to group entities per material here?
    glUseProgram(materialInstance3D);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, materialInstance3D_indicies);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, materialInstance3D_vertices);            // for vertex coordinates
    glUniformMatrix4fv(material3D.view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
}

//! Set variables, can this be done using a filtered / system ?
void RenderEntity3D(float3 position, float4 rotation, float scale1D, float brightness)
{
    glUniform3f(material3D.position, position.x, position.y, position.z);
    glUniform4f(material3D.rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    glUniform1f(material3D.scale, scale1D);
    glUniform1f(material3D.brightness, brightness);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL); // &squareTexturedIndicies);
}

void OpenGLEndInstancing3D()
{
    glUseProgram(0);
}