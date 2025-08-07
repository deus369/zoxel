entity spawn_prefab_vox_generated(ecs *world, const entity prefab) {
    zox_prefab_child(prefab)
    zox_prefab_set(e, GenerateVox, { zox_dirty_trigger });
    zox_prefab_set(e, Color, { color_white })
    return e;
}

entity spawn_vox_generated(ecs *world, const entity prefab, const color vox_color) {
    zox_instance(prefab)
    zox_set(e, Color, { vox_color })
    return e;
}

entity spawn_vox_generated_invisible(ecs *world, const entity prefab, const color vox_color) {
    zox_instance(prefab)
    zox_set(e, Color, { vox_color })
    zox_set(e, RenderDisabled, { 1 })
    return e;
}