// this needs zextData with Mesh in one entity

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
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value) return;
        GenerateTexture *generateTexture = &generateTextures[i];
        if (generateTexture->value) return;
        const ZextData *zextData = &zextDatas[i];
        const ZextSize *zextSize = &zextSizes[i];
        const ZextPadding *zextPadding = &zextPaddings[i];
        const MeshAlignment *meshAlignment = &meshAlignments[i];
        const CanvasLink *canvasLink = &canvasLinks[i];
        PixelSize *pixelSize = &pixelSizes[i];
        TextureSize *textureSize = &textureSizes[i];
        MeshVertices2D *meshVertices2D = &meshVertices2Ds[i];
        const PixelSize *canvasSize = ecs_get(world, canvasLink->value, PixelSize);
        int font_size = zextSize->value;
        int2 size = (int2) { font_size * zextData->length + zextPadding->value.x * 2, font_size + zextPadding->value.y * 2 };
        float2 canvasSizef = { (float) canvasSize->value.x, (float) canvasSize->value.y };
        float2 scale2D = (float2) { size.x / canvasSizef.y, size.y / canvasSizef.y };
        pixelSize->value = size;
        textureSize->value = size;
        const InitializeEntityMesh *initializeEntityMesh = ecs_get(world, it->entities[i], InitializeEntityMesh);
        if (initializeEntityMesh->value == 0) {
            set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(meshAlignment->value), 4, scale2D);
        }
        generateTexture->value = 1;
        meshDirty->value = 1;
    }
} zox_declare_system(ZextBackgroundUpdateSystem)

// todo: put a AutoResizeZextX tag on these, so it resizes the background of a text that updates
void ZextBackgroundUpdateSystem2(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
    const ZextData *zextDatas = ecs_field(it, ZextData, 3);
    const ZextSize *zextSizes = ecs_field(it, ZextSize, 4);
    const ZextPadding *zextPaddings = ecs_field(it, ZextPadding, 5);
    const MeshAlignment *meshAlignments = ecs_field(it, MeshAlignment, 6);
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 7);
    const ParentLink *parentLinks = ecs_field(it, ParentLink, 8);
    for (int i = 0; i < it->count; i++) {
        const ZextDirty *zextDirty = &zextDirtys[i];
        if (!zextDirty->value) continue;
        ecs_entity_t e = it->entities[i];
        const ParentLink *parentLink = &parentLinks[i];
        ecs_entity_t e2 = parentLink->value;
        MeshDirty *meshDirty = zox_get_mut(e2, MeshDirty)
        if (meshDirty->value) return;
        GenerateTexture *generateTexture = zox_get_mut(e2, GenerateTexture)
        if (generateTexture->value) return;
        PixelSize *pixelSize = zox_get_mut(e2, PixelSize)
        TextureSize *textureSize = zox_get_mut(e2, TextureSize)
        MeshVertices2D *meshVertices2D = zox_get_mut(e2, MeshVertices2D)
        const ZextData *zextData = &zextDatas[i];
        const ZextSize *zextSize = &zextSizes[i];
        const ZextPadding *zextPadding = &zextPaddings[i];
        const MeshAlignment *meshAlignment = &meshAlignments[i];
        const CanvasLink *canvasLink = &canvasLinks[i];
        const PixelSize *canvasSize = zox_get(canvasLink->value, PixelSize)
        float2 canvasSizef = int2_to_float2(canvasSize->value);
        int font_size = zextSize->value;
        int2 size = (int2) { font_size * zextData->length + zextPadding->value.x * 2, font_size + zextPadding->value.y * 2 };
        float2 scale2D = (float2) { size.x / canvasSizef.y, size.y / canvasSizef.y };
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
} zox_declare_system(ZextBackgroundUpdateSystem2)
