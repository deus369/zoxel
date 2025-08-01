ecs_entity_t spawn_prefab_character3_skeleton(ecs_world_t *world,
    const ecs_entity_t prefab)
{
    const ecs_entity_t e = spawn_prefab_character3(world, prefab, zox_character_type_skeleton);
    zox_make_prefab(e)
    // zox_prefab_child(prefab)
    zox_prefab_name("character3_skeleton")
    zox_add_tag(e, Skeleton)
    zox_add_tag(e, SkeletonMesh)
#ifdef zox_paint_skeletons
    zox_add_tag(e, PaintedSkeleton)
#endif
    zox_prefab_set(e, Children, { 0, NULL });
    zox_prefab_set(e, BoneLinks, { 0, NULL });
    zox_prefab_set(e, BoneIndexes, { 0, NULL });
    return e;
}