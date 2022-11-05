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
const char* basicRender2DVertFilepath = "resources/shaders/2D/BasicRender2D.vert";
const char* basicRender2DFragFilepath = "resources/shaders/2D/BasicRender2D.frag";
GLuint2 instanceShader2D;
GLuint square2DMaterial;
Material2D material2D;
GLuint2 squareMesh;

void DisposeInstance2DMaterial()
{
    glDeleteShader(instanceShader2D.x);
    glDeleteShader(instanceShader2D.y);
    glDeleteBuffers(1, &squareMesh.x);
    glDeleteBuffers(1, &squareMesh.y);
    glDeleteProgram(square2DMaterial);
}

void InitializeMesh(GLuint material)
{
    // gen buffers
    glGenBuffers(1, &squareMesh.x);
    glGenBuffers(1, &squareMesh.y);
    // set buffer data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareMesh.x);
    glBindBuffer(GL_ARRAY_BUFFER, squareMesh.y);
    // printf("A Binding Data %i %i\n", sizeof(squareIndicies), sizeof(squareVerts));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndicies), squareIndicies, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVerts), squareVerts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(material2D.vertexPosition);
    glVertexAttribPointer(material2D.vertexPosition, 2, GL_FLOAT, GL_FALSE, 8, 0);
    // printf("Setting Vertex Attribute Pointer for [%ix%i] Mesh.\n", squareMesh.x, squareMesh.y);
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
    /*for (int j = 0; j < sizeof(squareIndicies) / 4; j++)
    {
        printf("    - Index [%i] is [%i]\n", j, squareIndicies[j]);
    }
    for (int j = 0; j < sizeof(squareVerts) / 4; j++)
    {
        printf("    - Vertex [%i] is [%f]\n", j, squareVerts[j]);
    }*/
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

int LoadInstance2DMaterial()
{
    square2DMaterial = load_gpu_shader(&instanceShader2D, basicRender2DVertFilepath, basicRender2DFragFilepath);
    if (square2DMaterial == 0)
    {
        printf("Error loading shaders for square2DMaterial.\n");
        return -1;
    }
    InitializeMaterialPropertiesA(square2DMaterial);
    InitializeMesh(square2DMaterial);
    return 0;
}

void OpenGLBeginInstancing(const float4x4 viewMatrix)
{
    if (square2DMaterial == 0)
    {
        printf("OpenGLBeginInstancing square2DMaterial is 0.\n");
        return;
    }
    //! This sets the materials actually, would be best to group entities per material here?
    glUseProgram(square2DMaterial);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareMesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, squareMesh.y);            // for vertex coordinates
    glEnableVertexAttribArray(material2D.vertexPosition);
    glVertexAttribPointer(material2D.vertexPosition, 2, GL_FLOAT, GL_FALSE, 8, 0);  // 2 * 4
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
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL); // &squareIndicies);
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