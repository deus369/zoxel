void chunk_position_fix2(float3 real_position, int3 *chunk_position) {
    if (real_position.x < 0) {
        chunk_position->x -= 1;
    }
    if (real_position.y < 0) {
        chunk_position->y -= 1;
    }
    if (real_position.z < 0) {
        chunk_position->z -= 1;
    }
}

int3 get_voxel_position(float3 real_position) {
    int3 voxel_position = (int3) {
        (int) floor(real_position.x),
        (int) floor(real_position.y),
        (int) floor(real_position.z) };
    return voxel_position;
}

int3 get_chunk_position(float3 real_position, int3 chunk_size) {
    int3 voxel_position = get_voxel_position(real_position);
    // zoxel_log("voxelpos [%ix%ix%i]\n", voxel_position.x, voxel_position.y, voxel_position.z);
    int3 chunk_position = (int3) { voxel_position.x / chunk_size.x, voxel_position.y / chunk_size.y, voxel_position.z / chunk_size.z };
    // zoxel_log("chunk_position [%ix%ix%i]\n", chunk_position.x, chunk_position.y, chunk_position.z);
    chunk_position_fix2(real_position, &chunk_position);
    return chunk_position;
}

int3 voxel_chunk_position(int3 chunk_position, int3 chunk_size) {
    int3 voxel_position = int3_multiply_int3(chunk_position, chunk_size);
    if (voxel_position.x < 0) {
        voxel_position.x += 1;
    }
    if (voxel_position.y < 0) {
        voxel_position.y += 1;
    }
    if (voxel_position.z < 0) {
        voxel_position.z += 1;
    }
    return voxel_position;
}

int3 voxel_chunk_position_xz(int3 chunk_position, int3 chunk_size) {
    int3 voxel_position = int3_multiply_int3(chunk_position, chunk_size);
    if (voxel_position.x < 0) {
        voxel_position.x += 1;
    }
    if (voxel_position.z < 0) {
        voxel_position.z += 1;
    }
    return voxel_position;
}

int3 get_local_position(int3 voxel_position, int3 chunk_position, int3 chunk_size) {
    voxel_position.x %= chunk_size.x;
    voxel_position.y %= chunk_size.y;
    voxel_position.z %= chunk_size.z;
    if (voxel_position.x < 0) {
        voxel_position.x += chunk_size.x;
    }
    if (voxel_position.y < 0) {
        voxel_position.y += chunk_size.y;
    }
    if (voxel_position.z < 0) {
        voxel_position.z += chunk_size.z;
    }
    return voxel_position;
}
    
    // float3 center_mesh_offset = (float3) { - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f };        
    /*return (int3) {
        global_voxel_position.x - chunk_position.x * chunk_size.x,
        global_voxel_position.y - chunk_position.y * chunk_size.y,
        global_voxel_position.z - chunk_position.z * chunk_size.z
    };*/
    /*if (voxel_position.x < 0) {
        voxel_position.x += 1;
    }
    if (voxel_position.y < 0) {
        voxel_position.y += 1;
    }
    if (voxel_position.z < 0) {
        voxel_position.z += 1;
    }*/
    /*return (int3) {
        (int) round(real_position.x - center_mesh_offset.x / 2.0f),
        (int) round(real_position.y - center_mesh_offset.y / 2.0f),
        (int) round(real_position.z - center_mesh_offset.z / 2.0f) };*/
    // round
    /*return (int3) {
        (int) floor(real_position.x),
        (int) floor(real_position.y),
        (int) floor(real_position.z) };*/

/*int3 get_chunk_position(float3 real_position, int3 chunk_size) {
    return (int3) {
        (int) round((real_position.x) / chunk_size.x),
        (int) round((real_position.y) / chunk_size.y),
        (int) round((real_position.z) / chunk_size.z) };
}*/
    // chunk_position_fix(chunk_position);

    /*int3 chunk_position_fix(int3 chunk_position) {
    if (chunk_position.x < 0) {
        chunk_position.x += 1;
    }
    if (chunk_position.y < 0) {
        chunk_position.y += 1;
    }
    if (chunk_position.z < 0) {
        chunk_position.z += 1;
    }
    return chunk_position;
}*/