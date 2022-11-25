#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// #define zoxel_catch_opengl_errors
// first, get working on pc
//  then, move texture updating to the entity system
// texture issues
//  https://www.reddit.com/r/opengl/comments/ydsqkn/textured_square_works_on_pinephone_pro_but_not_pc/
//  https://github.com/edo9300/edopro/issues/151
// float3 backgroundColor = { 16.0f / 255.0f, 24.0f / 255.0f, 32.0f / 255.0f };
float3 backgroundColor = { 99.0f / 255.0f, 190.0f / 255.0f, 191.0f / 255.0f };

void opengl_clear()
{
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);       // Clears the buffer ?
    glClear(GL_DEPTH_BUFFER_BIT);       // Clears the buffer ?
    glEnable(GL_DEPTH_TEST);        // cull for 3D things
    glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK); // defaults to this
}

//! Spawns the buffers for a mesh indicies and verts on the gpu.
GLuint2 spawn_gpu_mesh_buffers()
{
    GLuint2 mesh;
    glGenBuffers(1, &mesh.x);
    glGenBuffers(1, &mesh.y);
    return mesh;
}

GLuint spawn_gpu_uvs_buffers()
{
    GLuint uvs;
    glGenBuffers(1, &uvs);
    return uvs;
}

bool opengl_set_material(GLuint material)
{
    if (material == 0)
    {
        // printf("render_entity_material2D material is 0.\n");
        return false;
    }
    glUseProgram(material);
    return true;
}

void opengl_set_mesh(GLuint2 mesh)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);            // for vertex coordinates
}

/*void opengl_set_uvs(GLuint uvs)
{
    glBindBuffer(GL_ARRAY_BUFFER, uvs);
}*/

void opengl_draw_triangles(int indicies_length)
{
    glDrawElements(GL_TRIANGLES, indicies_length, GL_UNSIGNED_INT, NULL);
}

void opengl_disable_opengl_program()
{
    glUseProgram(0);
}

/*
Multiple textures:

    https://learnopengl.com/Getting-started/textures

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
#ifdef zoxel_catch_opengl_errors
    if (!glIsProgram(entityMaterial))
    {
        printf("GL Is not program %i\n", entityMaterial);
        return;
    }
#endif
*/
    // Error 0x500/1280 means GL_INVALID_ENUM