typedef struct {
    GLint vertex_position;
    GLint vertex_uv;
    GLint vertex_color;
    GLuint position;
    GLuint rotation;
    GLuint scale;
    GLuint camera_matrix;
    GLuint texture;
    GLuint fog_data;
    GLuint brightness;
} MaterialTextured3D;
zox_custom_component(MaterialTextured3D)

MaterialTextured3D create_MaterialTextured3D(const GLuint material) {
    return (MaterialTextured3D) {
        glGetAttribLocation(material, "vertex_position"),
        glGetAttribLocation(material, "vertex_uv"),
        glGetAttribLocation(material, "vertex_color"),
        glGetUniformLocation(material, "position"),
        glGetUniformLocation(material, "rotation"),
        glGetUniformLocation(material, "scale"),
        glGetUniformLocation(material, "camera_matrix"),
        glGetUniformLocation(material, "tex"),
        glGetUniformLocation(material, "fog_data"),
        glGetUniformLocation(material, "brightness") };
}
