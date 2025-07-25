ecs_entity_t spawn_prefab_popup3(ecs_world_t *world,
    const ecs_entity_t prefab)
{
    zox_prefab_child(prefab)
    zox_prefab_name("popup3D")
    zox_add_tag(e, FillTexture)
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    zox_prefab_set(e, DestroyInTime, { 5 })
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_popup3(ecs_world_t *world,
    const SpawnDataElement3D data,
    Text3DData text_data,
    Zigel3DData zigel_data,
    const SpawnDataPopup3 popup_data)
{
    if (!text_data.prefab) {
        zox_log_error("invalid text_data prefab in spawn_popup3D");
        return 0;
    } else if (!zox_valid(data.prefab)) {
        zox_log_error("prefab_popup is invalid");
        return 0;
    }
    float3 depth_position = (float3) { 0, 0, element3D_depth_difference };
    zox_instance(data.prefab);
    zox_name("popup3D");
    zox_set(e, Color, { data.base_color });
    if (popup_data.lifetime) {
        zox_set(e, DestroyInTime, { popup_data.lifetime })
    }
    Children children = (Children) { 0, NULL };
    text_data.position = depth_position;
    text_data.parent = e;
    zigel_data.position = depth_position;
    zigel_data.scale = popup_data.scale; // 2;
    const ecs_entity_t text = spawn_text3D(world, text_data, zigel_data);
    // zox_set(text, Scale1D, { 4 })
    add_to_Children(&children, text);
    zox_set_ptr(e, Children, children);
    return e;
}