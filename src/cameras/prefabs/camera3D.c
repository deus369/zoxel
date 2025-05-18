ecs_entity_t spawn_prefab_camera3D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_camera3D")
    zox_add_tag(e, Camera3D)
    #ifndef zox_disable_post_processing
        zox_add_tag(e, RenderCamera)
    #endif
    return e;
}