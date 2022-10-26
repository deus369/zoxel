#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

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
    // glEnable(GL_DEPTH_TEST);
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

// GluPerspective(fov, aspectRatio, 1.0f, 100.0f);
// glViewport(0, 0, (GLsizei) screenWidth, (GLsizei) screenHeight);
/*glMatrixMode( GL_PROJECTION );
glLoadIdentity();
// gluOrtho2D(-1.0 * aspectRatio, aspectRatio, -1.0, 1.0);
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();*/

// vert shader
// const GLchar *vertSource =
//     "#version 330\n"
//     "layout(location = 0) in vec2 point;\n"
//     "uniform float pointX;\n"
//     "uniform float pointY;\n"
//     "uniform float angle;\n"
//     "uniform float scale;\n"
//     "void main() {\n"
//     "    vec2 position2D = vec2(pointX, pointY);\n"
//     "    mat2 rotate = mat2(cos(angle), -sin(angle),\n"
//     "                       sin(angle), cos(angle));\n"
//     "    gl_Position = vec4(position2D + (rotate * point) * scale, 0.0, 1.0);\n"
//     "}\n";
// // fragment shader
// const GLchar *fragSource =
//     "#version 330\n"
//     "uniform float brightness;\n"
//     "out vec4 color;\n"
//     "void main() {\n"
//     "    color = vec4(0.1, 0.65, 0.15, 0) * brightness;\n"
//     "}\n";

    /*GLchar* buffer;
    buffer = (GLchar*) malloc((bufferSize+1) * sizeof(GLchar));
    if (buffer == NULL)
    {
        printf("Can't allocate Shader buffer. \n");
        return -1;
    }
    LoadShaderFile(filepath, buffer, bufferSize);*/
    // GetFileSize(filepath, &bufferSize);

/*int CompileShader(const char* buffer, GLenum shaderType, GLuint* shader2)
{
    // GLint bufferSize = (GLint) GetStringSize(buffer); // (GLchar) 
    // printf("Compiling Shader: %i\n", bufferSize);
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const GLchar**) &buffer, NULL); // (const GLchar**) &bufferSize);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        GLint info_log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar* info_log = malloc(info_log_length);
        glGetShaderInfoLog(shader, info_log_length, NULL, info_log);
        fprintf(stderr, "Failed to compile shader:\n%s\n", info_log);
        free(info_log);
        return -1;
    }
    // free(buffer);
    *shader2 = shader;
    // printf("Success Loading Shader Source [%i] \n", (int) bufferSize);
    return 0;
}*/

/*int GetFileSize(const char* filepath, int32_t* file_size)
{
    FILE* file = fopen(filepath, "rb");
    if (file == NULL)
    {
        printf("Can't open shader file: %s \n", filepath);
        return -1;
    }
    fseek(file, 0L, SEEK_END);
    *file_size = ftell(file);
    fclose(file);
    return 0;
}

int LoadShaderFile(const char* filepath, GLchar* buffer, GLint size)
{
    FILE* file = fopen(filepath, "rb");
    if (file == NULL)
    {
        printf("Can't open shader file: %s \n", filepath);
        return -1;
    }
    fread(buffer, size, 1, file);
    buffer[size] = 0;
    fclose(file);
    return 0;
}*/
    // char *fragFilename = malloc(mallocSize);
        // strcpy(fragFilename, shaderFilepath);
        // strcat(fragFilename, fragExtension);

