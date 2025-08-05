// #define DISABLE_AO
#define AO_CORNER_DARKNESS 0.25f
#define AO_EDGE_DARKNESS 0.5f

// Neighbor indices for each face and vertex: [vertex][0] = adjacent1, [vertex][1] = adjacent2
static const byte neighbor_indices[6][voxel_face_vertices_length][2] = {
    // Left face
    {
        { 2, 4 }, // (0,0,0): down, back
        { 2, 5 }, // (0,0,1): down, front
        { 3, 5 }, // (0,1,1): up, front
        { 3, 4 }  // (0,1,0): up, back
    },
    // Right face
    {
        { 2, 4 }, // (1,0,0): down, back
        { 2, 5 }, // (1,0,1): down, front
        { 3, 5 }, // (1,1,1): up, front
        { 3, 4 }  // (1,1,0): up, back
    },
    // Down face
    {
        { 0, 4 }, // (0,0,0): left, back
        { 0, 5 }, // (0,0,1): left, front
        { 1, 5 }, // (1,0,1): right, front
        { 1, 4 }  // (1,0,0): right, back
    },
    // Up face
    {
        { 0, 4 }, // (0,1,0): left, back
        { 0, 5 }, // (0,1,1): left, front
        { 1, 5 }, // (1,1,1): right, front
        { 1, 4 }  // (1,1,0): right, back
    },
    // Back face
    {
        { 0, 2 }, // (0,0,0): left, down
        { 0, 3 }, // (0,1,0): left, up
        { 1, 3 }, // (1,1,0): right, up
        { 1, 2 }  // (1,0,0): right, down
    },
    // Front face
    {
        { 0, 2 }, // (0,0,1): left, down
        { 0, 3 }, // (0,1,1): left, up
        { 1, 3 }, // (1,1,1): right, up
        { 1, 2 }  // (1,0,1): right, down
    }
};

// Compute AO darkening factor based on two neighbor states
float compute_ao_factor(byte neighbor1, byte neighbor2) {
    int solid_count = (neighbor1) + (neighbor2);
    if (solid_count == 2) {
        return AO_CORNER_DARKNESS; // Both solid
    }
    if (solid_count == 1) {
        return AO_EDGE_DARKNESS;   // One solid
    }
    return 1.0f; // No solid neighbors
}


void add_voxel_face_colors_ao(
    color_rgb_array_d* color_rgbs,
    color_rgb voxel_color,
    const byte direction,
    const byte* neighbors
) {
    /*float3 light_direction = float3_up;
    float light_intensity = float3_dot(face_normals[direction], light_direction);
    light_intensity = clampf(light_intensity, 0.1f, 1.0f);*/
    // 4 points for a voxel cube side
    for (byte a = 0; a < voxel_face_vertices_length; a++) {
        // Compute AO using neighbor states
        byte neighbor1 = neighbors[neighbor_indices[direction][a][0]];
        byte neighbor2 = neighbors[neighbor_indices[direction][a][1]];
        float ao_factor = compute_ao_factor(neighbor1, neighbor2);
        color_rgb c = voxel_color;
        // color_rgb_multiply_float(&c, light_intensity * 2.0f);
        color_rgb_multiply_float(&c, ao_factor * 2);
        add_to_color_rgb_array_d(color_rgbs, c);
    }
}