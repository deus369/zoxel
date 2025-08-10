ecs_entity_t spawn_prefab_hierarchy(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)
    zox_prefab_name("hierarchy")
    zox_add_tag(e, EditorElement)
    zox_add_tag(e, HierarchyUI)
    zox_prefab_set(e, HierarchyUIDirty, { 1 })
    return e;
}