//! Keep property reference in material, upon creation.
// #define zoxel_catch_opengl_errors
// first, get working on pc
//  then, move texture updating to the entity system
// texture issues
//  https://www.reddit.com/r/opengl/comments/ydsqkn/textured_square_works_on_pinephone_pro_but_not_pc/
//  https://github.com/edo9300/edopro/issues/151
// const char *playerCharacterTextureName = "resources/textures/Test.png";
const bool disableTextureLoaded = false;
int textureType = GL_NEAREST; // GL_LINEAR
//! \todo Move these references to MaterialGPULink
//! \todo Update texture based on Player Entity texture updateing
GLuint2 shader2D_textured;
// not used atm
//const char* shader2D_textured_filepath_vert = resources_folder_name"shaders/2D/textured2D.vert";
//const char* shader2D_textured_filepath_frag = resources_folder_name"shaders/2D/textured2D.frag";
// MaterialGPULink and properties
GLuint texturedMaterial;
//! Mesh B - Buffers/Texture
GLuint2 squareTexturedMesh;
GLuint squareTexturedModelUVs;
const GLchar* shader2D_textured_vert_buffer = "\
#version 300 es\n\
in lowp vec2 vertexPosition;\
in lowp vec2 vertexUV;\
uniform lowp mat4 viewMatrix;\
uniform lowp float positionX;\
uniform lowp float positionY;\
uniform lowp float positionZ;\
uniform lowp float angle;\
uniform lowp float scale;\
out lowp vec2 uv;\
\
void main()\
{\
    vec2 position = vec2(positionX, positionY);\
    mat2 rotate = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));\
    gl_Position = viewMatrix * vec4(position + (rotate * vertexPosition) * scale, positionZ, 1.0);\
    uv = vertexUV;\
}\
";
const GLchar* shader2D_textured_frag_buffer = "\
#version 300 es\n\
in lowp vec2 uv;\
uniform lowp float brightness;\
uniform sampler2D tex;\
out lowp vec4 color;\
\
void main()\
{\
    color = texture(tex, uv) * brightness;\
}\
";

void dispose_shader2D_textured()
{
    glDeleteBuffers(1, &squareTexturedMesh.x);
    glDeleteBuffers(1, &squareTexturedMesh.y);
    glDeleteBuffers(1, &squareTexturedModelUVs);
    // glDeleteTextures(1, &textureID);
    glDeleteShader(shader2D_textured.x);
    glDeleteShader(shader2D_textured.y);
    glDeleteProgram(texturedMaterial);
#ifdef zoxel_catch_opengl_errors
    GLenum err7 = glGetError();
    if (err7 != GL_NO_ERROR)
    {
        printf("GL ERROR - dispose_opengl: %i\n", err7);
    }
#endif
}

void initialize_texture_mesh(GLuint material)
{
    MaterialTextured2D materialTextured2D = initialize_material2D_textured(material);
    // gen buffers
    glGenBuffers(1, &squareTexturedMesh.x);
    glGenBuffers(1, &squareTexturedMesh.y);  // generate a new VBO and get the associated ID
    glGenBuffers(1, &squareTexturedModelUVs);  // generate a new VBO and get the associated ID
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareTexturedMesh.x);
    glBindBuffer(GL_ARRAY_BUFFER, squareTexturedMesh.y);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indicies), square_indicies, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareTexturedVerts), squareTexturedVerts, GL_STATIC_DRAW); 
    glVertexAttribPointer(materialTextured2D.vertexPosition, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(0 * sizeof(float)));
    glVertexAttribPointer(materialTextured2D.vertexUV, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(2 * sizeof(float)));
    glEnableVertexAttribArray(materialTextured2D.vertexPosition);
    glEnableVertexAttribArray(materialTextured2D.vertexUV);
    // printf("Setting Vertex Attribute Pointer for [%ix%i] Mesh.\n", squareTexturedMesh.x, squareTexturedMesh.y);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
#ifdef zoxel_catch_opengl_errors
    GLenum err7 = glGetError();
    if (err7 != GL_NO_ERROR)
    {
        printf("GL ERROR with end of initialize_texture_mesh: %i\n", err7);
    }
#endif
}

int load_shader2D_textured()
{
    shader2D_textured = spawn_gpu_shader_inline(shader2D_textured_vert_buffer, shader2D_textured_frag_buffer);
    texturedMaterial = spawn_gpu_material_program((const GLuint2) { shader2D_textured.x, shader2D_textured.y });
    // texturedMaterial = load_gpu_shader(&shader2D_textured, shader2D_textured_filepath_vert, shader2D_textured_filepath_frag);
    initialize_texture_mesh(texturedMaterial);
    return 0;
}

GLuint spawn_gpu_texture_buffers()
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureType);
    glBindTexture(GL_TEXTURE_2D, 0);
    return textureID;
}

