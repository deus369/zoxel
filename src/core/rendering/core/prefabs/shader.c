ecs_entity_t prefab_shader;
// todo: keep a reference to the script for the shader

ecs_entity_t spawn_prefab_shader(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_prefab_name("prefab_shader")
    zox_add_tag(e, Shader)
    // zox_add(e, ShaderGPULink)
    add_gpu_shader(world, e);
    ecs_defer_end(world);
    prefab_shader = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab shader [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_shader(ecs_world_t *world, const GLchar* vert_buffer, const GLchar* frag_buffer) {
    zox_instance(prefab_shader)
    zox_name("shader")
    zox_set_only(e, ShaderGPULink, { spawn_gpu_shader_inline(vert_buffer, frag_buffer) })
    /*ShaderGPULink *shaderGPULink = ecs_get_mut(world, e, ShaderGPULink);
    shaderGPULink->value = value;
    ecs_modified(world, e, ShaderGPULink);*/
    return e;
}

void restore_shader(ecs_world_t *world, ecs_entity_t e, const GLchar* vert_buffer, const GLchar* frag_buffer) {
    zox_set_only(e, ShaderGPULink, { spawn_gpu_shader_inline(vert_buffer, frag_buffer) })
}