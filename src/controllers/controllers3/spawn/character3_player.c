ecs_entity_t spawn_character3_player(ecs_world_t *world,
    spawn_character3D_data spawn_data)
{
    spawn_data.prefab = prefab_character3_player;
    spawn_data.scale = vox_model_scale;
    // spawn_data.lod = character_lod;
    const ecs_entity_t e = spawn_character3(world, spawn_data);
    // make_test_skeleton(world, e);
    zox_name("character3_player")
    // do this in character spawn code (for character3_player)
    zox_geter_value(spawn_data.player, CameraLink, ecs_entity_t, camera)
    zox_set(e, PlayerLink, { spawn_data.player })
    zox_set(e, CameraLink, { camera })
    zox_set(spawn_data.player, CharacterLink, { e })
    attach_camera_to_character(world, spawn_data.player, camera, e);
    return e;
}