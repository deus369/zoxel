// delete opengl resources, shaders, textures,
void delete_all_opengl_resources(ecs_world_t *world) {
    if (is_using_vulkan) return;
    zoxel_log(" > disposing all opengl resources\n");
    ecs_run(world, ecs_id(MeshGPUDisposeSystem), 0, NULL);
    ecs_run(world, ecs_id(MeshColorsGPUDisposeSystem), 0, NULL);
    ecs_run(world, ecs_id(MeshUvsGPUDisposeSystem), 0, NULL);
    ecs_run(world, ecs_id(ShaderGPUDisposeSystem), 0, NULL);
    ecs_run(world, ecs_id(MaterialGPUDisposeSystem), 0, NULL);
    ecs_run(world, ecs_id(TextureGPUDisposeSystem), 0, NULL);
    opengl_dispose_shaders(); // todo: remove, for ones that  arn't entities yet
}

void opengl_delete_resources(ecs_world_t *world) {
    if (is_using_vulkan) return;
    rendering = 0;
    delete_all_opengl_resources(world);
}
