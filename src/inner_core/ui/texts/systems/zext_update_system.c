//! When ui text updates, spawn/destroy font entities
void ZextUpdateSystem(ecs_iter_t *it) {
    if (!it->ctx || !ecs_query_changed(it->ctx, NULL)) return;
    #ifdef zoxel_time_zext_update_system
        begin_timing()
    #endif
    ecs_world_t *world = it->world;
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
    const ZextData *zextDatas = ecs_field(it, ZextData, 3);
    const ZextSize *zextSizes = ecs_field(it, ZextSize, 4);
    const ZextPadding *zextPaddings = ecs_field(it, ZextPadding, 5);
    const Layer2D *layer2Ds = ecs_field(it, Layer2D, 6);
    const Position2D *position2Ds = ecs_field(it, Position2D, 7);
    const PixelSize *pixelSizes = ecs_field(it, PixelSize, 8);
    const ZextAlignment *zextAlignments = ecs_field(it, ZextAlignment, 9);
    Children *childrens = ecs_field(it, Children, 10);
    for (int i = 0; i < it->count; i++) {
        ZextDirty *zextDirty = &zextDirtys[i];
        if (zextDirty->value != 1) continue;
        ecs_entity_t e = it->entities[i];
        const ZextData *zextData = &zextDatas[i];
        const ZextSize *zextSize = &zextSizes[i];
        const ZextPadding *zextPadding = &zextPaddings[i];
        const Layer2D *layer2D = &layer2Ds[i];
        const Position2D *position2D = &position2Ds[i];
        const PixelSize *pixelSize = &pixelSizes[i];
        const ZextAlignment *zextAlignment = &zextAlignments[i];
        Children *children = &childrens[i];
        spawn_zext_zigels(world, e, children, zextData, zextSize->value, zextAlignment->value, zextPadding->value, layer2D->value, position2D->value, pixelSize->value);
        zextDirty->value = 0;
        #ifdef zoxel_debug_zigel_updates
            zoxel_log(" > zext is updating [%lu]\n", (long int) it->entities[i]);
        #endif
        #ifdef zoxel_time_zext_update_system
            did_do_timing()
        #endif
    }
    #ifdef zoxel_time_zext_update_system
        end_timing("    - zext_update_system")
    #endif
} zox_declare_system(ZextUpdateSystem)