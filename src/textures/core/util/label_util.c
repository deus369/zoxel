extern void add_entity_to_labels(ecs_world_t *world, const ecs_entity_t e, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, const int tree_level);

void add_to_labels_textures(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int tree_level) {
    if (!(zox_valid(e) && zox_has(e, Textures))) {
        return;
    }
    tree_level++;
    const Textures *component = zox_get(e, Textures)
    for (int i = 0; i < component->length; i++) {
        ecs_entity_t texture = component->value[i];
        add_entity_to_labels(world, texture, labels, entities, tree_level);
        // add_entity_children_to_labels(world, component->value[i], labels, entities, tree_level);
    }
}
