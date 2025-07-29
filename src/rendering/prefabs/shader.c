ecs_entity_t prefab_shader;

ecs_entity_t spawn_prefab_shader(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("shader")
    zox_add_tag(e, Shader)
    zox_prefab_set(e, ShaderSourceIndex, { 0 })
    add_gpu_shader(world, e); // adds ShaderGPULink
    prefab_shader = e;
    return e;
}

ecs_entity_t spawn_shader(ecs_world_t *world, const int shader_index) {
    uint2 shader = zox_gpu_compile_shader(shader_verts[shader_index], shader_frags[shader_index]);
    if (uint2_equals(shader, uint2_zero)) {
        zox_log_error("shader has failed")
        return 0;
    }
    zox_instance(prefab_shader)
    zox_name("shader")
    zox_set(e, ShaderSourceIndex, { shader_index })
    zox_set(e, ShaderGPULink, { shader })
    return e;
}

/*void restore_shader(ecs_world_t *world, ecs_entity_t e, const GLchar* vert_buffer, const GLchar* frag_buffer) {
    zox_set(e, ShaderGPULink, { zox_gpu_compile_shader(vert_buffer, frag_buffer) })
}*/
