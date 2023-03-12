// #define zoxel_catch_opengl_errors
// first, get working on pc
//  then, move texture updating to the entity system
// texture issues
//  https://www.reddit.com/r/opengl/comments/ydsqkn/textured_square_works_on_pinephone_pro_but_not_pc/
//  https://github.com/edo9300/edopro/issues/151
// float3 backgroundColor = { 16.0f / 255.0f, 24.0f / 255.0f, 32.0f / 255.0f };
// float3 backgroundColor = { 99.0f / 255.0f, 190.0f / 255.0f, 191.0f / 255.0f };
// float3 backgroundColor = { 9.0f / 255.0f, 70.0f / 255.0f, 75.0f / 255.0f };//
float3 backgroundColor = { 2.0f / 255.0f, 16.0f / 255.0f, 24.0f / 255.0f };//

void print_opengl()
{
    #ifdef zoxel_debug_opengl
        zoxel_log(" > opengl\n");
        zoxel_log("     + vendor:   %s\n", glGetString(GL_VENDOR));
        zoxel_log("     + renderer: %s\n", glGetString(GL_RENDERER));
        zoxel_log("     + version:  %s\n", glGetString(GL_VERSION));
        zoxel_log("     + glsl version:    %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    #endif
}

void opengl_clear()
{
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       // Clears the buffer ?
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
    #ifdef zoxel_catch_opengl_errors
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            zoxel_log("GL ERROR with spawn_gpu_mesh_buffers [%i] - glGenBuffers\n",
                (int) err);
        }
    #endif
    return mesh;
}

GLuint spawn_gpu_uvs_buffers()
{
    GLuint uvs;
    glGenBuffers(1, &uvs);
    return uvs;
}

unsigned char opengl_set_material(GLuint material)
{
    if (material == 0)
    {
        // printf("render_entity_material2D material is 0.\n");
        return 0;
    }
    glUseProgram(material);
    #ifdef zoxel_catch_opengl_errors
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            zoxel_log("GL ERROR with opengl_set_material [%i]\n", material);
            return 0;
        }
    #endif
    return 1;
}

void opengl_set_mesh(GLuint2 mesh)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);            // for vertex coordinates
}

void opengl_set_mesh_indicies(GLuint indices_buffer)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);    // for indices
}

void opengl_set_mesh_uvs(GLuint uv_buffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);         // for UV coordinates
}

void opengl_unset_mesh()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void opengl_draw_triangles(int indicies_length)
{
    glDrawElements(GL_TRIANGLES, indicies_length, GL_UNSIGNED_INT, NULL);
    #ifdef zoxel_catch_opengl_errors
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            zoxel_log("GL ERROR with opengl_draw_triangles.\n");
        }
    #endif
}

void opengl_disable_opengl_program()
{
    glUseProgram(0);
}

void opengl_set_camera_view_matrix(GLuint material, const float4x4 view_matrix)
{
    GLuint view_matrix_location = glGetUniformLocation(material, "viewMatrix");
    // glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, (const GLfloat*) ((float*) &view_matrix));
    glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, (float*) &view_matrix);
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