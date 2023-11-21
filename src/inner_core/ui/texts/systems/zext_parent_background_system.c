// todo: put a AutoResizeZextX tag on these, so it resizes the background of a text that updates
void ZextParentBackgroundSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ZextDirty, zextDirtys, 2)
    zox_field_in(ZextData, zextDatas, 3)
    zox_field_in(ZextSize, zextSizes, 4)
    zox_field_in(ZextPadding, zextPaddings, 5)
    zox_field_in(MeshAlignment, meshAlignments, 6)
    zox_field_in(CanvasLink, canvasLinks, 7)
    zox_field_in(ParentLink, parentLinks, 8)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ZextDirty, zextDirtys, zextDirty)
        if (!zextDirty->value) continue;
        // zox_log("   > updating parent background of label [%lu]\n", it->entities[i]);
        zox_field_i_in(ParentLink, parentLinks, parentLink)
        ecs_entity_t e2 = parentLink->value;
        // if (!zox_has(e2, ZextLabel)) zox_logg("       > zext label not on parent\n")
        if (!zox_has(e2, ZextLabel)) continue;
        MeshDirty *meshDirty = zox_get_mut(e2, MeshDirty)
        if (meshDirty->value) return;
        GenerateTexture *generateTexture = zox_get_mut(e2, GenerateTexture)
        if (generateTexture->value) return;
        zox_field_i_in(ZextData, zextDatas, zextData)
        zox_field_i_in(ZextSize, zextSizes, zextSize)
        zox_field_i_in(ZextPadding, zextPaddings, zextPadding)
        zox_field_i_in(MeshAlignment, meshAlignments, meshAlignment)
        zox_field_i_in(CanvasLink, canvasLinks, canvasLink)
        PixelSize *pixelSize = zox_get_mut(e2, PixelSize)
        TextureSize *textureSize = zox_get_mut(e2, TextureSize)
        MeshVertices2D *meshVertices2D = zox_get_mut(e2, MeshVertices2D)
        const int2 canvas_size = zox_get_value(canvasLink->value, PixelSize)
        const float2 canvasSizef = int2_to_float2(canvas_size);
        const int font_size = zextSize->value;
        const int2 size = (int2) { font_size * zextData->length + zextPadding->value.x * 2, font_size + zextPadding->value.y * 2 };
        const float2 scale2D = (float2) { size.x / canvasSizef.y, size.y / canvasSizef.y };
        // zox_log(" > zext background [%i to %i]\n", pixelSize->value.x, size.x)
        pixelSize->value = size;
        textureSize->value = size;
        set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(meshAlignment->value), 4, scale2D);
        generateTexture->value = 1;
        meshDirty->value = 1;
        zox_modified(e2, PixelSize)
        zox_modified(e2, TextureSize)
        zox_modified(e2, MeshVertices2D)
        zox_modified(e2, MeshDirty)
        zox_modified(e2, GenerateTexture)
    }
    // zox_log("  > uppdating background of label [%i]\n", it->count);
} zox_declare_system(ZextParentBackgroundSystem)
