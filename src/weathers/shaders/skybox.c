ecs_entity_t spawn_shader_skybox(ecs_world_t *world) {
    const byte shader_index = get_new_shader_source_index();
    char* vert = get_shader_source(world, "skybox.vert");
    char* frag = get_shader_source(world, "skybox.frag");
    shader_verts[shader_index] = vert;
    shader_frags[shader_index] = frag;
    const ecs_entity_t e = spawn_shader(world, shader_index);
    zox_name("shader_skybox")
    return e;
}