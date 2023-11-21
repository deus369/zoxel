// todo: canvas lines doesn't update in this
extern int2 get_line_element_mid_point(ecs_world_t *world, ecs_entity_t e);
extern void set_line_element_real_position2D(ecs_world_t *world, ecs_entity_t e, float2 real_position2D, int2 canvas_size, int2 pixel_position);

void set_element_position(ecs_world_t *world, ecs_entity_t e, int2 parent_pixel_position_global, int2 parent_pixel_size, int2 canvas_size) {
    if (e == 0 || !ecs_is_alive(world, e)) return;
    // get e components
    int2 pixel_position = int2_zero;
    if (zox_has(e, PixelPosition)) pixel_position = zox_get_value(e, PixelPosition)
    else pixel_position = get_line_element_mid_point(world, e);
    float2 anchor = float2_zero;    // should i pass this in from parent?
    if (zox_has(e, Anchor)) anchor = zox_get_value(e, Anchor)
    // calculate pixel and real positions
    int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    float2 position = get_element_position(pixel_position_global, canvas_size);
    // now set variables
    if (zox_has(e, Position2D)) {
        Position2D *position2D = zox_get_mut(e, Position2D)
        position2D->value = position;
        zox_modified(e, Position2D)
    }
    if (zox_has(e, CanvasPosition)) {
        CanvasPosition *canvasPosition = zox_get_mut(e, CanvasPosition)
        canvasPosition->value = pixel_position_global;
        zox_modified(e, CanvasPosition)
    }
    set_line_element_real_position2D(world, e, position, canvas_size, pixel_position);
    if (zox_has(e, Children)) {
        int2 pixel_size = zox_get_value(e, PixelSize)
        const Children *children = ecs_get(world, e, Children);
        for (int i = 0; i < children->length; i++) set_element_position(world, children->value[i], pixel_position_global, pixel_size, canvas_size);
    }
}

// moves ui around after repositioning the pixel position
// todo: hierarchy doesn't set properly... uses this to set
void ElementPositionSystem(ecs_iter_t *it) {
    zox_iter_world()
    ecs_query_t *change_query = it->ctx;
    ecs_iter_t change_iter = ecs_query_iter(world, change_query);
    while (ecs_query_next(&change_iter)) {
        if (change_iter.table != it->table) ecs_query_skip(&change_iter);
    }
    const PixelPosition *pixelPositions = ecs_field(it, PixelPosition, 2);
    const ParentLink *parentLinks = ecs_field(it, ParentLink, 3);
    const Anchor *anchors = ecs_field(it, Anchor, 4);
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 5);
    Position2D *position2Ds = ecs_field(it, Position2D, 6);
    CanvasPosition *canvasPositions = ecs_field(it, CanvasPosition, 7);
    for (int i = 0; i < it->count; i++) {
        ecs_entity_t e = it->entities[i];
        const PixelPosition *pixelPosition = &pixelPositions[i];
        const ParentLink *parentLink = &parentLinks[i];
        const Anchor *anchor = &anchors[i];
        const CanvasLink *canvasLink = &canvasLinks[i];
        if (!ecs_is_valid(world, canvasLink->value) || parentLink->value != canvasLink->value) continue;
        const int2 canvas_size = zox_get_value(canvasLink->value, PixelSize)
        Position2D *position2D = &position2Ds[i];
        CanvasPosition *canvasPosition = &canvasPositions[i];
        int2 pixel_position = pixelPosition->value;
        float2 anchor2 = anchor->value;
        int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor2);
        float2 position = get_element_position(pixel_position_global, canvas_size);
        canvasPosition->value = pixel_position_global;
        position2D->value = position;
        if (zox_has(e, Children)) {
            int2 pixel_size = zox_get_value(e, PixelSize)
            const Children *children = zox_get(e, Children)
            for (int j = 0; j < children->length; j++) set_element_position(world, children->value[j], pixel_position_global, pixel_size, canvas_size);
        }
        #ifdef debug_element_position_change_query
            zox_log("    - PixelPosition Updated [%lu]\n", e)
        #endif
    }
} zox_declare_system(ElementPositionSystem)

//   \done Make this instantaneous for children uis as well
//   \todo This needs to also account for child uis
//   \todo Change queries still not working, make a better test function with more components
/*if (!ecs_query_changed(change_query, NULL))
{
    return;
}*/
//! \todo Update this after getting a working example of change filters
/*#ifdef debug_element_position_change_query
    unsigned char did_change = ecs_query_changed(change_query, NULL);
#endif*/

/*void set_element_position(ecs_world_t *world, ecs_entity_t e, float2 parent_position, int2 parent_pixel_size, float2 canvas_size_f, float aspect_ratio) {
    if (e == 0 || !ecs_is_alive(world, e)) return; // || !ecs_is_valid(world, e)
    int2 pixel_position = int2_zero;
    if (zox_has(e, PixelPosition)) pixel_position = ecs_get(world, e, PixelPosition)->value;
    else pixel_position = get_line_element_mid_point(world, e);
    float2 anchor = float2_zero;    // should i pass this in from parent?
    if (zox_has(e, Anchor))  anchor = ecs_get(world, e, Anchor)->value;
    float2 real_position2D = get_ui_real_position2D_parent(pixel_position, anchor, parent_position, parent_pixel_size, canvas_size_f, aspect_ratio);
    if (zox_has(e, Position2D)) {
        Position2D *position2D = ecs_get_mut(world, e, Position2D);
        position2D->value = real_position2D;
        zox_modified(e, Position2D)
    }
    if (zox_has(e, CanvasPosition)) {
        CanvasPosition *canvasPosition = ecs_get_mut(world, e, CanvasPosition);
        canvasPosition->value = (int2) { ceil((real_position2D.x / aspect_ratio + 0.5f) * canvas_size_f.x), ((real_position2D.y + 0.5f) * canvas_size_f.y) };
        zox_modified(e, CanvasPosition)
    }
    set_line_element_real_position2D(world, e, real_position2D, canvas_size_f, aspect_ratio, pixel_position);
    if (zox_has(e, Children)) {
        int2 pixel_size = ecs_get(world, e, PixelSize)->value;
        const Children *children = ecs_get(world, e, Children);
        for (int i = 0; i < children->length; i++) set_element_position(world, children->value[i], real_position2D, pixel_size, canvas_size_f, aspect_ratio);
    }
}*/
