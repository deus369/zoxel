// #define zox_time_frame_texture_system
void FrameTextureSystem(ecs_iter_t *it) {
    if (!it->ctx || !ecs_query_changed(it->ctx, NULL)) return;
#ifdef zox_time_frame_texture_system
    begin_timing()
#endif
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 2);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 3);
    const Color *colors = ecs_field(it, Color, 4);
    const OutlineThickness *outlineThicknesss = ecs_field(it, OutlineThickness, 5);
    const FrameCorner *frameEdges = ecs_field(it, FrameCorner, 6);
    TextureData *textures = ecs_field(it, TextureData, 7);
    TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 8);
    for (int i = 0; i < it->count; i++) {
        GenerateTexture *generateTexture = &generateTextures[i];
        if (!generateTexture->value) continue;
        TextureDirty *textureDirty = &textureDirtys[i];
        if (textureDirty->value) continue;
        const TextureSize *textureSize = &textureSizes[i];
        const Color *color2 = &colors[i];
        const OutlineThickness *outlineThickness = &outlineThicknesss[i];
        const FrameCorner *frameEdge = &frameEdges[i];
        TextureData *textureData = &textures[i];
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        generate_frame_texture(textureData, textureSize, color2, outlineThickness->value, frameEdge->value);
        generateTexture->value = 0;
        textureDirty->value = 1;
#ifdef zox_time_frame_texture_system
        did_do_timing()
#endif
        // zox_log("   > texture (frame) generated [%i] - %lu - %f\n", i, it->entities[i], zox_current_time)
    }
#ifdef zox_time_frame_texture_system
    end_timing("    - frame_texture_system")
#endif
} zox_declare_system(FrameTextureSystem)
