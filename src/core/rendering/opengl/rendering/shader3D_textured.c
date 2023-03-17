// Shader3D Textured
GLuint2 shader3D_textured;
// const char* shader3D_textured_filepath_vert = resources_folder_name"shaders/3D/shader3D_textured.vert";
// const char* shader3D_textured_filepath_frag = resources_folder_name"shaders/3D/shader3D_textured.frag";
//! inline shaders incase the shader files don't exist.
const GLchar* shader3D_textured_vert_buffer = "\
#version 300 es\n\
in highp vec3 vertexPosition;\
in highp vec2 vertexUV;\
uniform highp mat4 view_matrix;\
uniform highp vec3 position;\
uniform highp vec4 rotation;\
uniform highp float scale;\
out highp vec2 uv;\
out highp float fogFactor;\
\
vec3 float4_rotate_float3(vec4 rotation, vec3 value)\
{\
    vec3 rotationXYZ = rotation.xyz;\
    vec3 t = cross(rotationXYZ, value) * 2.0f;\
    vec3 crossB = cross(rotationXYZ, t);\
    vec3 scaledT = t * rotation.w;\
    return value + scaledT + crossB;\
}\
\
void main()\
{\
    gl_Position = view_matrix * vec4(position + float4_rotate_float3(rotation, vertexPosition * scale), 1.0);\
    uv = vertexUV;\
    fogFactor = (view_matrix * vec4(position + float4_rotate_float3(rotation, vertexPosition * scale), 1.0)).z;\
}\
";
const GLchar* shader3D_textured_frag_buffer = "\
#version 300 es\n\
uniform highp float brightness;\
uniform sampler2D tex;\
in highp vec2 uv;\
in highp float fogFactor;\
out highp vec4 color; \
 \
void main() \
{ \
    color = texture(tex, uv) * brightness; \
    highp vec4 backgroundColor = vec4(2.0f / 255.0f, 16.0f / 255.0f, 24.0f / 255.0f, 1);\
    highp float fog_density = 0.012;\
    highp float fogBlend = 1.0 - exp2(-fog_density * fog_density * fogFactor * fogFactor);\
    color = mix(color, backgroundColor, fogBlend);\
} \
";

void dispose_shader3D_textured() {
    glDeleteShader(shader3D_textured.x);
    glDeleteShader(shader3D_textured.y);
}

int load_shader3D_textured() {
    // shader3D_textured = spawn_gpu_shader(shader3D_textured_filepath_vert, shader3D_textured_filepath_frag);
    shader3D_textured = spawn_gpu_shader_inline(shader3D_textured_vert_buffer, shader3D_textured_frag_buffer);
    GLuint material = spawn_gpu_material_program(shader3D_textured);
    shader_attributes_material_textured3D = (Material3DTextured) { 
        glGetAttribLocation(material, "vertexPosition"),
        glGetAttribLocation(material, "vertexUV"),
        glGetUniformLocation(material, "view_matrix"),
        glGetUniformLocation(material, "position"),
        glGetUniformLocation(material, "rotation"),
        glGetUniformLocation(material, "scale"),
        glGetUniformLocation(material, "brightness"),
        glGetUniformLocation(material, "tex")
    };
    zoxel_log(" + vertexPosition location: %i\n", shader_attributes_material_textured3D.vertexPosition);
    zoxel_log(" + vertexUV location: %i\n", shader_attributes_material_textured3D.vertexUV);
    zoxel_log(" + view_matrix location: %i\n", shader_attributes_material_textured3D.view_matrix);
    zoxel_log(" + texture location: %i\n", shader_attributes_material_textured3D.texture);
    glDeleteProgram(material);
    return 0;
}

void opengl_set_texture_only(GLuint texture_buffer) {
    glBindTexture(GL_TEXTURE_2D, texture_buffer);
}

void opengl_set_texture(GLuint texture_buffer, unsigned char isBlend) {
    if (isBlend) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    } else {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_BLEND);
    }
    glBindTexture(GL_TEXTURE_2D, texture_buffer);
}

