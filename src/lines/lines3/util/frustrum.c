void draw_frustum(ecs_world_t *world, float3 *frustum, const color_rgb debug_color) {
    // const color_rgb plane_color = (color_rgb) { 255, 125, 55 };
    const color_rgb near_plane_color = debug_color; // (color_rgb) { 255, 22, 22 };
    const color_rgb far_plane_color = debug_color; // (color_rgb) { 205, 22, 22 };
    const color_rgb side_color = debug_color; // (color_rgb) { 233, 55, 55 };
    // draw near plane
    render_line3D(world, frustum[0], frustum[1], near_plane_color);
    render_line3D(world, frustum[1], frustum[2], near_plane_color);
    render_line3D(world, frustum[2], frustum[3], near_plane_color);
    render_line3D(world, frustum[3], frustum[0], near_plane_color);
    // draw far plane
    render_line3D(world, frustum[4], frustum[5], far_plane_color);
    render_line3D(world, frustum[5], frustum[6], far_plane_color);
    render_line3D(world, frustum[6], frustum[7], far_plane_color);
    render_line3D(world, frustum[7], frustum[4], far_plane_color);
    // draw far plane
    render_line3D(world, frustum[0], frustum[4], side_color);
    render_line3D(world, frustum[1], frustum[5], side_color);
    render_line3D(world, frustum[2], frustum[6], side_color);
    render_line3D(world, frustum[3], frustum[7], side_color);
}