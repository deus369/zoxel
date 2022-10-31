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
//! Mesh A - Buffers
const char* basicRender2DVertFilepath = "Resources/Shaders/2D/BasicRender2D.vert";
const char* basicRender2DFragFilepath = "Resources/Shaders/2D/BasicRender2D.frag";
GLuint square2DMaterial;
Material2D material2D;
GLuint squareModelIndicies;
GLuint squareModelVertices;

void DisposeInstance2DMaterial()
{
    glDeleteBuffers(1, &squareModelIndicies);
    glDeleteBuffers(1, &squareModelVertices);
    glDeleteProgram(square2DMaterial);
}

void InitializeMaterialPropertiesA(GLuint material)
{
    material2D.view_matrix = glGetUniformLocation(material, "viewMatrix");
    material2D.angle = glGetUniformLocation(material, "angle");
    material2D.scale = glGetUniformLocation(material, "scale");
    material2D.brightness = glGetUniformLocation(material, "brightness");
    material2D.positionX = glGetUniformLocation(material, "positionX");
    material2D.positionY = glGetUniformLocation(material, "positionY");
    material2D.vertexPosition = glGetAttribLocation(material, "vertexPosition");
}

void InitializeMesh(GLuint material)
{
    // gen buffers
    glGenBuffers(1, &squareModelIndicies);
    glGenBuffers(1, &squareModelVertices);
    // set buffer data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareModelIndicies);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareTexturedIndicies), squareTexturedIndicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, squareModelVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVerts), squareVerts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(material2D.vertexPosition);
    glVertexAttribPointer(material2D.vertexPosition, 2, GL_FLOAT, GL_FALSE, 8, 0);
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

int LoadInstance2DMaterial()
{
    square2DMaterial = LoadMaterial(basicRender2DVertFilepath, basicRender2DFragFilepath);
    if (square2DMaterial == 0)
    {
        printf("Error loading Shaders for square2DMaterial.\n");
        return -1;
    }
    InitializeMaterialPropertiesA(square2DMaterial);
    InitializeMesh(square2DMaterial);
    return 0;
}

void OpenGLBeginInstancing(const float4x4 viewMatrix)
{
    //! This sets the materials actually, would be best to group entities per material here?
    glUseProgram(square2DMaterial);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareModelIndicies);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, squareModelVertices);            // for vertex coordinates
    glUniformMatrix4fv(material2D.view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
}

// does this per material!
void RenderEntity2D(float2 position, float angle, float scale, float brightness)
{
    // set variables, can this be done using a filtered / system ?
    glUniform1f(material2D.positionX, position.x);
    glUniform1f(material2D.positionY, position.y);
    glUniform1f(material2D.scale, scale);
    glUniform1f(material2D.angle, angle);
    glUniform1f(material2D.brightness, brightness);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL); // &squareTexturedIndicies);
}

void OpenGLEndInstancing()
{
    glUseProgram(0);
#ifdef DEVBUILD
    GLenum err7 = glGetError();
    if (err7 != GL_NO_ERROR)
    {
        printf("GL HAD ERROR with end of OpenGLEndInstancing: %i\n", err7);
    }
#endif
}
    /*printf("Loading Shader Vert: %s\n", basicRender2DVertFilepath);
    GLuint vertShader;
    if (LoadShader(basicRender2DVertFilepath, GL_VERTEX_SHADER, &vertShader) != 0)
    {
        printf("Error loading Shader Vert.\n");
        return -1;
    }
    printf("Loading Shader Frag: %s\n", basicRender2DFragFilepath);
    GLuint fragShader;
    if (LoadShader(basicRender2DFragFilepath, GL_FRAGMENT_SHADER, &fragShader) != 0)
    {
        printf("Error loading Shader Frag.\n");
        return -1;
    }
    square2DMaterial = glCreateProgram();
    LinkShaderProgram(square2DMaterial, vertShader, fragShader);
    // Clean up shaders
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);*/