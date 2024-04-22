void on_element_pixels_resized(ecs_world_t *world, ecs_entity_t e, const int2 size, unsigned char mesh_alignment) {
    const CanvasLink *canvasLink = zox_get(e, CanvasLink)
    PixelSize *pixelSize = zox_get_mut(e, PixelSize)
    TextureSize *textureSize = zox_get_mut(e, TextureSize)
    GenerateTexture *generateTexture = zox_get_mut(e, GenerateTexture)
    MeshVertices2D *meshVertices2D = zox_get_mut(e, MeshVertices2D)
    MeshDirty *meshDirty = zox_get_mut(e, MeshDirty)
    const float2 canvas_size = int2_to_float2(zox_gett_value(canvasLink->value, PixelSize));
    const float2 scale2D = (float2) { size.x / canvas_size.y, size.y / canvas_size.y };
    pixelSize->value = size;
    textureSize->value = size;
    set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(mesh_alignment), 4, scale2D);
    generateTexture->value = 1;
    meshDirty->value = 1;
    zox_modified(e, PixelSize)
    zox_modified(e, TextureSize)
    zox_modified(e, GenerateTexture)
    zox_modified(e, MeshVertices2D)
    zox_modified(e, MeshDirty)
}

void ZextParentBackgroundSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ZextDirty, zextDirtys, 2)
    zox_field_in(ZextData, zextDatas, 3)
    zox_field_in(ZextSize, zextSizes, 4)
    zox_field_in(ZextPadding, zextPaddings, 5)
    zox_field_in(MeshAlignment, meshAlignments, 6)
    zox_field_in(ParentLink, parentLinks, 8)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ZextDirty, zextDirtys, zextDirty)
        if (!zextDirty->value) continue;
        zox_field_i_in(ParentLink, parentLinks, parentLink)
        ecs_entity_t e2 = parentLink->value;
        if (!zox_has(e2, ZextLabel)) continue;
        MeshDirty *meshDirty = zox_get_mut(e2, MeshDirty)
        if (meshDirty->value) return;
        GenerateTexture *generateTexture = zox_get_mut(e2, GenerateTexture)
        if (generateTexture->value) return;
        zox_field_i_in(ZextData, zextDatas, zextData)
        zox_field_i_in(ZextSize, zextSizes, zextSize)
        zox_field_i_in(ZextPadding, zextPaddings, zextPadding)
        zox_field_i_in(MeshAlignment, meshAlignments, meshAlignment)
        const int font_size = zextSize->value;
        const int2 size = (int2) { font_size * zextData->length + zextPadding->value.x * 2, font_size + zextPadding->value.y * 2 };
        on_element_pixels_resized(world, e2, size, meshAlignment->value);
    }
} zox_declare_system(ZextParentBackgroundSystem)
