//! When ui text updates, spawn/destroy font entities
void ZextUpdateSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        // printf("ZextUpdateSystem: changeQuery didn't change\n");
        return;
    }
    // printf("ZextUpdateSystem: changeQuery changed\n");
    // ecs_query_skip(it); //! Resetting doesn't cause table changes.
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
    const ZextData *zextDatas = ecs_field(it, ZextData, 3);
    const ZextSize *zextSizes = ecs_field(it, ZextSize, 4);
    const Layer2D *layer2Ds = ecs_field(it, Layer2D, 5);
    const Position2D *position2Ds = ecs_field(it, Position2D, 6);
    const PixelSize *pixelSizes = ecs_field(it, PixelSize, 7);
    Children *childrens = ecs_field(it, Children, 8);
    for (int i = 0; i < it->count; i++)
    {
        ZextDirty *zextDirty = &zextDirtys[i];
        if (zextDirty->value != 1)
        {
            // printf("ZextUpdateSystem: ZextDirty is not dirty.\n");
            continue;
        }
        zextDirty->value = 0;
        // printf("ZextUpdateSystem: ZextDirty is has updated.\n");
        ecs_entity_t e = it->entities[i];
        const ZextData *zextData = &zextDatas[i];
        const ZextSize *zextSize = &zextSizes[i];
        const Layer2D *layer2D = &layer2Ds[i];
        const Position2D *position2D = &position2Ds[i];
        const PixelSize *pixelSize = &pixelSizes[i];
        Children *children = &childrens[i];
        spawn_zext_zigels(world, e, children, zextData, zextSize->value, layer2D->value,
            position2D->value, pixelSize->value);
    }
}
zoxel_declare_system(ZextUpdateSystem)