void render_entity_material2D(const float4x4 viewMatrix, GLuint material, GLuint texture,
    float2 position, float angle, float scale, float brightness)
{
    if (material == 0)
    {
        // printf("render_entity_material2D material is 0.\n");
        return;
    }
    MaterialTextured2D materialTextured2D = initialize_material2D_textured(material);
    glUseProgram(material);   // invalid operation
    /*GLenum err65 = glGetError();
    if (err65 != GL_NO_ERROR)
    {
        printf("GLError [glUseProgram(material) %i]: %i\n", material, err65);
        return;
    }*/
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareTexturedMesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, squareTexturedMesh.y);            // for vertex buffer data
    glEnableVertexAttribArray(materialTextured2D.vertexPosition);
    glEnableVertexAttribArray(materialTextured2D.vertexUV);
    glVertexAttribPointer(materialTextured2D.vertexPosition, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(0 * sizeof(float)));
    glVertexAttribPointer(materialTextured2D.vertexUV, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(2 * sizeof(float)));
    glUniformMatrix4fv(materialTextured2D.view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
    glUniform1f(materialTextured2D.positionX, position.x);
    glUniform1f(materialTextured2D.positionY, position.y);
    glUniform1f(materialTextured2D.angle, angle);
    glUniform1f(materialTextured2D.scale, scale);
    glUniform1f(materialTextured2D.brightness, brightness);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    /*GLenum err66 = glGetError();
    if (err66 != GL_NO_ERROR)
    {
        printf("GLError [render_entity_material2D]: %i\n", err66);
        return;
    }*/
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glUseProgram(0);
}

void render_entity_material2D_and_mesh(const float4x4 viewMatrix, GLuint2 mesh, GLuint material, GLuint texture,
    float2 position, float angle, float scale, float brightness, unsigned char layer)
{
    if (material == 0)
    {
        // printf("render_entity_material2D material is 0.\n");
        return;
    }
    MaterialTextured2D materialTextured2D = initialize_material2D_textured(material);
    glUseProgram(material);   // invalid operation
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS);
    // glEnable(GL_ALPHA_TEST);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);            // for vertex coordinates
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnableVertexAttribArray(materialTextured2D.vertexPosition);
    glEnableVertexAttribArray(materialTextured2D.vertexUV);
    glVertexAttribPointer(materialTextured2D.vertexPosition, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(0 * sizeof(float)));
    glVertexAttribPointer(materialTextured2D.vertexUV, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(2 * sizeof(float)));
    glUniformMatrix4fv(materialTextured2D.view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
    glUniform1f(materialTextured2D.positionX, position.x);
    glUniform1f(materialTextured2D.positionY, position.y);
    glUniform1f(materialTextured2D.positionZ, ((int) layer) * +0.0001f);
    glUniform1f(materialTextured2D.angle, angle);
    glUniform1f(materialTextured2D.scale, scale);
    glUniform1f(materialTextured2D.brightness, brightness);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    /*GLenum err66 = glGetError();
    if (err66 != GL_NO_ERROR)
    {
        printf("GLError [render_entity_material2D]: %i\n", err66);
        return;
    }*/
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
    glDisable(GL_BLEND);
    // glDisable(GL_ALPHA_TEST);
    // glDisable(GL_DEPTH_TEST);
}

// #ifdef zoxel_catch_opengl_errors
//     GLenum err66 = glGetError();
//     if (err66 != GL_NO_ERROR)
//     {
//         printf("GL ERROR with End of render_entity_material2D: %i\n", err66);
//         return;
//     }
// #endif
    /*if (load_shader(shader2D_textured_filepath_vert, GL_VERTEX_SHADER, &shader2D_textured.x) != 0)
    {
        printf("Error loading shader vert 2D.\n");
        return -1;
    }
    if (load_shader(shader2D_textured_filepath_frag, GL_FRAGMENT_SHADER, &shader2D_textured.y) != 0)
    {
        printf("Error loading shader frag 2D.\n");
        return -1;
    }
    texturedMaterial = spawn_gpu_material_program(shader2D_textured);*/

/*void RenderEntityMaterial2D2(const float4x4 viewMatrix, GLuint material, GLuint texture,
    float2 position, float angle, float2 scale, float brightness)
{
    if (material == 0)
    {
        // printf("render_entity_material2D material is 0.\n");
        return;
    }
    MaterialTextured2D materialTextured2D;
    initialize_material2D_textured(material, &materialTextured2D);
    glUseProgram(material);   // invalid operation
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareTexturedMesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, squareTexturedMesh.y);            // for vertex buffer data
    glEnableVertexAttribArray(materialTextured2D.vertexPosition);
    glEnableVertexAttribArray(materialTextured2D.vertexUV);
    glVertexAttribPointer(materialTextured2D.vertexPosition, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(0 * sizeof(float)));
    glVertexAttribPointer(materialTextured2D.vertexUV, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(2 * sizeof(float)));
    glUniformMatrix4fv(materialTextured2D.view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
    glUniform1f(materialTextured2D.positionX, position.x);
    glUniform1f(materialTextured2D.positionY, position.y);
    glUniform1f(materialTextured2D.angle, angle);
    glUniform2f(materialTextured2D.scale, scale.x, scale.y);
    // glUniform2f(materialTextured2D.scale2, scale.x, scale.y);
    glUniform1f(materialTextured2D.brightness, brightness);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glUseProgram(0);
}*/