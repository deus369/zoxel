typedef struct {
    GLint vertex_position;
    GLint vertex_color;
    GLuint transform_matrix;
    GLuint camera_matrix;
    GLuint bone_matrix;
    GLuint brightness;
    GLuint fog_data;
} MaterialColored3D;
zox_custom_component(MaterialColored3D)

MaterialColored3D create_MaterialColored3D(const GLuint material) {
    return (MaterialColored3D) {
        glGetAttribLocation(material, "vertex_position"),
        glGetAttribLocation(material, "vertex_color"),
        glGetUniformLocation(material, "transform_matrix"),
        glGetUniformLocation(material, "camera_matrix"),
        glGetUniformLocation(material, "bone_matrix"),
        glGetUniformLocation(material, "brightness"),
        glGetUniformLocation(material, "fog_data")
    };
}
