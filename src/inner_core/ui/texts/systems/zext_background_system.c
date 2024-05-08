// this needs zextData with Mesh in one entity
void ZextBackgroundSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ZextDirty, zextDirtys, 2)
    zox_field_in(ZextData, zextDatas, 3)
    zox_field_in(ZextSize, zextSizes, 4)
    zox_field_in(ZextPadding, zextPaddings, 5)
    zox_field_in(MeshAlignment, meshAlignments, 6)
    zox_field_in(CanvasLink, canvasLinks, 7)
    zox_field_out(PixelSize, pixelSizes, 8)
    zox_field_out(TextureSize, textureSizes, 9)
    zox_field_out(GenerateTexture, generateTextures, 10)
    zox_field_out(MeshVertices2D, meshVertices2Ds, 11)
    zox_field_out(MeshDirty, meshDirtys, 12)
    zox_field_in(InitializeEntityMesh, initializeEntityMeshs, 13)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ZextDirty, zextDirtys, zextDirty)
        if (!zextDirty->value) continue;
        zox_field_i_out(MeshDirty, meshDirtys, meshDirty)
        zox_field_i_out(GenerateTexture, generateTextures, generateTexture)
        if (generateTexture->value) return;
        zox_field_i_in(ZextData, zextDatas, zextData)
        zox_field_i_in(ZextSize, zextSizes, zextSize)
        zox_field_i_in(ZextPadding, zextPaddings, zextPadding)
        zox_field_i_in(MeshAlignment, meshAlignments, meshAlignment)
        zox_field_i_in(CanvasLink, canvasLinks, canvasLink)
        zox_field_i_in(InitializeEntityMesh, initializeEntityMeshs, initializeEntityMesh)
        zox_field_i_out(PixelSize, pixelSizes, pixelSize)
        zox_field_i_out(TextureSize, textureSizes, textureSize)
        zox_field_i_out(MeshVertices2D, meshVertices2Ds, meshVertices2D)
        const int2 canvas_size = zox_get_value(canvasLink->value, PixelSize)
        const int2 size = calculate_zext_size(zextData, zextSize->value, zextPadding->value);
        const float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
        const float2 scale2D = (float2) { size.x / canvasSizef.y, size.y / canvasSizef.y };
        pixelSize->value = size;
        textureSize->value = size;
        if (!initializeEntityMesh->value) set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(meshAlignment->value), 4, scale2D);
        generateTexture->value = 1;
        meshDirty->value = 1;
    }
} zox_declare_system(ZextBackgroundSystem)
