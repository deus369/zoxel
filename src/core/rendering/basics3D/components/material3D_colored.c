typedef struct {
    GLint vertex_position;
    GLint vertex_color;
    GLuint position;
    GLuint rotation;
    GLuint scale;
    GLuint camera_matrix;
    GLuint brightness;
    GLuint fog_data;
} MaterialColored3D;
zox_custom_component(MaterialColored3D)

MaterialColored3D create_MaterialColored3D(const GLuint material) {
    return (MaterialColored3D) {
        glGetAttribLocation(material, "vertex_position"),
        glGetAttribLocation(material, "vertex_color"),
        glGetUniformLocation(material, "position"),
        glGetUniformLocation(material, "rotation"),
        glGetUniformLocation(material, "scale"),
        glGetUniformLocation(material, "camera_matrix"),
        glGetUniformLocation(material, "brightness"),
        glGetUniformLocation(material, "fog_data")
    };
}
