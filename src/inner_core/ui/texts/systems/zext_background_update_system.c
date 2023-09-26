void ZextBackgroundUpdateSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
    const ZextData *zextDatas = ecs_field(it, ZextData, 3);
    const ZextSize *zextSizes = ecs_field(it, ZextSize, 4);
    const ZextPadding *zextPaddings = ecs_field(it, ZextPadding, 5);
    const MeshAlignment *meshAlignments = ecs_field(it, MeshAlignment, 6);
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 7);
    PixelSize *pixelSizes = ecs_field(it, PixelSize, 8);
    TextureSize *textureSizes = ecs_field(it, TextureSize, 9);
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 10);
    MeshVertices2D *meshVertices2Ds = ecs_field(it, MeshVertices2D, 11);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 12);
    for (int i = 0; i < it->count; i++) {
        const ZextDirty *zextDirty = &zextDirtys[i];
        if (!zextDirty->value) continue;
        const ZextData *zextData = &zextDatas[i];
        const ZextSize *zextSize = &zextSizes[i];
        const ZextPadding *zextPadding = &zextPaddings[i];
        const MeshAlignment *meshAlignment = &meshAlignments[i];
        const CanvasLink *canvasLink = &canvasLinks[i];
        PixelSize *pixelSize = &pixelSizes[i];
        TextureSize *textureSize = &textureSizes[i];
        GenerateTexture *generateTexture = &generateTextures[i];
        MeshVertices2D *meshVertices2D = &meshVertices2Ds[i];
        MeshDirty *meshDirty = &meshDirtys[i];
        const PixelSize *canvasSize = ecs_get(world, canvasLink->value, PixelSize);
        int font_size = zextSize->value;
        pixelSize->value = (int2) { font_size * zextData->length + zextPadding->value.x * 2, font_size + zextPadding->value.y * 2 };
        textureSize->value = pixelSize->value;
        const InitializeEntityMesh *initializeEntityMesh = ecs_get(world, it->entities[i], InitializeEntityMesh);
        if (initializeEntityMesh->value == 0) {
            float2 canvasSizef = { (float) canvasSize->value.x, (float) canvasSize->value.y };
            float2 scale2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
            set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(meshAlignment->value), 4, scale2D);
            // zoxel_log(" > mesh scale 2: %fx%f - pixel [%ix%i] - canvas [%ix%i]\n", scale2D.x, scale2D.y, pixelSize->value.x, pixelSize->value.y, canvasSize->value.x, canvasSize->value.y);
        }
        generateTexture->value = 1;
        meshDirty->value = 1;
        // zoxel_log(" >  [%lu] zext_background_update_system: scale2D [%fx%f]\n", it->entities[i], scale2D.x, scale2D.y);
        // zoxel_log(" > zoxel label background is updating [%i]\n", zextData->length);
    }
} zox_declare_system(ZextBackgroundUpdateSystem)