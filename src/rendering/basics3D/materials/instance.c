// todo: Different meshes, linking, and then use a stack
//  also LODing support
byte can_render_instanes = 1;
// #define zox_max_vox_instances 10000 // needs to match the shader file
ecs_entity_t shader_vox_instance = 0;
ecs_entity_t material_vox_instance = 0;

typedef struct {
    GLint vertex_position;
    GLint vertex_color;
    GLint matrices;
    uint camera_matrix;
    uint brightness;
    uint fog_data;
} MaterialVoxInstance;
zox_custom_component(MaterialVoxInstance)

MaterialVoxInstance create_MaterialVoxInstance(const uint material) {
    return (MaterialVoxInstance) {
        glGetAttribLocation(material, "vertex_position"),
        glGetAttribLocation(material, "vertex_color"),
        glGetUniformBlockIndex(material, "InstanceMatrices"),
        glGetUniformLocation(material, "camera_matrix"),
        glGetUniformLocation(material, "brightness"),
        glGetUniformLocation(material, "fog_data")
    };
}

uint generate_ubo(GLint binding_point) {
    uint ubo;
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(float4x4) * zox_get_safe_ubo_size(), NULL, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_point, ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, 0); // Unbind after allocation
    zox_log_shader(" + spawned ubo: %i binded to block index %i", ubo, binding_point)
    return ubo;
}

uint spawn_ubo(ecs_world_t *world, const ecs_entity_t material) {
    zox_geter(material, MaterialVoxInstance, materialVoxInstance)
    const GLint binding_point = materialVoxInstance->matrices;
    if (binding_point == GL_INVALID_INDEX) {
        zox_log_error("InstanceMatrices block index not found in shader")
        can_render_instanes = 0;
    }
    return generate_ubo(binding_point);
}

ecs_entity_t spawn_material_vox_instance(ecs_world_t *world) {
    const byte shader_index = get_new_shader_source_index();
    char* vert = get_shader_source(world, "vox_instance.vert");
    char* frag = get_shader_source(world, "vox_instance.frag");
    shader_verts[shader_index] = vert;
    shader_frags[shader_index] = frag;
    const ecs_entity_t shader = spawn_shader(world, shader_index);
    if (!shader) {
        zox_log_error("[shader_vox_instance] failed to spawn")
        can_render_instanes = 0;
        return 0;
    }
    uint material;
    const ecs_entity_t e = spawn_material(world, shader, &material);
    zox_set(e, ShaderLink, { shader })
    if (!material) {
        zox_log_error("vox instance material failed to initialize")
        can_render_instanes = 0;
        return 0;
    }
    const MaterialVoxInstance materialVoxInstance =  create_MaterialVoxInstance(material);
    zox_set_data(e, MaterialVoxInstance, materialVoxInstance)
    uint ubo = generate_ubo(materialVoxInstance.matrices);
    zox_set(e, UboGPULink, { ubo })
    material_vox_instance = e;
    shader_vox_instance = shader;
    return e;
}