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
GLuint squareModelIndicies;
GLuint squareModelVertices;

void DisposeMesh()
{
    glDeleteBuffers(1, &squareModelIndicies);
    glDeleteBuffers(1, &squareModelVertices);
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
    glEnableVertexAttribArray(gl_vertexPositionA);
    glVertexAttribPointer(gl_vertexPositionA, 2, GL_FLOAT, GL_FALSE, 8, 0);
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

void OpenGLBeginInstancing(const float4x4 viewMatrix)
{
    //! This sets the materials actually, would be best to group entities per material here?
    glUseProgram(material);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareModelIndicies);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, squareModelVertices);            // for vertex coordinates
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