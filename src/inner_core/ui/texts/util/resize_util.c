void on_element_pixels_resized(ecs_world_t *world, const ecs_entity_t e, const int2 size, const unsigned char mesh_alignment) {
    const ecs_entity_t canvas = zox_get_value(e, CanvasLink)
    const float2 canvas_size = int2_to_float2(zox_gett_value(canvas, PixelSize));
    const float2 scale2D = (float2) { size.x / canvas_size.y, size.y / canvas_size.y };
    PixelSize *pixelSize = zox_get_mut(e, PixelSize)
    TextureSize *textureSize = zox_get_mut(e, TextureSize)
    GenerateTexture *generateTexture = zox_get_mut(e, GenerateTexture)
    MeshVertices2D *meshVertices2D = zox_get_mut(e, MeshVertices2D)
    MeshDirty *meshDirty = zox_get_mut(e, MeshDirty)
    pixelSize->value = size;
    textureSize->value = size;
    set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(mesh_alignment), 4, scale2D);
    generateTexture->value = zox_generate_texture_trigger;
    meshDirty->value = mesh_state_trigger;
    zox_modified(e, PixelSize)
    zox_modified(e, TextureSize)
    zox_modified(e, GenerateTexture)
    zox_modified(e, MeshVertices2D)
    zox_modified(e, MeshDirty)
}