void opengl_disable_texture(unsigned char isBlend) {
    if (isBlend) {
        glDisable(GL_BLEND);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void opengl_set_buffer_attributes(GLuint vertex_buffer, GLuint uv_buffer, Material3DTextured *attributes) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glEnableVertexAttribArray(attributes->vertexPosition);
    glVertexAttribPointer(attributes->vertexPosition, 3, GL_FLOAT, GL_FALSE, 12, 0);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glEnableVertexAttribArray(attributes->vertexUV);
    glVertexAttribPointer(attributes->vertexUV, 2, GL_FLOAT, GL_FALSE, 8, 0);
}

void opengl_set_material3D_uvs_properties(float4 rotation, float scale, float brightness, Material3DTextured *attributes) {
    // glUniform3f(materialTextured3D->position, position.x, position.y, position.z);
    glUniform4f(attributes->rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    glUniform1f(attributes->scale, scale);
    glUniform1f(attributes->brightness, brightness);
}

void opengl_set_material3D_uvs_position(float3 position, Material3DTextured *attributes) {
    glUniform3f(attributes->position, position.x, position.y, position.z);
}

void opengl_shader3D_textured_set_camera_view_matrix(const float4x4 view_matrix, Material3DTextured *attributes) {
    glUniformMatrix4fv(attributes->view_matrix, 1, GL_FALSE, (float*) &view_matrix);
}

// printf("Rendering Cube [%ix%i]\n", mesh.x, mesh.y);
// printf("    - Rendering Cube [%ix%i]\n", squareTexturedMesh.x, squareTexturedMesh.y);
// glEnableVertexAttribArray(materialTextured3D.vertexPosition);
// glVertexAttribPointer(materialTextured3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 12, 0); // 4 * 3

void opengl_upload_shader3D_textured(GLuint2 mesh_buffer, GLuint uv_buffer, GLuint material_buffer,
    const int *indicies, int indicies_length, const float3 *verts, int verts_length, const float2 *uvs) {
    tri_count += indicies_length / 3;
    // Bind the index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * sizeof(int), indicies, GL_STATIC_DRAW);
    // Bind the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float3), verts, GL_STATIC_DRAW);
    // Bind the UV buffer
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float2), uvs, GL_STATIC_DRAW);
    // Set the vertex attribute pointers
    glVertexAttribPointer(shader_attributes_material_textured3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(shader_attributes_material_textured3D.vertexUV, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(float3) * verts_length));
    // Enable the vertex attribute arrays
    glEnableVertexAttribArray(shader_attributes_material_textured3D.vertexPosition);
    glEnableVertexAttribArray(shader_attributes_material_textured3D.vertexUV);
    // Unbind the buffers
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/*
glEnableVertexAttribArray(materialTextured3D.vertexPosition);
glEnableVertexAttribArray(materialTextured3D.vertexUV);
glVertexAttribPointer(materialTextured3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 20, 0);
glVertexAttribPointer(materialTextured3D.vertexUV, 2, GL_FLOAT, GL_FALSE, 20, (GLvoid*)(12));*/

/*void opengl_upload_shader3D_textured(
    GLuint2 mesh_buffer, GLuint material_buffer,
    const int *indicies, int indicies_length,
    const float3 *verts, int verts_length,
    const float2 *uvs, int uvs_length)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * 4, indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
    int float_per_data = 5;
    int floats_length = verts_length * float_per_data;
    float combined_verts[floats_length];
    for (int i = 0; i < verts_length; i++)
    {
        float3 vert = verts[i];
        float2 uv = uvs[i];
        combined_verts[i * float_per_data + 0] = vert.x;
        combined_verts[i * float_per_data + 1] = vert.y;
        combined_verts[i * float_per_data + 2] = vert.z;
        combined_verts[i * float_per_data + 3] = uv.x;
        combined_verts[i * float_per_data + 4] = uv.y;
    }
    glBufferData(GL_ARRAY_BUFFER, floats_length * 4, combined_verts, GL_STATIC_DRAW);
    
    glVertexAttribPointer(material3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 4 * float_per_data, (GLvoid*)(0 * sizeof(float)));
    glVertexAttribPointer(material3D.vertexUV, 2, GL_FLOAT, GL_FALSE, 4 * float_per_data, (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(material3D.vertexPosition);
    glEnableVertexAttribArray(material3D.vertexUV);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}*/

// printf("Binding Data %i %i\n", indicies_length, verts_length);

/*glBufferData(GL_ARRAY_BUFFER, verts_length * 3, verts, GL_STATIC_DRAW);
// uvs - combine with verts... this won't work?
glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
glEnableVertexAttribArray(material3D.vertexUV);
glVertexAttribPointer(material3D.vertexUV, 2, GL_FLOAT, GL_FALSE, 8, 0);*/
// glVertexAttribPointer(material3D.vertexUV, 2, GL_FLOAT, GL_FALSE, 8, (GLvoid*)(3 * sizeof(float)));
// glBufferData(GL_ARRAY_BUFFER, uvs_length * 4, uvs, GL_STATIC_DRAW);
// printf("Setting Vertex Attribute Pointer for [%ix%i] Mesh.\n", mesh.x, mesh.y);
// disable bindings

// glEnableVertexAttribArray(material3D.vertexPosition);
// glVertexAttribPointer(material3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 12, 0);
//! This recreates vertex data during upload
//! \todo Can I upload a non combined one? This isn't efficient.
// int proper_verts_length = verts_length; //  / 3);
// \todo Even this size of array crashed web build! stackSize > 655360
/*if (floats_length > 15536) // 6)
{
    printf("floats_length greater than 65536 [%i]\n", floats_length);
}*/

//  
// highp float fogFactor = fogDensity * (gl_FragCoord.z / gl_FragCoord.w);
// in highp float fogFactor;
// color = mix(color, fogColor, fogFactor);
// color = mix(color, fogColor, smoothstep(4.0,32.0,fogBlend));

/*
layout(location = 0) in highp vec3 vertexPosition;\
layout(location = 1) in highp vec2 vertexUV;\
layout(location = 2) uniform highp mat4 view_matrix;\
layout(location = 3) uniform highp vec3 position;\
layout(location = 4) uniform highp vec4 rotation;\
layout(location = 5) uniform highp float scale;\

layout(location = 6) uniform highp float brightness;\
layout(location = 7) uniform sampler2D tex;\
*/
