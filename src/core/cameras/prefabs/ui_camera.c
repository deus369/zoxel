ecs_entity_t spawn_ui_camera(ecs_world_t *world, int2 screenDimensions) {
    float3 position = { 0, 0, 1.0f };
    zox_instance(prefab_base_camera)
    zox_name("ui_camera")
    zox_add_tag(e, UICamera)
    zox_set_only(e, Position3D, { position })
    zox_set_only(e, Rotation3D, { quaternion_identity })
    zox_set_only(e, FieldOfView, { 53.2f })  // fudged this to get ui right... maybe not the best but it works xD
    zox_set_only(e, ScreenDimensions, { screenDimensions })
    zox_add_tag(e, Camera2D)
    ui_cameras[0] = e;
    #ifdef zoxel_debug_spawns
        zox_log(" > spawned ui_camera [%lu]\n", e)
    #endif
    return e;
}