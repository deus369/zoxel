#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

//! Creates materials for Textured and Default 2D Shaders.
void CreateTexturedMesh();

float3 backgroundColor = { 0.2, 0.2, 0.5 };
// Stored Shader Variables
GLuint squareModel;
GLuint squareModelIndicies;
GLint attribVertexPositionA;
GLuint gl_view_matrix;
GLuint gl_positionX;
GLuint gl_positionY;
GLuint gl_angle;
GLuint gl_scale;
GLuint gl_brightness;

const char *playerCharacterTextureName = "Resources/Textures/Test.png";
// extern const char *outputTextureName;
GLuint tex_sampler_loc;
GLuint squareTexturedModelVertices;
GLuint squareTexturedModelUVs;
GLuint squareTexturedModelIndicies;
GLuint textureID;
GLint attribVertexPosition;
GLint attribVertexTexCoord;
// const char *outputTextureName = "Resources/Textures/Test.png";

void InitializeMesh()
{
    attribVertexPositionA = glGetAttribLocation(material, "vertexPosition");
    gl_angle = glGetUniformLocation(material, "angle");
    gl_scale = glGetUniformLocation(material, "scale");
    gl_brightness = glGetUniformLocation(material, "brightness");
    gl_positionX = glGetUniformLocation(material, "positionX");
    gl_positionY = glGetUniformLocation(material, "positionY");
    gl_view_matrix = glGetUniformLocation(material, "viewMatrix");
    // gen buffers
    glGenBuffers(1, &squareModelIndicies);
    glGenBuffers(1, &squareModel);
    // set buffer data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareModelIndicies);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareTexturedIndicies), squareTexturedIndicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, squareModel);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVerts), squareVerts, GL_STATIC_DRAW);
    glVertexAttribPointer(attribVertexPositionA, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(attribVertexPositionA);
    // reset
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // textured one
    //size_t vSize = sizeof(squareVerts);
    //size_t uvSize = sizeof(squareUVs);
    // printf("squareModelIndicies %i\n", squareModelIndicies);
    // printf("squareModel %i\n", squareModel);
    CreateTexturedMesh();
}

void CreateTexturedMesh()
{
    // get indexes
    attribVertexPosition = glGetAttribLocation(material2, "vertexPosition");
    attribVertexTexCoord = glGetAttribLocation(material2, "vertexUV");
    tex_sampler_loc = glGetUniformLocation(material2, "tex");
    /*printf("material2 %i\n", material2);
    printf("attribVertexPosition %i\n", attribVertexPosition);
    printf("attribVertexTexCoord %i\n", attribVertexTexCoord);*/
    // gen buffers
    glGenBuffers(1, &squareTexturedModelIndicies);
    glGenBuffers(1, &squareTexturedModelVertices);  // generate a new VBO and get the associated ID
    glGenBuffers(1, &squareTexturedModelUVs);  // generate a new VBO and get the associated ID
    // indicies
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareTexturedModelIndicies);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareTexturedIndicies2), squareTexturedIndicies2, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //verts
    glBindBuffer(GL_ARRAY_BUFFER, squareTexturedModelVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareTexturedVerts), squareTexturedVerts, GL_STATIC_DRAW); 
    // glVertexAttribPointer(attribVertexPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
    // glEnableVertexAttribArray(attribVertexPosition);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // texture
    SDL_Surface* surface = IMG_Load(playerCharacterTextureName);
    printf("BytesPerPixel: %i - ", surface->format->BytesPerPixel);
    printf("Loading Texture: [%s] of Size: %ix%i\n", playerCharacterTextureName, surface->w, surface->h);
    
    glGenTextures(1, &textureID);
    // glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    int colorMode = GL_RGB;
    if(surface->format->BytesPerPixel == 4)
    {
        colorMode = GL_RGBA;
    }
    int textureType = GL_NEAREST; // GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureType);
    // push data to gpu
    glTexImage2D(GL_TEXTURE_2D, 0, colorMode, surface->w, surface->h, 0, colorMode, GL_UNSIGNED_BYTE, surface->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_FreeSurface(surface);
}

void RenderEntityMaterial2D(const float4x4 viewMatrix, GLint material3, float2 position, float angle, float scale, float brightness)
{
    // printf("Rendering %i\n", material);
    glUseProgram(material3);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // glEnable(GL_TEXTURE_2D);
    glUniform1i(tex_sampler_loc, 0);  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareTexturedModelIndicies);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, squareTexturedModelVertices);            // for vertex coordinates
    glEnableVertexAttribArray(attribVertexPosition);
    glEnableVertexAttribArray(attribVertexTexCoord);
    GLintptr vertex_position_offset = 0 * sizeof(float);
    glVertexAttribPointer(attribVertexPosition, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)vertex_position_offset);
    GLintptr vertex_texcoord_offset = 2 * sizeof(float);
    glVertexAttribPointer(attribVertexTexCoord, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)vertex_texcoord_offset);
    glUniformMatrix4fv(gl_view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
    glUniform1f(gl_positionX, position.x);
    glUniform1f(gl_positionY, position.y);
    glUniform1f(gl_scale, scale);
    glUniform1f(gl_angle, angle);
    glUniform1f(gl_brightness, brightness);
    // finally draw it
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL); // (void*)0);               // ptr to indices

    // disable
    glDisableVertexAttribArray(attribVertexPosition);
    glDisableVertexAttribArray(attribVertexTexCoord);
    glBindTexture(GL_TEXTURE_2D, 0);
    // glDisable(GL_TEXTURE_2D);
    glUseProgram(0);
}

//! Cleanup OpenGL resources
void EndAppOpenGL()
{
    glDeleteBuffers(1, &squareModel);
    glDeleteBuffers(1, &squareModelIndicies);
    glDeleteBuffers(1, &squareTexturedModelVertices);
    glDeleteBuffers(1, &squareTexturedModelUVs);
    glDeleteBuffers(1, &squareTexturedModelIndicies);
    glDeleteProgram(material);
    glDeleteProgram(material2);
}

void UpdateBeginOpenGL(const float4x4 viewMatrix)
{
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);       // Clears the buffer ?
    glDisable(GL_DEPTH_TEST);
    //! This sets the materials actually, would be best to group entities per material here?
    glUseProgram(material);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareModelIndicies);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, squareModel);            // for vertex coordinates
    glEnableVertexAttribArray(attribVertexPosition);
    glVertexAttribPointer(attribVertexPosition, 2, GL_FLOAT, GL_FALSE, 8, 0);
    glUniformMatrix4fv(gl_view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
}

// does this per material!
void RenderEntity2D(float2 position, float angle, float scale, float brightness)
{
    // set variables, can this be done using a filtered / system ?
    glUniform1f(gl_positionX, position.x);
    glUniform1f(gl_positionY, position.y);
    glUniform1f(gl_scale, scale);
    glUniform1f(gl_angle, angle);
    glUniform1f(gl_brightness, brightness);
    // glDrawArrays(GL_TRIANGLE_STRIP, 0, count);
    // glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, &squareTexturedIndicies);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL); // &squareTexturedIndicies);
}

void UpdateEndOpenGL()
{
    glDisableVertexAttribArray(attribVertexPosition);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void EndAppGraphics()
{
    //EndAppOpenGL();
}