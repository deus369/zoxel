#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// #define DEVBUILD
// first, get working on pc
//  then, move texture updating to the entity system
// texture issues
//  https://www.reddit.com/r/opengl/comments/ydsqkn/textured_square_works_on_pinephone_pro_but_not_pc/
//  https://github.com/edo9300/edopro/issues/151
//! Creates materials for Textured and Default 2D Shaders.
void CreateTexturedMesh();
const char *playerCharacterTextureName = "Resources/Textures/Test.png";
const bool disableTextureLoaded = false;
float3 backgroundColor = { 0.2, 0.2, 0.5 };
int textureType = GL_NEAREST; // GL_LINEAR
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
// extern const char *outputTextureName;
GLuint tex_sampler_loc;
GLuint gl_view_matrix2;
GLuint gl_positionX2;
GLuint gl_positionY2;
GLuint gl_angle2;
GLuint gl_scale2;
GLuint gl_brightness2;
GLuint squareTexturedModelVertices;
GLuint squareTexturedModelUVs;
GLuint squareTexturedModelIndicies;
GLuint textureID;
GLint attribVertexPosition;
GLint attribVertexTexCoord;
// const char *outputTextureName = "Resources/Textures/Test.png";

void InitializeTexturedMesh(GLuint material)
{
    // get indexes
    attribVertexPosition = glGetAttribLocation(material, "vertexPosition");
    attribVertexTexCoord = glGetAttribLocation(material, "vertexUV");
    tex_sampler_loc = glGetUniformLocation(material, "tex");
    gl_view_matrix2 = glGetUniformLocation(material, "viewMatrix");
    gl_positionX2 = glGetUniformLocation(material, "positionX");
    gl_positionY2 = glGetUniformLocation(material, "positionY");
    gl_angle2 = glGetUniformLocation(material, "angle");
    gl_scale2 = glGetUniformLocation(material, "scale");
    gl_brightness2 = glGetUniformLocation(material, "brightness");
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
    int colorMode = GL_RGB;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureType);
    // push data to gpu
    SDL_Surface* surface = IMG_Load(playerCharacterTextureName);
    if (surface != NULL && !disableTextureLoaded)
    {
        if(surface->format->BytesPerPixel == 4)
        {
            colorMode = GL_RGBA;
        }
        printf("Loading Texture: [%s] of Size: %ix%i - BytesPerPixel: %i\n",
            playerCharacterTextureName, surface->w, surface->h, surface->format->BytesPerPixel);
        glTexImage2D(GL_TEXTURE_2D, 0, colorMode, surface->w, surface->h, 0, colorMode, GL_UNSIGNED_BYTE, surface->pixels);
#ifdef DEVBUILD
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            printf("GL HAD ERROR with glTexImage2D: %i\n", err);
        }
#endif
    }
    else
    {
        printf("IMG_Load failed: %s\n", IMG_GetError());    // SDL_GetError
        // 2 x 2 x 3 = 12 bytes
        // printf("Loading Texture Test - 4 pixels.\n");
        unsigned char pixels[12] = { 0,0,0, 55,55,55, 125,125,125, 200,200,200 };
        glTexImage2D(GL_TEXTURE_2D, 0, colorMode, 2, 2, 0, colorMode, GL_UNSIGNED_BYTE, pixels);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_FreeSurface(surface);
#ifdef DEVBUILD
    GLenum err7 = glGetError();
    if (err7 != GL_NO_ERROR)
    {
        printf("GL HAD ERROR with end of InitializeTexturedMesh: %i\n", err7);
    }
#endif
}

void RenderEntityMaterial2D(const float4x4 viewMatrix, GLint entityMaterial, float2 position, float angle, float scale, float brightness)
{
    // Error 0x500/1280 means GL_INVALID_ENUM
#ifdef DEVBUILD
    if (!glIsProgram(entityMaterial))
    {
        printf("GL Is not program %i\n", entityMaterial);
        return;
    }
#endif
    glUseProgram(entityMaterial);   // invalid operation
    // Texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    // Bind Buffer + Indicies
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareTexturedModelIndicies);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, squareTexturedModelVertices);            // for vertex buffer data
    // enable the things
    glEnableVertexAttribArray(attribVertexPosition);
    glVertexAttribPointer(attribVertexPosition, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(0 * sizeof(float)));
    glEnableVertexAttribArray(attribVertexTexCoord);
    glVertexAttribPointer(attribVertexTexCoord, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(2 * sizeof(float)));
    // Properties
    glUniformMatrix4fv(gl_view_matrix2, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
    glUniform1f(gl_positionX2, position.x);
    glUniform1f(gl_positionY2, position.y);
    glUniform1f(gl_angle2, angle);
    glUniform1f(gl_scale2, scale);
    glUniform1f(gl_brightness2, brightness);
    // finally draw it
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    // Disables
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(attribVertexPosition);
    glDisableVertexAttribArray(attribVertexTexCoord);
    glUseProgram(0);
#ifdef DEVBUILD
    GLenum err66 = glGetError();
    if (err66 != GL_NO_ERROR)
    {
        printf("GL HAD ERROR with End of RenderEntityMaterial2D: %i\n", err66);
        return;
    }
#endif
}

void InitializeMesh(GLuint material)
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
#ifdef DEVBUILD
    GLenum err7 = glGetError();
    if (err7 != GL_NO_ERROR)
    {
        printf("GL HAD ERROR with end of InitializeMesh: %i\n", err7);
    }
#endif
}

void OpenGLClear()
{
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);       // Clears the buffer ?
    // glDisable(GL_DEPTH_TEST);
}

void OpenGLBeginInstancing(const float4x4 viewMatrix)
{
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

void OpenGLEndInstancing()
{
    glDisableVertexAttribArray(attribVertexPosition);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
#ifdef DEVBUILD
    GLenum err7 = glGetError();
    if (err7 != GL_NO_ERROR)
    {
        printf("GL HAD ERROR with end of OpenGLEndInstancing: %i\n", err7);
    }
#endif
}

//! Cleanup OpenGL resources
void EndAppOpenGL()
{
    glDeleteBuffers(1, &squareModel);
    glDeleteBuffers(1, &squareModelIndicies);
    glDeleteBuffers(1, &squareTexturedModelVertices);
    glDeleteBuffers(1, &squareTexturedModelUVs);
    glDeleteBuffers(1, &squareTexturedModelIndicies);
    glDeleteTextures(1, &textureID);
    glDeleteProgram(material);
    glDeleteProgram(texturedMaterial);
#ifdef DEVBUILD
    GLenum err7 = glGetError();
    if (err7 != GL_NO_ERROR)
    {
        printf("GL HAD ERROR with end of EndAppOpenGL: %i\n", err7);
    }
#endif
}

/*
Multiple Textures:

    https://learnopengl.com/Getting-started/Textures

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

*/
    // glActiveTexture(GL_TEXTURE0);
    // glUniform1i(tex_sampler_loc, 0);
    // glEnableTexture(tex_sampler_loc);
    // glActiveTexture(GL_TEXTURE0);
    // glUniform1i(tex_sampler_loc, 0);