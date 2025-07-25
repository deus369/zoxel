ecs_entity_t spawn_prefab_crosshair(ecs_world_t *world,
    const ecs_entity_t prefab)
{
    zox_prefab_child(prefab)
    zox_set(e, HitType, { 0 })
    zox_set(e, FrameCorner, { crosshair_corner })
    zox_set(e, OutlineThickness, { crosshair_thickness })
    zox_set(e, Color, { empty_color })
    zox_set(e, OutlineColor, { crosshair_air })
    return e;
}

ecs_entity_t spawn_crosshair(ecs_world_t *world,
    const CanvasSpawnData canvas_data,
    const ParentSpawnData parent_data,
    ElementSpawnData element_data)
{
    zox_instance(element_data.prefab)
    zox_name("crosshair")
    set_element_spawn_data(world, e, canvas_data, parent_data, &element_data);
    local_crosshair = e;
    return e;
}
