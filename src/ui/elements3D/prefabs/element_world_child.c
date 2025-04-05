ecs_entity_t spawn_prefab_element3D_child(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_element3D_child")
    zox_add_tag(e, Element3D)
    zox_prefab_set(e, Color, {{ 0, 255, 0, 255 }}) 
    zox_prefab_set(e, ParentLink, { 0 })
    zox_prefab_set(e, LocalPosition3D, { float3_zero })
    // zox_prefab_set(e, LocalPosition3D, { (float3) { 0, 0, -0.01f } })
    zox_prefab_set(e, LocalRotation3D, { quaternion_identity })
    add_ui_components_world(world, e, (float2) { 0.2f, 0.05f });
    if (!headless) zox_add_tag(e, SingleMaterial)
    return e;
}
