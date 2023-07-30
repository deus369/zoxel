const float shader_depth_multiplier = 0.001f; // 0.0001f;
const unsigned char disableTextureLoaded = 0;
int textureType = GL_NEAREST; // GL_LINEAR
uint2 shader2D_textured;
uint material2D_textured;
uint2 squareTexturedMesh;
uint squareTexturedModelUVs;

void dispose_shader2D_textured() {
    glDeleteBuffers(1, &squareTexturedMesh.x);
    glDeleteBuffers(1, &squareTexturedMesh.y);
    glDeleteBuffers(1, &squareTexturedModelUVs);
    // glDeleteTextures(1, &textureID);
    glDeleteShader(shader2D_textured.x);
    glDeleteShader(shader2D_textured.y);
    glDeleteProgram(material2D_textured);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("dispose_shader2D_textured");
    #endif
}

void initialize_texture_mesh(uint material) {
    MaterialTextured2D materialTextured2D = initialize_material2D_textured(material);
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
    // printf("Setting Vertex Attribute Pointer for [%ix%i] Mesh.\n", squareTexturedMesh.x, squareTexturedMesh.y);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("initialize_texture_mesh");
    #endif
}

int load_shader2D_textured() {
    shader2D_textured = spawn_gpu_shader_inline(shader2D_textured_vert_buffer, shader2D_textured_frag_buffer);
    material2D_textured = spawn_gpu_material_program((const uint2) { shader2D_textured.x, shader2D_textured.y });
    // material2D_textured = load_gpu_shader(&shader2D_textured, shader2D_textured_filepath_vert, shader2D_textured_filepath_frag);
    initialize_texture_mesh(material2D_textured);
    return 0;
}

uint spawn_gpu_texture_buffers() {
    uint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureType);
    glBindTexture(GL_TEXTURE_2D, 0);
    return textureID;
}

void render_entity_material2D(const float4x4 viewMatrix, uint material, uint texture, float2 position, float angle, float scale, float brightness) {
    if (material == 0) {
        // printf("render_entity_material2D material is 0.\n");
        return;
    }
    MaterialTextured2D materialTextured2D = initialize_material2D_textured(material);
    glUseProgram(material);
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
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glUseProgram(0);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("render_entity_material2D");
    #endif
}

void render_entity_material2D_and_mesh(const float4x4 viewMatrix, uint2 mesh, uint material, uint texture, float2 position, float angle, float scale, float brightness, unsigned char layer) {
    if (material == 0) {
        // printf("render_entity_material2D material is 0.\n");
        return;
    }
    MaterialTextured2D materialTextured2D = initialize_material2D_textured(material);
    glUseProgram(material);   // invalid operation
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS);
    // glEnable(GL_ALPHA_TEST);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);            // for vertex coordinates
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnableVertexAttribArray(materialTextured2D.vertexPosition);
    glEnableVertexAttribArray(materialTextured2D.vertexUV);
    glVertexAttribPointer(materialTextured2D.vertexPosition, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(0 * sizeof(float)));
    glVertexAttribPointer(materialTextured2D.vertexUV, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(2 * sizeof(float)));
    glUniformMatrix4fv(materialTextured2D.view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
    glUniform1f(materialTextured2D.positionX, position.x);
    glUniform1f(materialTextured2D.positionY, position.y);
    glUniform1f(materialTextured2D.positionZ, ((int) layer) * shader_depth_multiplier);
    glUniform1f(materialTextured2D.angle, angle);
    glUniform1f(materialTextured2D.scale, scale);
    glUniform1f(materialTextured2D.brightness, brightness);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    // glBindTexture(GL_TEXTURE_2D, 0);
    // glDisable(GL_BLEND);
    // glUseProgram(0);
    // glDisable(GL_ALPHA_TEST);
    // glDisable(GL_DEPTH_TEST);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("render_entity_material2D_and_mesh");
    #endif
}

