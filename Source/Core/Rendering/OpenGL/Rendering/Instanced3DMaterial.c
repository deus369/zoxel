// RenderParticle

const char* basicRender3DVertFilepath = "Resources/Shaders/3D/BasicRender3D.vert";
const char* basicRender3DFragFilepath = "Resources/Shaders/3D/BasicRender3D.frag";
GLuint materialInstance3D;
// cube reference
GLuint materialInstance3D_indicies;
GLuint materialInstance3D_vertices;
// MaterialInstance3D materialInstance3DProperties;

void DisposeInstanced3DMaterial()
{
    // glDeleteBuffers(1, &materialInstance3D_indicies);
    // glDeleteBuffers(1, &materialInstance3D_vertices);
}

void InitializeCubeMesh(GLuint material)
{

}

void InitializeInstanced3DProperties(GLuint material)
{

}

int LoadInstance3DMaterial()
{
    materialInstance3D = LoadMaterial(basicRender3DVertFilepath, basicRender3DFragFilepath);
    InitializeInstanced3DProperties(materialInstance3D);
    InitializeCubeMesh(materialInstance3D);
    return 0;
}