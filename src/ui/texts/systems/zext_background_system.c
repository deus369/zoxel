// this needs textData with Mesh in one entity
void ZextBackgroundSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(ZextDirty, zextDirtys, 2)
    zox_field_in(TextData, textDatas, 3)
    zox_field_in(TextSize, textSizes, 4)
    zox_field_in(TextPadding, textPaddings, 5)
    zox_field_in(MeshAlignment, meshAlignments, 6)
    zox_field_in(CanvasLink, canvasLinks, 7)
    zox_field_out(PixelSize, pixelSizes, 8)
    zox_field_out(TextureSize, textureSizes, 9)
    zox_field_out(GenerateTexture, generateTextures, 10)
    zox_field_out(MeshVertices2D, meshVertices2Ds, 11)
    zox_field_out(MeshDirty, meshDirtys, 12)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ZextDirty, zextDirtys, zextDirty)
        if (zextDirty->value != zext_update_update) {
            continue;
        }
        zox_field_o(GenerateTexture, generateTextures, generateTexture)
        // if (generateTexture->value) return;
        zox_field_i(TextData, textDatas, textData)
        zox_field_i(TextSize, textSizes, textSize)
        zox_field_i(TextPadding, textPaddings, textPadding)
        zox_field_i(MeshAlignment, meshAlignments, meshAlignment)
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        zox_field_o(PixelSize, pixelSizes, pixelSize)
        zox_field_o(TextureSize, textureSizes, textureSize)
        zox_field_o(MeshVertices2D, meshVertices2Ds, meshVertices2D)
        zox_field_o(MeshDirty, meshDirtys, meshDirty)
        const int2 canvas_size = zox_get_value(canvasLink->value, PixelSize)
        const int2 size = calculate_zext_size(textData->value, textData->length, textSize->value, textPadding->value, default_line_padding);
        const float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
        const float2 size2D = (float2) { size.x / canvasSizef.y, size.y / canvasSizef.y };
        pixelSize->value = size;
        textureSize->value = size;
        set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(meshAlignment->value), 4, size2D);
        meshDirty->value = mesh_state_trigger;
        generateTexture->value = zox_generate_texture_trigger;
    }
} zox_declare_system(ZextBackgroundSystem)