// #define INCBIN_PREFIX
// #include "../incbin/incbin.h"       // Using https://github.com/graphitemaster/incbin/
// #include "opengl.h"
// #include "../../Core/Core/Core.h"
// Use a shaders folder
// const char *shaderFilepath = "BasicRender2D";
// INCBIN(basicRender2DVert, "../../../Resources/Shaders/BasicRender2D.vert");
// INCBIN(basicRender2DVert, "../../../Resources/Shaders/BasicRender2D.vert");
// Fuck this isn't going to work on other machines..
// Convert shader files to .c files, add on \n's or something.. create a header file generated with includes
// Get filepath of game, add that on!
// version 330
// layout(location = 0)
    // PrintOpenGL();
    // printf("basicRender2DVertEnd: %i\n", GetStringSize(basicRender2DVertEnd));
    /*if (CompileShader(basicRender2DVertEnd, GL_VERTEX_SHADER, &vertShader) != 0)
    {
        printf("Error loading Shader Vert");
    }*/
    // glPushMatrix();
    // glMultMatrixf(mat44);
    // glLoadMatrixf(mat44);
    // glTranslatef(positionX, positionY, 0);
    // glRotatef( 0, 0.0, 0.0, 1.0 );
    // glScalef(scale, scale, scale);
    // glTranslatef(positionX, positionY, 0);
    // glPopMatrix();

    // glBegin(GL_TRIANGLES);
    // glColor3f(0.1, 0.2, 0.3);
    // glVertex3f(0, 0, 0);
    // glVertex3f(1, 0, 0);
    // glVertex3f(0, 1, 0);
    // glEnd();

    // You should probably use CSurface::OnLoad ... ;)
    //-- and make sure the Surface pointer is good!
    /*GLuint bufferIndexes[2];
    GLuint* pointer = bufferIndexes;
    glGenBuffers(2, pointer);
    // glGenBuffers(1, &squareTexturedModel);

    int vertexBufferId = bufferIndexes[0];
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVerts), squareVerts, GL_STATIC_DRAW);
    int uvID = bufferIndexes[1];
    glBindBuffer(GL_ARRAY_BUFFER, uvID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareUVs), squareUVs, GL_STATIC_DRAW);
    // 1
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, uvID);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);*/

    //glBindBuffer(GL_ARRAY_BUFFER, squareTexturedModel);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(squareTexturedVerts), squareTexturedVerts, GL_STATIC_DRAW);
    // glEnableVertexAttribArray((GLuint)0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), &squareTexturedVerts);  // vertices
    // glEnableVertexAttribArray((GLuint)1);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), &squareTexturedVerts + 2);        // uv
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    //  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0); // (void*)(4 * sizeof(float)));

    
    /*glBindBuffer(GL_ARRAY_BUFFER, squareTexturedModelVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVerts2), squareVerts2, GL_STATIC_DRAW); 
    glVertexAttribPointer(attribVertexPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(attribVertexPosition);
    glBindBuffer(GL_ARRAY_BUFFER, 0);*/
    // uvs
    /*glBindBuffer(GL_ARRAY_BUFFER, squareTexturedModelUVs);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareUVs), squareUVs, GL_STATIC_DRAW);
    glVertexAttribPointer(attribVertexTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(attribVertexTexCoord);
    glBindBuffer(GL_ARRAY_BUFFER, 0);*/

    // (GL_ARRAY_BUFFER, squareTexturedModel); // bind VBO in order to use
    //glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, squareVerts);                  // copy verts at offset 0
    //glBufferSubData(GL_ARRAY_BUFFER, vSize, uvSize, squareUVs);             // copy uvs after verts
    // reset

    // printf("squareTexturedModelIndicies %i\n", squareTexturedModelIndicies);
    // printf("squareTexturedModelVertices %i\n", squareTexturedModelVertices);
    // printf("squareTexturedModelUVs %i\n", squareTexturedModelUVs);
    //int sauwaw = sizeof(squareTexturedIndicies);
    //printf("sizeof(squareTexturedIndicies) %i\n", sauwaw);


    //glEnableVertexAttribArray(attribVertex);          // activate vertex position array
    //glEnableVertexAttribArray(attribTexCoord);        // activate texture coords array
    //glVertexAttribPointer(attribVertex, 2, GL_FLOAT, false, stride, 0);
    //glVertexAttribPointer(attribTexCoord, 2, GL_FLOAT, false, stride, 2);
    // glBindBuffer(GL_ARRAY_BUFFER, squareTexturedModel);            // for vertex coordinates
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareTexturedModel2);    // for indices
    // glBindVertexArray(squareTexturedVerts);
    // glDrawArrays(GL_TRIANGLE_STRIP, 0, count);
    // glVertexPointer(4, GL_FLOAT, 0, &squareTexturedVerts);

    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(squareVerts) / sizeof(*squareVerts) / 2);
    /*glBegin(GL_QUADS);
        glTexCoord2f(squareUVs[0], squareUVs[1]); glVertex3f(squareVerts[0], squareVerts[1], 0);
        glTexCoord2f(squareUVs[0], squareUVs[1]); glVertex3f(squareVerts[2], squareVerts[3], 0);
        glTexCoord2f(squareUVs[0], squareUVs[1]); glVertex3f(squareVerts[4], squareVerts[5], 0);
        glTexCoord2f(squareUVs[0], squareUVs[1]); glVertex3f(squareVerts[6], squareVerts[7], 0);
    glEnd();*/
    /*glBindBuffer(GL_ARRAY_BUFFER, squareTexturedModelUVs);
    glEnableVertexAttribArray(attribVertexTexCoord);*/
    /*glBindBuffer(GL_ARRAY_BUFFER, squareTexturedModelVertices);
    glEnableVertexAttribArray(attribVertexTexCoord);*/
    // glEnableVertexAttribArray(attribVertexPosition);
    // glVertexAttribPointer(attribVertexPosition, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)(0)); // 0);
    // glVertexAttribPointer(attribVertexTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(squareVerts));
    // glActiveTexture(GL_TEXTURE0);