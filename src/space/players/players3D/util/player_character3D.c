/*ecs_entity_t spawn_player_character3D(ecs_world_t *world, ecs_entity_t camera) {
    // child prefabs don't seem to inherit tags
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_player_character3D);
    zox_set(e, CameraLink, { camera })
    zox_set(camera, CameraTarget, { e })
    zox_set(camera, Character2DLink, { e })
    zox_set(e, Scale1D, { 0.06f + ((rand() % 101) / 100.0f) * 0.04f  })
    zox_set(e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f })
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, shader3D);
    return e;
}
*/
