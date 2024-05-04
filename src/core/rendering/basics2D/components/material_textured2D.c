typedef struct {
    GLint vertex_position;
    GLint vertex_uv;
    GLuint position;
    GLuint angle;
    GLuint scale;
    GLuint camera_matrix;
    GLuint texture;
    GLuint brightness;
    GLuint alpha;
} MaterialTextured2D;
zox_custom_component(MaterialTextured2D)

MaterialTextured2D create_MaterialTextured2D(const GLuint material) {
    return (MaterialTextured2D) {
        glGetAttribLocation(material, "vertex_position"),
        glGetAttribLocation(material, "vertex_uv"),
        glGetUniformLocation(material, "position"),
        glGetUniformLocation(material, "angle"),
        glGetUniformLocation(material, "scale"),
        glGetUniformLocation(material, "camera_matrix"),
        glGetUniformLocation(material, "texture"),
        glGetUniformLocation(material, "brightness"),
        glGetUniformLocation(material, "alpha") };
}
