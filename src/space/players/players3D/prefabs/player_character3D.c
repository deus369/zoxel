ecs_entity_t player_character3D_prefab;

ecs_entity_t spawn_player_character3D_prefab(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(prefab_character3D)
    zox_name("prefab_player_character3D")
    zox_add_tag(e, PlayerCharacter)
    zox_add_tag(e, PlayerCharacter3D)
    zox_add(e, CameraLink)
    zox_set(e, DisableMovement, { 0 })
    zox_remove(e, AnimateChunk)
    // ecs_remove(world, e, AnimateChunk);
    // printf("Has AnimateChunk? %b\n", ecs_has(world, e, AnimateChunk));
    ecs_defer_end(world);
    player_character3D_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab player_character3D [%lu].\n", (long int) (e));
    #endif
    return e;
}