// todo: remove any canvas elements, these will just be world transform uis
ecs_entity_t prefab_element_world_child;

ecs_entity_t spawn_prefab_element3D_child(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_element_world_child")
    zox_add_tag(e, Element3D)
    zox_add_tag(e, SingleMaterial)
    zox_prefab_set(e, Color, {{ 0, 255, 0, 255 }}) 
    zox_prefab_set(e, ParentLink, { 0 })
    zox_prefab_set(e, LocalPosition3D, { float3_zero })
    zox_prefab_set(e, LocalRotation3D, { quaternion_identity })
    add_ui_components_world(world, e, (float2) { 0.2f, 0.05f });
    prefab_element_world_child = e;
#ifdef zoxel_debug_prefabs
    zox_log(" > spawned prefab element_world [%lu]\n", e)
#endif
    return e;
}
