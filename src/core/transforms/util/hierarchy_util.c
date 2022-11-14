void delete_hierarchy(ecs_world_t *world, ecs_entity_t e)
{
    ecs_delete(world, e);
    if (ecs_has(world, e, Children))
    {
        const Children *children = ecs_get(world, e, Children);
        for (int i = 0; i < children->length; i++)
        {
            delete_hierarchy(world, children->value[i]);
        }
    }
}