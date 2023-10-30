//! When ui text updates, spawn/destroy font entities
void ZextUpdateSystem(ecs_iter_t *it) {
    if (!it->ctx || !ecs_query_changed(it->ctx, NULL)) return;
    ecs_world_t *world = it->world;
    const ZextData *zextDatas = ecs_field(it, ZextData, 2);
    const ZextSize *zextSizes = ecs_field(it, ZextSize, 3);
    const ZextPadding *zextPaddings = ecs_field(it, ZextPadding, 4);
    const Layer2D *layer2Ds = ecs_field(it, Layer2D, 5);
    const Position2D *position2Ds = ecs_field(it, Position2D, 6);
    const PixelSize *pixelSizes = ecs_field(it, PixelSize, 7);
    const MeshAlignment *meshAlignments = ecs_field(it, MeshAlignment, 8);
    const RenderDisabled *renderDisableds = ecs_field(it, RenderDisabled, 9);
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 10);
    Children *childrens = ecs_field(it, Children, 11);
    for (int i = 0; i < it->count; i++) {
        ZextDirty *zextDirty = &zextDirtys[i];
        if (zextDirty->value == 2) {
            zextDirty->value = 0;
            continue;
        }
        if (!zextDirty->value) continue;
        Children *children = &childrens[i];
        if (is_zext_updating(world, children)) continue;
        ecs_entity_t e = it->entities[i];
        const ZextData *zextData = &zextDatas[i];
        const ZextSize *zextSize = &zextSizes[i];
        const ZextPadding *zextPadding = &zextPaddings[i];
        const Layer2D *layer2D = &layer2Ds[i];
        const Position2D *position2D = &position2Ds[i];
        const PixelSize *pixelSize = &pixelSizes[i];
        const MeshAlignment *meshAlignment = &meshAlignments[i];
        const RenderDisabled *renderDisabled = &renderDisableds[i];
        spawn_zext_zigels(world, e, children, zextData, zextSize->value, meshAlignment->value, zextPadding->value, layer2D->value, position2D->value, pixelSize->value, renderDisabled->value);
        zextDirty->value = 2;
        #ifdef zoxel_debug_zigel_updates
            zox_log(" > zext is updating [%lu] [%i]\n", it->entities[i], zextData->length)
        #endif
    }
} zox_declare_system(ZextUpdateSystem)
