// Shader3D Textured
GLuint2 shader3D_textured;
const char* shader3D_textured_filepath_vert = resources_folder_name"shaders/3D/shader3D_textured.vert";
const char* shader3D_textured_filepath_frag = resources_folder_name"shaders/3D/shader3D_textured.frag";
//! inline shaders incase the shader files don't exist.
const GLchar* shader3D_textured_vert_buffer = "\
#version 300 es\n\
in lowp vec3 vertexPosition; \
in lowp vec2 vertexUV; \
uniform lowp mat4 viewMatrix; \
uniform lowp vec3 position; \
uniform lowp vec4 rotation; \
uniform lowp float scale; \
out lowp vec2 uv; \
out lowp float fogFactor;\
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
    uv = vertexUV;\
    fogFactor = (viewMatrix * vec4(position + float4_rotate_float3(rotation, vertexPosition * scale), 1.0)).z;\
}\
";
const GLchar* shader3D_textured_frag_buffer = "\
#version 300 es\n\
in lowp vec2 uv;\
in lowp float fogFactor;\
uniform lowp float brightness; \
uniform sampler2D tex; \
out lowp vec4 color; \
 \
void main() \
{ \
    color = texture(tex, uv) * brightness; \
    lowp vec4 backgroundColor = vec4(2.0f / 255.0f, 16.0f / 255.0f, 24.0f / 255.0f, 1);\
    lowp float fog_density = 0.01;\
    lowp float fogBlend = 1.0 - exp2(-fog_density * fog_density * fogFactor * fogFactor);\
    color = mix(color, backgroundColor, fogBlend);\
} \
";

//  
// lowp float fogFactor = fogDensity * (gl_FragCoord.z / gl_FragCoord.w);
// in lowp float fogFactor;
// color = mix(color, fogColor, fogFactor);
// color = mix(color, fogColor, smoothstep(4.0,32.0,fogBlend));

void dispose_shader3D_textured()
{
    glDeleteShader(shader3D_textured.x);
    glDeleteShader(shader3D_textured.y);
}

int load_shader3D_textured()
{
    // shader3D_textured = spawn_gpu_shader(shader3D_textured_filepath_vert, shader3D_textured_filepath_frag);
    shader3D_textured = spawn_gpu_shader_inline(shader3D_textured_vert_buffer, shader3D_textured_frag_buffer);
    return 0;
}

void opengl_set_texture(GLuint texturel_buffer, unsigned char isBlend)
{
    if (isBlend)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }
    else
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_BLEND);
    }
    glBindTexture(GL_TEXTURE_2D, texturel_buffer);
}

void opengl_disable_texture(unsigned char isBlend)
{
    if (isBlend)
    {
        glDisable(GL_BLEND);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void opengl_set_buffer_attributes(GLuint material, GLuint vertex_buffer, GLuint uv_buffer)
{
    Material3DTextured materialTextured3D = spawn_material3D_textured(material);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glEnableVertexAttribArray(materialTextured3D.vertexPosition);
    glVertexAttribPointer(materialTextured3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 12, 0);

    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glEnableVertexAttribArray(materialTextured3D.vertexUV);
    glVertexAttribPointer(materialTextured3D.vertexUV, 2, GL_FLOAT, GL_FALSE, 8, 0); // (GLvoid*)(12));
}

int opengl_set_material3D_uvs_properties(GLuint material,
    float3 position, float4 rotation, float scale, float brightness)
{
    Material3DTextured materialTextured3D = spawn_material3D_textured(material);
    glUniform3f(materialTextured3D.position, position.x, position.y, position.z);
    glUniform4f(materialTextured3D.rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    glUniform1f(materialTextured3D.scale, scale);
    glUniform1f(materialTextured3D.brightness, brightness);
    #ifdef zoxel_catch_opengl_errors
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            zoxel_log("GL ERROR with opengl_set_material3D_uvs_properties [%i]\n", (int) err);
            return -1;
        }
    #endif
    return 0;
}

// printf("Rendering Cube [%ix%i]\n", mesh.x, mesh.y);
// printf("    - Rendering Cube [%ix%i]\n", squareTexturedMesh.x, squareTexturedMesh.y);
// glEnableVertexAttribArray(materialTextured3D.vertexPosition);
// glVertexAttribPointer(materialTextured3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 12, 0); // 4 * 3

void opengl_upload_shader3D_textured(
    GLuint2 mesh_buffer, GLuint uv_buffer, GLuint material_buffer,
    const int *indicies, int indicies_length,
    const float3 *verts, int verts_length,
    const float2 *uvs, int uvs_length)
{
    quad_count += indicies_length / 3;
    Material3DTextured material3D = spawn_material3D_textured(material_buffer);
    // Bind the index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * sizeof(int), indicies, GL_STATIC_DRAW);

    // Bind the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float3), verts, GL_STATIC_DRAW);

    // Bind the UV buffer
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glBufferData(GL_ARRAY_BUFFER, uvs_length * sizeof(float2), uvs, GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    glVertexAttribPointer(material3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(material3D.vertexUV, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(float3) * verts_length));

    // Enable the vertex attribute arrays
    glEnableVertexAttribArray(material3D.vertexPosition);
    glEnableVertexAttribArray(material3D.vertexUV);

    // Unbind the buffers
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/*Material3DTextured materialTextured3D = spawn_material3D_textured(material);
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
    Material3DTextured material3D = spawn_material3D_textured(material_buffer);
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