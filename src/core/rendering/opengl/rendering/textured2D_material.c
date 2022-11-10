//! Functions for handling textured2D_material (SquareTextured2D)
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

//! Keep property reference in material, upon creation.
// #define DEVBUILD
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
GLuint2 textured2DShader;
const char* texturedRender2DVertPath = "resources/shaders/2D/TexturedRender2D.vert";
const char* texturedRender2DFragPath = "resources/shaders/2D/TexturedRender2D.frag";
// MaterialGPULink and properties
GLuint texturedMaterial;
//! Mesh B - Buffers/Texture
GLuint2 squareTexturedMesh;
GLuint squareTexturedModelUVs;

void DisposeTexturedMaterial2D()
{
    glDeleteBuffers(1, &squareTexturedMesh.x);
    glDeleteBuffers(1, &squareTexturedMesh.y);
    glDeleteBuffers(1, &squareTexturedModelUVs);
    // glDeleteTextures(1, &textureID);
    glDeleteShader(textured2DShader.x);
    glDeleteShader(textured2DShader.y);
    glDeleteProgram(texturedMaterial);
#ifdef DEVBUILD
    GLenum err7 = glGetError();
    if (err7 != GL_NO_ERROR)
    {
        printf("GL HAD ERROR with end of dispose_opengl: %i\n", err7);
    }
#endif
}

void InitializeMaterialPropertiesB(GLuint material, MaterialTextured2D *materialTextured2D)
{
    materialTextured2D->view_matrix = glGetUniformLocation(material, "viewMatrix");
    materialTextured2D->positionX = glGetUniformLocation(material, "positionX");
    materialTextured2D->positionY = glGetUniformLocation(material, "positionY");
    materialTextured2D->angle = glGetUniformLocation(material, "angle");
    materialTextured2D->scale = glGetUniformLocation(material, "scale");
    materialTextured2D->scale2 = glGetUniformLocation(material, "scale2");
    materialTextured2D->brightness = glGetUniformLocation(material, "brightness");
    materialTextured2D->vertexPosition = glGetAttribLocation(material, "vertexPosition");
    materialTextured2D->vertexUV = glGetAttribLocation(material, "vertexUV");
    materialTextured2D->texture = glGetUniformLocation(material, "tex");
}

void InitializeTexturedMesh(GLuint material)
{
    MaterialTextured2D materialTextured2D;
    InitializeMaterialPropertiesB(material, &materialTextured2D);
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
    printf("Setting Vertex Attribute Pointer for [%ix%i] Mesh.\n", squareTexturedMesh.x, squareTexturedMesh.y);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
#ifdef DEVBUILD
    GLenum err7 = glGetError();
    if (err7 != GL_NO_ERROR)
    {
        printf("GL HAD ERROR with end of InitializeTexturedMesh: %i\n", err7);
    }
#endif
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

void RenderEntityMaterial2D2(const float4x4 viewMatrix, GLuint material, GLuint texture,
    float2 position, float angle, float2 scale, float brightness)
{
    if (material == 0)
    {
        // printf("render_entity_material2D material is 0.\n");
        return;
    }
    MaterialTextured2D materialTextured2D;
    InitializeMaterialPropertiesB(material, &materialTextured2D);
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
    glUniform2f(materialTextured2D.scale2, scale.x, scale.y);
    glUniform1f(materialTextured2D.brightness, brightness);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glUseProgram(0);
}

void render_entity_material2D(const float4x4 viewMatrix, GLuint material, GLuint texture,
    float2 position, float angle, float scale, float brightness)
{
    if (material == 0)
    {
        // printf("render_entity_material2D material is 0.\n");
        return;
    }
    MaterialTextured2D materialTextured2D;
    InitializeMaterialPropertiesB(material, &materialTextured2D);
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
    float2 position, float angle, float scale, float brightness)
{
    if (material == 0)
    {
        // printf("render_entity_material2D material is 0.\n");
        return;
    }
    MaterialTextured2D materialTextured2D;
    InitializeMaterialPropertiesB(material, &materialTextured2D);
    glUseProgram(material);   // invalid operation
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);            // for vertex coordinates
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture);
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

int LoadTextureRender2DShader()
{
    texturedMaterial = load_gpu_shader(&textured2DShader, texturedRender2DVertPath, texturedRender2DFragPath);
    InitializeTexturedMesh(texturedMaterial);
    return 0;
}

// #ifdef DEVBUILD
//     GLenum err66 = glGetError();
//     if (err66 != GL_NO_ERROR)
//     {
//         printf("GL HAD ERROR with End of render_entity_material2D: %i\n", err66);
//         return;
//     }
// #endif
    /*if (LoadShader(texturedRender2DVertPath, GL_VERTEX_SHADER, &textured2DShader.x) != 0)
    {
        printf("Error loading shader vert 2D.\n");
        return -1;
    }
    if (LoadShader(texturedRender2DFragPath, GL_FRAGMENT_SHADER, &textured2DShader.y) != 0)
    {
        printf("Error loading shader frag 2D.\n");
        return -1;
    }
    texturedMaterial = spawn_gpu_material_program(textured2DShader);*/