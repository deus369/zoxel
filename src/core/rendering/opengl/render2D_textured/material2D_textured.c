//! Links to locations inside a base material.
typedef struct {
    GLint vertexPosition;
    uint view_matrix;
    uint positionX;
    uint positionY;
    uint positionZ;
    uint angle;
    uint scale;
    uint brightness;
    // textured
    GLint vertexUV;
    uint texture;
} MaterialTextured2D;

MaterialTextured2D initialize_material2D_textured(uint material) {
    MaterialTextured2D materialTextured2D;
    materialTextured2D.view_matrix = glGetUniformLocation(material, "camera_matrix");
    materialTextured2D.positionX = glGetUniformLocation(material, "positionX");
    materialTextured2D.positionY = glGetUniformLocation(material, "positionY");
    materialTextured2D.positionZ = glGetUniformLocation(material, "positionZ");
    materialTextured2D.angle = glGetUniformLocation(material, "angle");
    materialTextured2D.scale = glGetUniformLocation(material, "scale");
    // materialTextured2D.scale2 = glGetUniformLocation(material, "scale2");
    materialTextured2D.brightness = glGetUniformLocation(material, "brightness");
    materialTextured2D.vertexPosition = glGetAttribLocation(material, "vertexPosition");
    // textured
    materialTextured2D.vertexUV = glGetAttribLocation(material, "vertexUV");
    materialTextured2D.texture = glGetUniformLocation(material, "tex");
    return materialTextured2D;
}