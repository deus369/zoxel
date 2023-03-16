typedef struct
{
    GLint vertexPosition;
    GLint vertexUV;
    GLuint view_matrix;
    GLuint position;
    GLuint rotation;
    GLuint scale;
    GLuint brightness;
    GLuint texture;
} Material3DTextured;

Material3DTextured shader_attributes_material_textured3D;
// const Material3DTextured shader_attributes_material_textured3D = (Material3DTextured) { 0, 1, 2, 3, 4, 5, 6, 7 };

/*Material3DTextured spawn_material3D_textured()
{
    Material3DTextured material3D;

    material3D.vertexPosition = 0;
    material3D.vertexUV = 1;
    material3D.view_matrix = 2;
    material3D.position = 3;
    material3D.rotation = 4;
    material3D.scale = 5;
    material3D.brightness = 6;
    material3D.texture = 7;
    
    return material3D;
}*/


/*material3D.view_matrix = glGetUniformLocation(material, "viewMatrix");
material3D.position = glGetUniformLocation(material, "position");
material3D.rotation = glGetUniformLocation(material, "rotation");
material3D.scale = glGetUniformLocation(material, "scale");
material3D.brightness = glGetUniformLocation(material, "brightness");
material3D.vertexPosition = glGetAttribLocation(material, "vertexPosition");
material3D.vertexUV = glGetAttribLocation(material, "vertexUV");
material3D.texture = glGetUniformLocation(material, "tex");*/
