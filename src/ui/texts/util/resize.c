void on_element_pixels_resized(ecs_world_t *world, const ecs_entity_t e, const int2 size, const byte mesh_alignment) {
    const ecs_entity_t canvas = zox_get_value(e, CanvasLink)
    if (!canvas) {
        zox_log("! canvas invalid in element [%s]\n", zox_get_name(e))
        return;
    }
    const float2 canvas_size = int2_to_float2(zox_gett_value(canvas, PixelSize));
    const float2 scale2D = (float2) { size.x / canvas_size.y, size.y / canvas_size.y };
    zox_get_muter(e, PixelSize, pixelSize)
    zox_get_muter(e, TextureSize, textureSize)
    zox_get_muter(e, MeshVertices2D, meshVertices2D)
    zox_get_muter(e, GenerateTexture, generateTexture)
    zox_get_muter(e, MeshDirty, meshDirty)
    pixelSize->value = size;
    textureSize->value = size;
    set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(mesh_alignment), 4, scale2D);
    generateTexture->value = zox_generate_texture_trigger;
    meshDirty->value = mesh_state_trigger;
}
