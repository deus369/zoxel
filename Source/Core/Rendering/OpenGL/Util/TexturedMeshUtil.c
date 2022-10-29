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
// const char *playerCharacterTextureName = "Resources/Textures/Test.png";
const bool disableTextureLoaded = false;
int textureType = GL_NEAREST; // GL_LINEAR

//! \todo Move these references to Material
//! \todo Update texture based on Player Entity texture updateing

//! Mesh B - Buffers/Texture
GLuint squareTexturedModelIndicies;
GLuint squareTexturedModelVertices;
GLuint squareTexturedModelUVs;
GLuint textureID;

void DisposeTexturedMesh()
{
    glDeleteBuffers(1, &squareTexturedModelIndicies);
    glDeleteBuffers(1, &squareTexturedModelVertices);
    glDeleteBuffers(1, &squareTexturedModelUVs);
    glDeleteTextures(1, &textureID);
}

void InitializeTexturedMesh(GLuint material)
{
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
    glVertexAttribPointer(materialTextured2D.vertexPosition, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(0 * sizeof(float)));
    glVertexAttribPointer(materialTextured2D.vertexUV, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(2 * sizeof(float)));
    glEnableVertexAttribArray(materialTextured2D.vertexPosition);
    glEnableVertexAttribArray(materialTextured2D.vertexUV);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureType);
    glBindTexture(GL_TEXTURE_2D, 0);
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
    glUseProgram(entityMaterial);   // invalid operation
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    // Texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    // Bind Buffer + Indicies
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareTexturedModelIndicies);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, squareTexturedModelVertices);            // for vertex buffer data
    // Properties
    glUniformMatrix4fv(materialTextured2D.view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
    glUniform1f(materialTextured2D.positionX, position.x);
    glUniform1f(materialTextured2D.positionY, position.y);
    glUniform1f(materialTextured2D.angle, angle);
    glUniform1f(materialTextured2D.scale, scale);
    glUniform1f(materialTextured2D.brightness, brightness);
    // finally draw it
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    // Disable the things
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
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

    // Load texture from file and upload to gpu directlyy.
    // push data to gpu
    /*
    int colorMode = GL_RGB;
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
    SDL_FreeSurface(surface);
    */
   

/*
Multiple Textures:

    https://learnopengl.com/Getting-started/Textures

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

*/
    // glActiveTexture(GL_TEXTURE0);
    // glUniform1i(texture, 0);
    // glEnableTexture(texture);
    // glActiveTexture(GL_TEXTURE0);
    // glUniform1i(texture, 0);

/*
#ifdef DEVBUILD
    if (!glIsProgram(entityMaterial))
    {
        printf("GL Is not program %i\n", entityMaterial);
        return;
    }
#endif
*/
    // Error 0x500/1280 means GL_INVALID_ENUM