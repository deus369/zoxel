/*void delete_hierarchy(ecs_world_t *world, ecs_entity_t e) {
    if (ecs_has(world, e, Children)) {
        const Children *children = ecs_get(world, e, Children);
        for (int i = 0; i < children->length; i++) {
            delete_hierarchy(world, children->value[i]);
        }
    }
    ecs_delete(world, e);
}*/

// ECS_OBSERVER(world, on_parent_destroyed, EcsOnStore, Children);

void on_parent_destroyed(ecs_iter_t *it) {
    // zoxel_log("on_parent_destroyed [%i]\n", it->count);
    const Children *children = ecs_field(it, Children, 1);
    for (int i = 0; i < it->count; i++) {
        const Children *children2 = &children[i];
        for (int j = 0; j < children2->length; j++) {
            ecs_delete(it->world, children2->value[j]);
        }   
        // ecs_delete(it->world, it->entities[i]);
    }
}
