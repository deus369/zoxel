ecs_entity_t spawn_prefab_character3_skeleton(ecs_world_t *world,
    const ecs_entity_t prefab)
{
    const ecs_entity_t e = spawn_prefab_character3(world, prefab, zox_character_type_skeleton);
    zox_make_prefab(e)
    // zox_prefab_child(prefab)
    zox_prefab_name("character3_skeleton")
    zox_add_tag(e, Skeleton)
    zox_add_tag(e, SkeletonMesh)
    zox_prefab_add(e, Children)
    zox_prefab_add(e, BoneLinks)
    zox_prefab_add(e, BoneIndexes)
#ifdef zox_paint_skeletons
    zox_add_tag(e, PaintedSkeleton)
#endif
    return e;
}