void render_entity_material2D_and_mesh2(const float4x4 viewMatrix, uint2 mesh, uint material, uint uvs_gpu_link, uint texture, float2 position, float angle, float scale, float brightness, unsigned char layer) {
    if (material == 0) {
        // printf("render_entity_material2D material is 0.\n");
        return;
    }
    MaterialTextured2D materialTextured2D = initialize_material2D_textured(material);
    glUseProgram(material);   // invalid operation
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS);
    // glEnable(GL_ALPHA_TEST);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);            // for vertex coordinates
    glEnableVertexAttribArray(materialTextured2D.vertexPosition);
    glVertexAttribPointer(materialTextured2D.vertexPosition, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(0 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, uvs_gpu_link);            // for vertex coordinates
    glEnableVertexAttribArray(materialTextured2D.vertexUV);
    glVertexAttribPointer(materialTextured2D.vertexUV, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(2 * sizeof(float)));
    glUniformMatrix4fv(materialTextured2D.view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
    glUniform1f(materialTextured2D.positionX, position.x);
    glUniform1f(materialTextured2D.positionY, position.y);
    glUniform1f(materialTextured2D.positionZ, ((int) layer) * shader_depth_multiplier);
    glUniform1f(materialTextured2D.angle, angle);
    glUniform1f(materialTextured2D.scale, scale);
    glUniform1f(materialTextured2D.brightness, brightness);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    // glBindTexture(GL_TEXTURE_2D, 0);
    // glDisable(GL_BLEND);
    // glUseProgram(0);
    // glDisable(GL_ALPHA_TEST);
    // glDisable(GL_DEPTH_TEST);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("render_entity_material2D_and_mesh");
    #endif
}

void opengl_set_buffer_attributes2D(uint vertex_buffer, uint uv_buffer, MaterialTextured2D *attributes) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glEnableVertexAttribArray(attributes->vertexPosition);
    glVertexAttribPointer(attributes->vertexPosition, 2, GL_FLOAT, GL_FALSE, 0, 0); // 12, 0);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glEnableVertexAttribArray(attributes->vertexUV);
    glVertexAttribPointer(attributes->vertexUV, 2, GL_FLOAT, GL_FALSE,  0, 0); // 8, 0);
}

/*void opengl_upload_shader2D_textured(uint2 mesh_buffer, uint uv_buffer, const int *indicies, int indicies_length, const float2 *verts, const float2 *uvs, int verts_length) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * sizeof(int), indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float2), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float2), uvs, GL_STATIC_DRAW);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}*/

void opengl_upload_shader2D_textured(uint2 mesh_buffer, uint material_buffer,
    const int *indicies, int indicies_length, const float2 *verts, const float2 *uvs, int verts_length) {
    MaterialTextured2D materialTextured2D = initialize_material2D_textured(material_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * 4, indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
    int float_per_data = 4;
    int floats_length = verts_length * float_per_data;
    float combined_verts[floats_length];
    for (int i = 0; i < verts_length; i++) {
        float2 vert = verts[i];
        float2 uv = uvs[i];
        combined_verts[i * float_per_data + 0] = vert.x;
        combined_verts[i * float_per_data + 1] = vert.y;
        combined_verts[i * float_per_data + 2] = uv.x;
        combined_verts[i * float_per_data + 3] = uv.y;
        // printf("[%i] uv: %fx%f\n", i, uv.x, uv.y);
    }
    glBufferData(GL_ARRAY_BUFFER, floats_length * 4, combined_verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(materialTextured2D.vertexPosition);
    glEnableVertexAttribArray(materialTextured2D.vertexUV);
    glVertexAttribPointer(materialTextured2D.vertexPosition, 2, GL_FLOAT, GL_FALSE, 4 * float_per_data, (GLvoid*)(0 * sizeof(float)));
    glVertexAttribPointer(materialTextured2D.vertexUV, 2, GL_FLOAT, GL_FALSE, 4 * float_per_data, (GLvoid*)(2 * sizeof(float)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // printf("Binding Data %i %i\n", indicies_length, verts_length);
}