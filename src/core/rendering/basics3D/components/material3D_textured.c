typedef struct {
    GLint vertex_position;
    GLint vertex_uv;
    GLint vertex_color;
    GLuint camera_matrix;
    GLuint position;
    GLuint rotation;
    GLuint scale;
    GLuint texture;
    GLuint fog_data;
    GLuint brightness;
} Textured3DAttributes;
zox_custom_component(Textured3DAttributes)