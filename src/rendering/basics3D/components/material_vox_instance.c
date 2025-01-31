typedef struct {
    GLint vertex_position;
    GLint vertex_color;
    GLint matrices;
    GLuint camera_matrix;
    GLuint brightness;
    GLuint fog_data;
} MaterialVoxInstance;
zox_custom_component(MaterialVoxInstance)

MaterialVoxInstance create_MaterialVoxInstance(const GLuint material) {
    return (MaterialVoxInstance) {
        glGetAttribLocation(material, "vertex_position"),
        glGetAttribLocation(material, "vertex_color"),
        glGetUniformBlockIndex(material, "InstanceMatrices"),
        glGetUniformLocation(material, "camera_matrix"),
        glGetUniformLocation(material, "brightness"),
        glGetUniformLocation(material, "fog_data")
    };
}
