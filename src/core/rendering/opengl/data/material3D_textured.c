typedef struct
{
    GLint vertexPosition;
    GLuint view_matrix;
    GLuint position;
    GLuint rotation;
    GLuint scale;
    GLuint brightness;
    // textured
    GLint vertexUV;
    GLuint texture;
} Material3DTextured;

Material3DTextured spawn_material3D_textured(GLuint material)
{
    Material3DTextured material3D;
    material3D.view_matrix = glGetUniformLocation(material, "viewMatrix");
    material3D.position = glGetUniformLocation(material, "position");
    material3D.rotation = glGetUniformLocation(material, "rotation");
    material3D.scale = glGetUniformLocation(material, "scale");
    material3D.brightness = glGetUniformLocation(material, "brightness");
    material3D.vertexPosition = glGetAttribLocation(material, "vertexPosition");
    // textured
    material3D.vertexUV = glGetAttribLocation(material, "vertexUV");
    material3D.texture = glGetUniformLocation(material, "tex");
    return material3D;
}