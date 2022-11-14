//! Basic noise texture.
ecs_entity_t player_character2D_prefab;

void spawn_player_character2D_prefab(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, character2DPrefab);
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab player_character2D [%lu].\n", (long int) (e));
    #endif
    ecs_add_id(world, e, EcsPrefab);
    ecs_set_name(world, e, "player_character2D_prefab");
    zoxel_add_tag(world, e, PlayerCharacter2D);
    zoxel_add_component(world, e, CameraLink);
    player_character2D_prefab = e;
}