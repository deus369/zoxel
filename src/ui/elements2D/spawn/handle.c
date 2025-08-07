entity spawn_handle(ecs *world,
    const CanvasSpawnData canvas_data,
    const ParentSpawnData parent_data,
    ElementSpawnData element_data)
{
    zox_instance(element_data.prefab)
    zox_name("handle")
    set_element_spawn_data(world, e, canvas_data, parent_data, &element_data);
    zox_set(e, DraggableLimits, { (int4) {
        -(parent_data.size.x / 2) + (element_data.size.x / 2),
        (parent_data.size.x / 2) - (element_data.size.x / 2),
        0,
        0
    } })
    return e;
}