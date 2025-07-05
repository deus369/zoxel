ecs_entity_t spawn_prefab_popup3D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_popup3D")
    zox_add_tag(e, FillTexture)
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    zox_prefab_set(e, DestroyInTime, { 5 })
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_popup3D(ecs_world_t *world, const SpawnDataElement3D data, Text3DData text_data, Zigel3DData zigel_data) {
    if (!text_data.prefab) {
        zox_log("invalid text_data prefab in spawn_popup3D\n")
        return 0;
    }
    zox_instance(data.prefab)
    zox_name("popup3D")
    zox_set(e, Color, { data.base_color })
    float3 depth_position = (float3) { 0, 0, element3D_depth_difference };
    text_data.position = depth_position;
    text_data.parent = e;
    zigel_data.position = depth_position;
    zigel_data.scale = 2;
    const ecs_entity_t text = spawn_text3D(world, text_data, zigel_data);
    if (text) {
        Children *children = &((Children) { 0, NULL });
        add_to_Children(children, text);
        zox_set(e, Children, { children->length, children->value })
        // zox_set(text, Scale1D, { 4 })
    }
    return e;
}