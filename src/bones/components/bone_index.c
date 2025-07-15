zox_component(BoneIndexGPULink, uint)

void add_gpu_bone_index(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_prefab_set(e, BoneIndexGPULink, { 0 })
}

void spawn_gpu_bone_index(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set(e, BoneIndexGPULink, { spawn_gpu_generic_buffer() })
}

ECS_DTOR(BoneIndexGPULink, ptr, {
    if (ptr->value) glDeleteBuffers(1, &ptr->value);
})

