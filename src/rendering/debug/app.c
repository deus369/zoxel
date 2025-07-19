extern ecs_entity_t zox_canvases[16];
static inline int2 get_texture_size(ecs_world_t*, ecs_entity_t);

uint debug_label_app(ecs_world_t *world,
    const ecs_entity_t player,
    char *buffer,
    const uint size, uint index)
{
    zox_geter(main_app, CameraLinks, cameras)
    zox_geter_value(main_app, WindowSize, int2, viewport_size)

    index += snprintf(buffer + index, size - index, "App [%s]\n", zox_get_name(main_app));
    index += snprintf(buffer + index, size - index, "   - size [%ix%i]\n", viewport_size.x, viewport_size.y);
    index += snprintf(buffer + index, size - index, "   - cameras [%i]:\n", cameras->length);


    for (int i = 0; i < cameras->length; i++) {
        const ecs_entity_t camera = cameras->value[i];
        zox_geter_value(camera, ScreenDimensions, int2, camera_size)
        zox_geter_value(camera, ScreenPosition, int2, screen_position)
        zox_geter_value(camera, ScreenToCanvas, float4, screen_ratio)
        index += snprintf(buffer + index, size - index, "# %s\n", zox_get_name(camera));
        index += snprintf(buffer + index, size - index, "   - pos [%ix%i]\n", screen_position.x, screen_position.y);
        index += snprintf(buffer + index, size - index, "   - size [%ix%i]\n", camera_size.x, camera_size.y);
        index += snprintf(buffer + index, size - index, "   - ratio [%fx%fx%fx%f]\n", screen_ratio.x, screen_ratio.y, screen_ratio.z, screen_ratio.w);
    }

    // canvas
    // render texture size
    //zox_geter(local_realm, PlayerLinks, players)
    //zox_geter_value(players->value[0], CanvasLink, ecs_entity_t, canvas)
    ecs_entity_t canvas = zox_canvases[0];
    zox_geter_value(canvas, PixelSize, int2, canvas_size)
    zox_geter_value(canvas, ScreenToCanvas, float4, canvas_ratio)
    zox_geter(canvas, Children, canvas_children)
    index += snprintf(buffer + index, size - index, "Canvas [%s]\n", zox_get_name(canvas));
    index += snprintf(buffer + index, size - index, "   - size [%ix%i]\n", canvas_size.x, canvas_size.y);
    index += snprintf(buffer + index, size - index, "   - ratio [%fx%fx%fx%f]\n", canvas_ratio.x, canvas_ratio.y, canvas_ratio.z, canvas_ratio.w);
    index += snprintf(buffer + index, size - index, "   - children [%i]:\n", canvas_children->length);

    for (int i = 0; i < canvas_children->length; i++) {
        const ecs_entity_t element = canvas_children->value[i];
        if (!zox_has(element, RenderTexture)) {
            continue;
        }
        zox_geter_value(element, PixelSize, int2, element_size)
        // zox_geter_value(element, TextureSize, int2, texture_size)
        int2 texture_size = get_texture_size(world, element);
        zox_geter(element, MeshVertices2D, texture_verts)
        index += snprintf(buffer + index, size - index, "# %s\n", zox_get_name(element));
        index += snprintf(buffer + index, size - index, "   - size [%ix%i]\n", element_size.x, element_size.y);
        index += snprintf(buffer + index, size - index, "   - t_size [%ix%i]\n", texture_size.x, texture_size.y);
        /*for (int j = 0; j < texture_verts->length; j++) {
            float2 vert = texture_verts->value[j];
            index += snprintf(buffer + index, size - index, "       - v [%fx%f]\n", vert.x, vert.y);
        }*/
    }


    // ----?
    return index;
}