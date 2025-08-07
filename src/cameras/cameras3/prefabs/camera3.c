entity spawn_prefab_camera3D(ecs *world, const entity prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("camera3D")
    zox_add_tag(e, Camera3D)
#ifndef zox_disable_post_processing
    zox_add_tag(e, RenderCamera)
#endif
    return e;
}