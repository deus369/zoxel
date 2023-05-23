//! Links to locations inside a base material.
typedef struct {
    GLint vertexPosition;
    uint view_matrix;
    uint position;
    uint rotation;
    uint scale;
    uint brightness;
} Material3D;

Material3D spawn_material3D_properties(uint material) {
    Material3D material3D;
    material3D.view_matrix = glGetUniformLocation(material, "camera_matrix");
    material3D.position = glGetUniformLocation(material, "position");
    material3D.rotation = glGetUniformLocation(material, "rotation");
    material3D.scale = glGetUniformLocation(material, "scale");
    material3D.brightness = glGetUniformLocation(material, "brightness");
    material3D.vertexPosition = glGetAttribLocation(material, "vertexPosition");
    return material3D;
}