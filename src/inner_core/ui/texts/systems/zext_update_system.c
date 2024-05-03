//! When ui text updates, spawn/destroy font entities
void ZextUpdateSystem(ecs_iter_t *it) {
    zox_change_check()
    zox_iter_world()
    zox_field_in(ZextData, zextDatas, 2)
    zox_field_in(ZextSize, zextSizes, 3)
    zox_field_in(ZextPadding, zextPaddings, 4)
    zox_field_in(Layer2D, layer2Ds, 5)
    zox_field_in(CanvasPosition, canvasPositions, 6)
    zox_field_in(PixelSize, pixelSizes, 7)
    zox_field_in(MeshAlignment, meshAlignments, 8)
    zox_field_in(RenderDisabled, renderDisableds, 9)
    zox_field_out(ZextDirty, zextDirtys, 10)
    zox_field_out(Children, childrens, 11)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(ZextDirty, zextDirtys, zextDirty)
        if (!zextDirty->value) continue;
        zox_field_i_in(ZextData, zextDatas, zextData)
        zox_field_i_out(Children, childrens, children)
        if (is_zext_updating(world, children)) continue;
        zox_field_e()
        const ecs_entity_t canvas = get_root_canvas(world, e);
        zox_field_i_in(ZextSize, zextSizes, zextSize)
        zox_field_i_in(ZextPadding, zextPaddings, zextPadding)
        zox_field_i_in(Layer2D, layer2Ds, layer2D)
        zox_field_i_in(CanvasPosition, canvasPositions, canvasPosition)
        zox_field_i_in(PixelSize, pixelSizes, pixelSize)
        zox_field_i_in(MeshAlignment, meshAlignments, meshAlignment)
        zox_field_i_in(RenderDisabled, renderDisableds, renderDisabled)
        spawn_zext_zigels(world, e, canvas, children, zextData, zextSize->value, meshAlignment->value, zextPadding->value, layer2D->value, canvasPosition->value, pixelSize->value, renderDisabled->value);
        zextDirty->value = 0; // 2;
#ifdef zoxel_debug_zigel_updates
        zox_log(" > zext is updating [%lu] [%i]\n", it->entities[i], zextData->length)
#endif
    }
} zox_declare_system(ZextUpdateSystem)
