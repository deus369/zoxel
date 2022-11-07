//! Basic noise texture.
ecs_entity_t playerCharacter2DPrefab;

void spawn_player_character2D_prefab(ecs_world_t *world)
{
    playerCharacter2DPrefab = ecs_new_w_pair(world, EcsIsA, character2DPrefab);
    printf("Spawned player_character2D_prefab [%lu].\n", (long int) (playerCharacter2DPrefab));
    ecs_add_id(world, playerCharacter2DPrefab, EcsPrefab);
    ecs_set_name(world, playerCharacter2DPrefab, "player_character2D_prefab");
    zoxel_add_tag(world, playerCharacter2DPrefab, PlayerCharacter2D);
    zoxel_add_component(world, playerCharacter2DPrefab, CameraLink);
}