//! Basic noise texture.
ecs_entity_t playerCharacter2DPrefab;

void InitializePlayerCharacter2DPrefab(ecs_world_t *world)
{
    playerCharacter2DPrefab = ecs_new_w_pair(world, EcsIsA, character2DPrefab);
    ecs_add_id(world, playerCharacter2DPrefab, EcsPrefab);
    ecs_set_name(world, playerCharacter2DPrefab, "PlayerCharacter2D_Prefab");
    ecs_add(world, playerCharacter2DPrefab, PlayerCharacter2D);
}