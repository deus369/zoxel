//! Links to locations inside a base material.
typedef struct {
    GLint vertex_position;
    GLuint camera_matrix;
    GLuint positionX;
    GLuint positionY;
    GLuint positionZ;
    GLuint angle;
    GLuint scale;
    GLuint brightness;
    GLint vertex_uv;
    GLuint texture;
} MaterialTextured2D;

MaterialTextured2D initialize_material2D_textured(GLuint material) {
    MaterialTextured2D materialTextured2D;
    materialTextured2D.camera_matrix = glGetUniformLocation(material, "camera_matrix");
    materialTextured2D.positionX = glGetUniformLocation(material, "positionX");
    materialTextured2D.positionY = glGetUniformLocation(material, "positionY");
    materialTextured2D.positionZ = glGetUniformLocation(material, "positionZ");
    materialTextured2D.angle = glGetUniformLocation(material, "angle");
    materialTextured2D.scale = glGetUniformLocation(material, "scale");
    // materialTextured2D.scale2 = glGetUniformLocation(material, "scale2");
    materialTextured2D.brightness = glGetUniformLocation(material, "brightness");
    materialTextured2D.vertex_position = glGetAttribLocation(material, "vertex_position");
    // textured
    materialTextured2D.vertex_uv = glGetAttribLocation(material, "vertex_uv");
    materialTextured2D.texture = glGetUniformLocation(material, "tex");
    return materialTextured2D;
}