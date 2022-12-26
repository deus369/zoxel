typedef struct
{
    GLint vertexPosition;
    GLint vertexColor;
    GLuint view_matrix;
    GLuint position;
    GLuint rotation;
    GLuint scale;
    GLuint brightness;
} MaterialColored3D;

MaterialColored3D spawn_material3D_colored_properties(GLuint material)
{
    MaterialColored3D material3D;
    material3D.view_matrix = glGetUniformLocation(material, "viewMatrix");
    material3D.position = glGetUniformLocation(material, "position");
    material3D.rotation = glGetUniformLocation(material, "rotation");
    material3D.scale = glGetUniformLocation(material, "scale");
    material3D.brightness = glGetUniformLocation(material, "brightness");
    material3D.vertexPosition = glGetAttribLocation(material, "vertexPosition");
    material3D.vertexColor = glGetAttribLocation(material, "vertexColor");
    return material3D;
}