ecs_entity_t spawn_prefab_vox_file(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_vox_file")
    zox_add_tag(e, Vox)
    zox_prefab_add(e, ChunkSize)
    zox_prefab_add(e, ChunkOctree)
    zox_prefab_add(e, ColorRGBs)
    return e;
}

ecs_entity_t spawn_vox_file(ecs_world_t *world, const ecs_entity_t prefab, const vox_file *data) {
    zox_instance(prefab)
    set_vox_file(world, e, data);
#ifdef zox_disable_io_voxes
    zox_delete(e)
    return 0;
#endif
    return e;
}
