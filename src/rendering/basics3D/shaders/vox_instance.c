// todo: Different meshes, linking, and then use a stack
//  also LODing support
#define zox_max_vox_instances 10000
ecs_entity_t shader_vox_instance;
ecs_entity_t material_vox_instance;

GLuint generate_ubo(GLint binding_point) {
    GLuint ubo;
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(float4x4) * zox_max_vox_instances, NULL, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_point, ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, 0); // Unbind after allocation
    zox_log_shader(" + spawned ubo: %i binded to block index %i", ubo, binding_point)
    return ubo;
}

GLuint spawn_ubo(ecs_world_t *world, const ecs_entity_t material) {
    const MaterialVoxInstance *materialVoxInstance = zox_get(material, MaterialVoxInstance)
    const GLint binding_point = materialVoxInstance->matrices;
    if (binding_point == GL_INVALID_INDEX) zox_log("InstanceMatrices block index not found in shader.\n")
        return generate_ubo(binding_point);
}

ecs_entity_t spawn_material_vox_instance(ecs_world_t *world) {
    const byte shader_index = get_new_shader_source_index();
    char* vert = get_shader_source(world, "vox_instance.vert");
    char* frag = get_shader_source(world, "vox_instance.frag");
    shader_verts[shader_index] = vert;
    shader_frags[shader_index] = frag;
    const ecs_entity_t shader = spawn_shader(world, shader_index);
    if (!shader) return 0;
    GLuint material;
    const ecs_entity_t e = spawn_material(world, shader, &material);
    zox_set(e, ShaderLink, { shader })
    const MaterialVoxInstance materialVoxInstance =  create_MaterialVoxInstance(material);
    zox_set_data(e, MaterialVoxInstance, materialVoxInstance)
    material_vox_instance = e;
    shader_vox_instance = shader;
    GLuint ubo = generate_ubo(materialVoxInstance.matrices);
    zox_set(e, UboGPULink, { ubo })
    return e;
}

/*const GLchar* shader_vert_vox_instance = "\
#version 320 es\n\
layout(location=0) in highp vec3 vertex_position;\
layout(location=1) in highp vec3 vertex_color;\
uniform InstanceMatrices {\
    lowp mat4 matrices[10000];\
};\
uniform highp mat4 camera_matrix;\
uniform lowp vec4 fog_data;\
out lowp vec3 vertex_color_frag;\
out lowp float fog_blend;\
\
void main() {\
    lowp mat4 transform_matrix = matrices[gl_InstanceID];\
    gl_Position = camera_matrix * transform_matrix * vec4(vertex_position, 1);\
    vertex_color_frag = vertex_color;\
    highp float fog_level = gl_Position.z * gl_Position.z;\
    fog_blend = min(1.0, 1.1 - exp2(-fog_data.w * fog_level));\
}";

const GLchar* shader_frag_vox_instance = "\
#version 320 es\n\
in lowp vec3 vertex_color_frag;\
in lowp float fog_blend;\
uniform lowp vec4 fog_data;\
uniform lowp float brightness;\
out lowp vec3 frag_color;\
\
void main() {\
    frag_color = vertex_color_frag * brightness;\
    frag_color = mix(frag_color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
}";*/
