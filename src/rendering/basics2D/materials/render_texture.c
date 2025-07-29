ecs_entity_t shader_render_texture;
ecs_entity_t material_render_texture;


//! Links to locations inside a base material->
typedef struct {
    GLint vertex_position;
    GLint vertex_uv;
    uint camera_matrix;
    uint transform_matrix;
    uint texture;
} MaterialAttributesRenderTexture;
zox_custom_component(MaterialAttributesRenderTexture)

MaterialAttributesRenderTexture create_MaterialAttributesRenderTexture(const uint material) {
    return (MaterialAttributesRenderTexture) {
        .vertex_position = glGetAttribLocation(material, "vertex_position"),
        .vertex_uv = glGetAttribLocation(material, "vertex_uv"),
        .camera_matrix = glGetUniformLocation(material, "camera_matrix"),
        .transform_matrix = glGetUniformLocation(material, "transform_matrix"),
        .texture = glGetUniformLocation(material, "texture") };
}

ecs_entity_t spawn_shader_render_texture(ecs_world_t *world) {
    const byte shader_index = get_new_shader_source_index();
    char* vert = get_shader_source(world, "render_texture.vert");
    char* frag = get_shader_source(world, "render_texture.frag");
    shader_verts[shader_index] = vert;
    shader_frags[shader_index] = frag;
    const ecs_entity_t e = spawn_shader(world, shader_index);
    if (!e) {
        zox_log_error("[shader_render_texture] failed to spawn")
        return 0;
    }
    zox_name("shader_render_texture")
    return e;
}

ecs_entity_t spawn_material_render_texture(ecs_world_t *world) {
    const ecs_entity_t shader = spawn_shader_render_texture(world);
    if (!shader) return 0;
    uint material;
    const ecs_entity_t e = spawn_material(world, shader, &material);
    zox_set(e, ShaderLink, { shader })
    const MaterialAttributesRenderTexture attributes = create_MaterialAttributesRenderTexture(material);
    zox_set_data(e, MaterialAttributesRenderTexture, attributes)
    material_render_texture = e;
    shader_render_texture = shader;
    return e;
}
