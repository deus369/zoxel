
typedef struct {
    float percentage;
} Elementbar3DData;

typedef struct {
    Canvas3DData canvas;
    Element3DData backbar;
    Element3DData frontbar;
    Element3DData text;
    Element3DData zigel;
    Elementbar3DData meta;
} SpawnDataElementbar3D;

ecs_entity_t spawn_prefab_elementbar3D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_elementbar3D")
    zox_add_tag(e, FillTexture)
    zox_prefab_set(e, ElementBar, { 1 })
    zox_prefab_set(e, ElementBarSize, { float2_zero })
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    zox_prefab_set(e, Color, { back_bar_color }) // back_bar_color_3D_start })
    zox_prefab_add(e, Children)
    zox_set(e, UITrail, {{ 0, 0.43f, 0 }})
    prefab_set_mesh3D_vertices(world, e, square_vertices, 4, statbar_back_mesh_scale);
    return e;
}

ecs_entity_t spawn_elementbar3D(ecs_world_t *world, SpawnDataElementbar3D *data) {
    zox_instance(data->backbar.prefab)
    zox_name("elementbar3D")
    zox_set(e, UIHolderLink, { data->canvas.ui_holder })
    zox_set(e, UITrail, { { 0, data->canvas.position_y, 0 } })
    zox_set(e, ElementBar, { data->meta.percentage })
    zox_set(e, ElementBarSize, { statbar_front_mesh_scale })
    zox_set(e, RenderDisabled, { data->backbar.render_disabled })
    Children *children = &((Children) { 0, NULL });
    const float3 frontbar_position = (float3) { 0, 0, element3D_depth_difference };
    const ecs_entity_t frontbar = spawn_elementbar3D_front(world, data->frontbar.prefab, data->canvas.ui_holder, e, frontbar_position, data->frontbar.render_disabled);
    add_to_Children(children, frontbar);
    const float3 text_position = (float3) { 0, 0, element3D_depth_difference * 2 };
    Text3DData text_data = {
        .parent = e,
        .prefab = data->text.prefab,
        .prefab_zigel = data->zigel.prefab,
        .text = "Health [10/10]", // "!"
        .position = text_position,
        .font_thickness = 2
    };
    const ecs_entity_t text = spawn_text3D(world, &text_data);
    add_to_Children(children, text);
    zox_set(e, Children, { children->length, children->value })
    return e;
}

//  const ecs_entity_t prefab, const ecs_entity_t prefab_front, const ecs_entity_t ui_holder, const float percentage, const byte render_disabled, const float position_y) {

// const ecs_entity_t camera = main_cameras[0];
// const ecs_entity_t canvas = zox_canvases[0];
// zox_set(e, CameraLink, { camera })
// zox_set(e, CanvasLink, { canvas })