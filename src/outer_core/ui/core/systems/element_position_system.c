
void set_element_position(ecs_world_t *world, ecs_entity_t e,
    int2 canvas_size, float2 canvas_size_f, float aspect_ratio,
    float2 parent_position2D, int2 parent_pixel_size)
{
    int2 pixel_position = ecs_get(world, e, PixelPosition)->value;
    float2 anchor = ecs_get(world, e, Anchor)->value;
    float2 real_position = get_ui_real_position2D_parent(
        pixel_position, anchor,
        parent_position2D, parent_pixel_size,
        canvas_size, canvas_size_f, aspect_ratio);
    ecs_set(world, e, Position2D, { real_position });
    int2 global_pixel_position = (int2) {
        ceil((real_position.x / aspect_ratio + 0.5f) * canvas_size_f.x),
        ((real_position.y + 0.5f) * canvas_size_f.y) };
    ecs_set(world, e, CanvasPixelPosition, { global_pixel_position });
    // set all children as well.
    if (ecs_has(world, e, Children))
    {
        const Children *children = ecs_get(world, e, Children);
        for (int i = 0; i < children->length; i++)
        {
            set_element_position(world, children->value[i],
                canvas_size, canvas_size_f, aspect_ratio,
                real_position, pixel_position);
        }
    }
}

//! Sets real position when pixel position updates
/**
*   \done Make this instantaneous for children uis as well.
*   \todo This needs to also account for child uis
*   \todo Change queries still not working, make a better test function with more components.
*/
void ElementPositionSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    ecs_iter_t change_iter = ecs_query_iter(it->world, changeQuery);
    while (ecs_query_next(&change_iter))
    {
        if (change_iter.table != it->table)
        {
            ecs_query_skip(&change_iter);
        }
    }
    /*if (!ecs_query_changed(changeQuery, NULL))
    {
        return;
    }*/
    //! \todo Update this after getting a working example of change filters
    /*#ifdef debug_element_position_change_query
        bool did_change = ecs_query_changed(changeQuery, NULL);
    #endif*/
    ecs_world_t *world = it->world;
    const PixelPosition *pixelPositions = ecs_field(it, PixelPosition, 2);
    const ParentLink *parentLinks = ecs_field(it, ParentLink, 3);
    const Anchor *anchors = ecs_field(it, Anchor, 4);
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 5);
    Position2D *position2Ds = ecs_field(it, Position2D, 6);
    CanvasPixelPosition *canvasPixelPositions = ecs_field(it, CanvasPixelPosition, 7);
    for (int i = 0; i < it->count; i++)
    {
        ecs_entity_t e = it->entities[i];
        const PixelPosition *pixelPosition = &pixelPositions[i];
        const ParentLink *parentLink = &parentLinks[i];
        const Anchor *anchor = &anchors[i];
        const CanvasLink *canvasLink = &canvasLinks[i];
        if (!ecs_is_valid(world, canvasLink->value))
        {
            // printf("canvasLink not valid: %lu\n", (long int) e);
            continue;
        }
        if (parentLink->value != canvasLink->value)
        {
            continue;
        }
        int2 canvas_size = ecs_get(world, canvasLink->value, PixelSize)->value;
        float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
        float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
        // printf("canvas_size [%ix%i]\n", canvas_size.x, canvas_size.y);
        Position2D *position2D = &position2Ds[i];
        CanvasPixelPosition *canvasPixelPosition = &canvasPixelPositions[i];
        position2D->value = get_ui_real_position2D_canvas(pixelPosition->value, anchor->value, canvas_size);
        canvasPixelPosition->value = (int2) {
            ceil((position2D->value.x / aspect_ratio + 0.5f) * canvas_size_f.x),
            ((position2D->value.y + 0.5f) * canvas_size_f.y) };
        #ifdef debug_element_position_change_query
            printf("    - PixelPosition Updated [%lu]\n", (long int) e);
        #endif
        if (ecs_has(world, e, Children))
        {
            int2 pixel_size = ecs_get(world, e, PixelSize)->value;
            const Children *children = ecs_get(world, e, Children);
            for (int i = 0; i < children->length; i++)
            {
                set_element_position(world, children->value[i],
                    canvas_size, canvas_size_f, aspect_ratio,
                    position2D->value, pixel_size);
            }
        }
    }
}
ECS_SYSTEM_DECLARE(ElementPositionSystem);

    /*if (anchor.x == 0.5f && anchor.y == 1.0f)
    {
        printf("    - set_element_position [%ix%i] anchor [%fx%f] \n", (long int) e,
            anchor.x, anchor.y);
        printf("        - pixel_position [%ix%i] \n",
            pixel_position.x, pixel_position.y);
        printf("        - real_position [%fx%f] \n",
            real_position.x, real_position.y);
        printf("        - parent_pixel_position [%ix%i] \n",
            parent_pixel_position.x, parent_pixel_position.y);
        printf("        - parent_position2D [%fx%f] \n",
            parent_position2D.x, parent_position2D.y);
        printf("        - local_position [%fx%f] \n",
            (parent_position2D.x - real_position.x), (parent_position2D.y - real_position.y));
    }*/