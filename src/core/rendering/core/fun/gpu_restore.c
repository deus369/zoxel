// restore opengl resources here
void restore_all_opengl_resources(ecs_world_t *world) {
    if (is_using_vulkan) return;
    zoxel_log(" > restoring all opengl resources\n");
    restore_shaders_dynamic(world);
    ecs_run(world, ecs_id(MeshGPURestoreSystem), 0, NULL);
    ecs_run(world, ecs_id(UvsGPULinkRestoreSystem), 0, NULL);
    ecs_run(world, ecs_id(ColorsGPULinkRestoreSystem), 0, NULL);
    ecs_run(world, ecs_id(MeshDirtyRestoreSystem), 0, NULL);
    ecs_run(world, ecs_id(MaterialRestoreSystem), 0, NULL);
    ecs_run(world, ecs_id(TextureRestoreSystem), 0, NULL);
}

void opengl_load_resources(ecs_world_t *world) {
    if (is_using_vulkan) return;
    rendering = 1;
    skip_time_to_current();
    restore_all_opengl_resources(world);
}
