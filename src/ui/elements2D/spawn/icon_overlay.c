ecs_entity_t spawn_icon_overlay(ecs_world_t *world,
    const CanvasSpawnData canvas_data,
    const ParentSpawnData parent_data,
    ElementSpawnData element_data)
{
    zox_instance(element_data.prefab)
    zox_name("icon_overlay")
    set_element_spawn_data(world, e, canvas_data, parent_data, &element_data);
    // zox_set(e, RenderDisabled, { 1 })
    return e;
}