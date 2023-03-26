
GLuint2 shader3D_colored;
const GLchar* shader3D_colored_vert_buffer = "\
#version 300 es\n\
in lowp vec3 vertexPosition; \
in lowp vec4 vertexColor; \
uniform lowp mat4 viewMatrix; \
uniform lowp vec3 position; \
uniform lowp vec4 rotation; \
uniform lowp float scale; \
out lowp vec4 vertexColorOutput; \
\
vec3 float4_rotate_float3(vec4 rotation, vec3 value) \
{ \
    vec3 rotationXYZ = rotation.xyz; \
    vec3 t = cross(rotationXYZ, value) * 2.0f; \
    vec3 crossB = cross(rotationXYZ, t); \
    vec3 scaledT = t * rotation.w; \
    return value + scaledT + crossB; \
} \
\
void main()\
{\
    gl_Position = viewMatrix * vec4(position + float4_rotate_float3(rotation, vertexPosition * scale), 1.0); \
    vertexColorOutput = vertexColor; \
}\
";
const GLchar* shader3D_colored_frag_buffer = "\
#version 300 es\n\
in lowp vec4 vertexColorOutput;\
uniform lowp float brightness; \
out lowp vec4 color; \
 \
void main() \
{ \
    color = vertexColorOutput * brightness; \
} \
";

void dispose_shader3D_colored() {
    glDeleteShader(shader3D_colored.x);
    glDeleteShader(shader3D_colored.y);
}

int load_shader3D_colored() {
    shader3D_colored = spawn_gpu_shader_inline(shader3D_colored_vert_buffer, shader3D_colored_frag_buffer);
    #ifdef zoxel_catch_opengl_errors
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            zoxel_log("GL ERROR with load_shader3D_colored [%i]\n", err);
            return false;
        }
    #endif
    return 0;
}

void set_gpu_mesh_colors(GLuint2 mesh, GLuint material, const int *indicies, int indicies_length,
    const float3 *verts, int verts_length, const color *colors) {
    tri_count += indicies_length / 3;
    MaterialColored3D materialColored3D = spawn_material3D_colored_properties(material);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);
    glEnableVertexAttribArray(materialColored3D.vertexPosition);
    glEnableVertexAttribArray(materialColored3D.vertexColor);
    int float_per_data = 7;
    int floats_length = verts_length * float_per_data;
    float combined_verts[floats_length];
    for (int i = 0; i < verts_length; i++)
    {
        float3 vert = verts[i];
        color vert_color = colors[i];
        // vert_color.r = rand() % 256;
        // vert_color.a = 1;
        float4 vert_color_float4 = color_to_float4(vert_color);
        combined_verts[i * float_per_data + 0] = vert.x;
        combined_verts[i * float_per_data + 1] = vert.y;
        combined_verts[i * float_per_data + 2] = vert.z;
        combined_verts[i * float_per_data + 3] = vert_color_float4.x;
        combined_verts[i * float_per_data + 4] = vert_color_float4.y;
        combined_verts[i * float_per_data + 5] = vert_color_float4.z;
        combined_verts[i * float_per_data + 6] = vert_color_float4.w;
        /*if (i < 16)
        {
            printf("    vert_color [%fx%fx%f] \n", vert_color_float4.x, vert_color_float4.y, vert_color_float4.z);
        }*/
    }
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * 4, indicies, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, floats_length * 4, combined_verts, GL_STATIC_DRAW);
    glVertexAttribPointer(materialColored3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 4 * float_per_data, (GLvoid*)(0 * sizeof(float)));
    glVertexAttribPointer(materialColored3D.vertexColor, 4, GL_FLOAT, GL_FALSE, 4 * float_per_data, (GLvoid*)(3 * sizeof(float)));
    // printf("Setting Vertex Attribute Pointer for [%ix%i] Mesh.\n", mesh.x, mesh.y);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int opengl_set_material3D_colors_properties(GLuint material,
    float3 position, float4 rotation, float scale, float brightness) {
    MaterialColored3D materialColored3D = spawn_material3D_colored_properties(material);
    glEnableVertexAttribArray(materialColored3D.vertexPosition);
    glEnableVertexAttribArray(materialColored3D.vertexColor);
    glVertexAttribPointer(materialColored3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 4 * 7, 0);
    glVertexAttribPointer(materialColored3D.vertexColor, 4, GL_FLOAT, GL_FALSE, 4 * 7, (GLvoid*)(3 * sizeof(float)));
    glUniform3f(materialColored3D.position, position.x, position.y, position.z);
    glUniform4f(materialColored3D.rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    glUniform1f(materialColored3D.scale, scale);
    glUniform1f(materialColored3D.brightness, brightness);
    #ifdef zoxel_catch_opengl_errors
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            zoxel_log("GL ERROR - opengl_set_material3D_colors_properties [%i]\n", (int) err);
            return -1;
        }
    #endif
    return 0;
}