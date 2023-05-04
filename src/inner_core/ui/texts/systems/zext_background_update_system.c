void ZextBackgroundUpdateSystem(ecs_iter_t *it) {
    const ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
    const ZextData *zextDatas = ecs_field(it, ZextData, 3);
    const ZextSize *zextSizes = ecs_field(it, ZextSize, 4);
    const ZextPadding *zextPaddings = ecs_field(it, ZextPadding, 5);
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 6);
    PixelSize *pixelSizes = ecs_field(it, PixelSize, 7);
    TextureSize *textureSizes = ecs_field(it, TextureSize, 8);
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 9);
    MeshVertices2D *meshVertices2Ds = ecs_field(it, MeshVertices2D, 10);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 11);
    for (int i = 0; i < it->count; i++) {
        const ZextDirty *zextDirty = &zextDirtys[i];
        if (zextDirty->value != 1) {
            continue;
        }
        const ZextData *zextData = &zextDatas[i];
        const ZextSize *zextSize = &zextSizes[i];
        const CanvasLink *canvasLink = &canvasLinks[i];
        const ZextPadding *zextPadding = &zextPaddings[i];
        PixelSize *pixelSize = &pixelSizes[i];
        TextureSize *textureSize = &textureSizes[i];
        GenerateTexture *generateTexture = &generateTextures[i];
        MeshVertices2D *meshVertices2D = &meshVertices2Ds[i];
        MeshDirty *meshDirty = &meshDirtys[i];
        const PixelSize *canvasSize = ecs_get(world, canvasLink->value, PixelSize);
        int font_size = zextSize->value;
        float2 canvasSizef = { (float) canvasSize->value.x, (float) canvasSize->value.y };
        // int2 text_padding = ; // (int2) { (int) (font_size * 0.3f), (int) (font_size * 0.3f) };
        // set texture
        pixelSize->value = (int2) { font_size * zextData->length + zextPadding->value.x * 2, font_size + zextPadding->value.y * 2 };
        textureSize->value = pixelSize->value;
        generateTexture->value = 1;
        // set mesh
        float2 scale2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
        for (int i = 0; i < meshVertices2D->length; i++) {
            meshVertices2D->value[i] = square_vertices_left_aligned[i];
            float2_multiply_float2_p(&meshVertices2D->value[i], scale2D);
        }
        meshDirty->value = 1;
        // zoxel_log(" > zoxel label background is updating [%i]\n", zextData->length);
    }
}
zoxel_declare_system(ZextBackgroundUpdateSystem)