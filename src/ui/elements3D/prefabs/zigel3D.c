typedef struct {
    ecs_entity_t prefab;
    ecs_entity_t parent;
    byte zigel_index; // zox character code
    color fill_color;
    color outline_color;
    byte font_thickness;
    byte resolution;
    float3 position;
    byte render_disabled; // zox character code
} Zigel3DData;

ecs_entity_t spawn_prefab_zigel3D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_zigel3D")
    zox_add_tag(e, Zigel)
    zox_add_tag(e, FontTexture)
    zox_prefab_set(e, ZigelIndex, { 0 })
    zox_prefab_set(e, Color, { color_white })
    zox_prefab_set(e, SecondaryColor, { color_white })
    zox_prefab_set(e, FontThickness, { 1 })
    zox_set(e, TextureSize, { 32, 32 })
    // zox_set(e, Scale1D, { 2 })
    prefab_set_mesh3D_vertices(world, e, square_vertices, 4, zigel3D_size);
    return e;
}

ecs_entity_t spawn_zigel3D(ecs_world_t *world, const Zigel3DData data) {
    zox_instance(data.prefab)
    zox_name("zigel3D")
    zox_set(e, ParentLink, { data.parent })
    zox_set(e, ZigelIndex, { data.zigel_index })
    zox_set(e, FontThickness, { data.font_thickness })
    zox_set(e, Color, { data.fill_color })
    zox_set(e, SecondaryColor, { data.outline_color })
    zox_set(e, LocalPosition3D, { data.position })
    zox_set(e, RenderDisabled, { data.render_disabled })
    zox_set(e, TextureSize, { data.resolution, data.resolution })
    return e;
}
