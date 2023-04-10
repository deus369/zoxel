typedef struct {
    GLint vertexPosition;
    GLint vertexColor;
    GLuint view_matrix;
    GLuint position;
    GLuint rotation;
    GLuint scale;
    GLuint brightness;
    GLuint fog_data;
} MaterialColored3D;

MaterialColored3D spawn_material3D_colored_properties(GLuint material) {
    MaterialColored3D materialColored3D;
    materialColored3D.view_matrix = glGetUniformLocation(material, "viewMatrix");
    materialColored3D.position = glGetUniformLocation(material, "position");
    materialColored3D.rotation = glGetUniformLocation(material, "rotation");
    materialColored3D.scale = glGetUniformLocation(material, "scale");
    materialColored3D.brightness = glGetUniformLocation(material, "brightness");
    materialColored3D.vertexPosition = glGetAttribLocation(material, "vertexPosition");
    materialColored3D.vertexColor = glGetAttribLocation(material, "vertexColor");
    materialColored3D.fog_data = glGetAttribLocation(material, "fog_data");
    return materialColored3D;
}