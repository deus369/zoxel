ecs_entity_t fps_display_prefab;

ecs_entity_t spawn_prefab_fps_display(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, label_prefab);
    ecs_add_id(world, e, EcsPrefab);
    ecs_set_name(world, e, "prefab_fps_display");
    zoxel_add_tag(world, e, FPSDisplay);
    zoxel_set(world, e, FPSDisplayTicker, { 0 });
    ecs_remove(world, e, AnimateZext);
    fps_display_prefab = e;
    return e;
}

ecs_entity_t spawn_fps_display(ecs_world_t *world, ecs_entity_t parent, int font_size)
{
    int textLength = 3;
    int2 pixel_size = (int2) { font_size * textLength, font_size };
    float2 anchor = { 1.0f, 1.0f };
    int2 position = { - pixel_size.x / 2, - font_size / 2 };
    int layer = 1;
    const PixelSize *parent_pixel_size = ecs_get(world, parent, PixelSize);
    ecs_entity_t e = spawn_label(world, fps_display_prefab, parent, position, anchor, "FPS", font_size, layer,
        (float2) { }, parent_pixel_size->value);
    return e;
}