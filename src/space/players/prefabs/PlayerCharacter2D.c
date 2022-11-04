//! Basic noise texture.
ecs_entity_t playerCharacter2DPrefab;

void SpawnPlayerCharacter2DPrefab(ecs_world_t *world)
{
    playerCharacter2DPrefab = ecs_new_w_pair(world, EcsIsA, character2DPrefab);
    ecs_add_id(world, playerCharacter2DPrefab, EcsPrefab);
    ecs_set_name(world, playerCharacter2DPrefab, "PlayerCharacter2D_Prefab");
    zoxel_add_tag(world, playerCharacter2DPrefab, PlayerCharacter2D);
    zoxel_add_component(world, playerCharacter2DPrefab, CameraLink);
}