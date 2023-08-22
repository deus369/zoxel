ecs_entity_t prefab_player_character2D;

ecs_entity_t spawn_prefab_player_character2D(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(character2D_prefab)
    zox_name("prefab_player_character2D")
    zox_add_tag(e, PlayerCharacter)
    zox_add_tag(e, PlayerCharacter2D)
    zox_add(e, CameraLink)
    zox_set(e, DisableMovement, { 0 })
    ecs_defer_end(world);
    prefab_player_character2D = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab player_character2D [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_player_character2D(ecs_world_t *world, ecs_entity_t camera) {
    zox_instance(prefab_player_character2D) // child prefabs don't seem to inherit tags ??
    zox_name("player_character2D")
    zox_set_only(e, Scale1D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  })
    zox_set_only(e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f })
    zox_set_only(e, CameraLink, { camera })
    zox_set_only(camera, CameraTarget, { e })
    zox_set_only(camera, Character2DLink, { e })
    spawn_gpu_material(world, e, shader2D_textured);
    spawn_gpu_texture(world, e);
    local_player = e;
    return e;
}

// ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_player_character2D)
// ecs_add_pair(world, e, CameraLink, mainCamera);
// ecs_add_pair(world, mainCamera, Character2DLink, e);