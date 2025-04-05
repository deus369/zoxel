const float2 elementbar_size = (float2) { 0.2f, 0.05f };

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
    zox_prefab_set(e, ElementBar, { 1 })
    zox_prefab_set(e, ElementBarSize, { float2_zero })
    zox_add_tag(e, FillTexture)
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    zox_prefab_set(e, Color, { back_bar_color_3D_start })
    zox_prefab_add(e, Children)
    zox_set(e, UITrail, {{ 0, 0.43f, 0 }})
    prefab_set_mesh3D_vertices(world, e, square_vertices, 4, elementbar_size);
    return e;
}

ecs_entity_t spawn_elementbar3D(ecs_world_t *world, SpawnDataElementbar3D *data) {
    const float depth_difference = 0.0012f;
    zox_instance(data->backbar.prefab)
    zox_name("elementbar3D")
    zox_set(e, UIHolderLink, { data->canvas.ui_holder })
    zox_set(e, UITrail, { { 0, data->canvas.position_y, 0 } })
    zox_set(e, ElementBar, { data->meta.percentage })
    zox_set(e, ElementBarSize, { statbar_front_mesh_scale })
    zox_set(e, RenderDisabled, { data->backbar.render_disabled })

    Children *children = &((Children) { 0, NULL });

    const ecs_entity_t frontbar = spawn_elementbar3D_front(world, data->frontbar.prefab, data->canvas.ui_holder, e, (float3) { 0, 0, depth_difference }, data->frontbar.render_disabled);
    add_to_Children(children, frontbar);

    Text3DData text_data = {
        .parent = e,
        .prefab = data->text.prefab,
        .prefab_zigel = data->zigel.prefab,
        .text = "!",
    };
    const ecs_entity_t text = spawn_text3D(world, &text_data);
    add_to_Children(children, text);
    zox_set(e, Children, { children->length, children->value })

    zox_set(e, RenderDisabled, { 1 })
    return e;
}

//  const ecs_entity_t prefab, const ecs_entity_t prefab_front, const ecs_entity_t ui_holder, const float percentage, const byte render_disabled, const float position_y) {

// const ecs_entity_t camera = main_cameras[0];
// const ecs_entity_t canvas = zox_canvases[0];
// zox_set(e, CameraLink, { camera })
// zox_set(e, CanvasLink, { canvas })