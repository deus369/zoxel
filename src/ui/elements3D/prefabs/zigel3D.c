typedef struct {
    ecs_entity_t prefab;
    ecs_entity_t parent;
    byte zigel_index; // zox character code
    int data_index;   // a link to TextData array index
    color fill_color;
    color outline_color;
    byte font_size;
    byte font_thickness;
    int2 texture_size;
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
    zox_set(e, TextureSize, { 64, 64 })
    zox_set(e, Scale1D, { 4 })
    return e;
}

ecs_entity_t spawn_zigel3D(ecs_world_t *world, const Zigel3DData *data) {
    zox_instance(data->prefab)
    zox_name("zigel3D")
    zox_set(e, ParentLink, { data->parent })
    zox_set(e, ZigelIndex, { data->zigel_index })
    // zox_set(e, FontThickness, { 8 }) // data->meta.font_thickness })
    zox_set(e, Color, { color_black }) // data->meta.fill_color })
    zox_set(e, SecondaryColor, { color_white}) // data->meta.outline_color })
    zox_log("+ spawned zigel3D (%s): %lu\n", zox_get_name(data->prefab), e)
    return e;
}
