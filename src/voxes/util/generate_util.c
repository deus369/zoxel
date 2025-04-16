void vox_outlines(ChunkOctree *chunk, const byte target_depth, byte3 size, const byte black_voxel) {
    byte3 voxel_position;
    for (voxel_position.x = 0; voxel_position.x < size.x; voxel_position.x++) {
        for (voxel_position.y = 0; voxel_position.y < size.y; voxel_position.y++) {
            for (voxel_position.z = 0; voxel_position.z < size.z; voxel_position.z++) {
                byte on_edges = byte3_on_edges(voxel_position, size);
                if (on_edges) {
                    // skip if air
                    byte3 temp_position_2 = voxel_position;
                    if (get_octree_voxel(chunk, &temp_position_2, target_depth) == 0) continue;
                    byte2 set_voxel = (byte2) { black_voxel, target_depth };
                    byte3 temp_position = voxel_position;
                    set_octree_voxel(chunk, &temp_position, &set_voxel, 0);
                }
            }
        }
    }
}

void noise_vox(ChunkOctree *chunk, const byte target_depth, const byte3 size, const byte2 voxel_range, const byte black_voxel) {
    byte3 voxel_position;
    for (voxel_position.x = 0; voxel_position.x < size.x; voxel_position.x++) {
        for (voxel_position.y = 0; voxel_position.y < size.y; voxel_position.y++) {
            for (voxel_position.z = 0; voxel_position.z < size.z; voxel_position.z++) {
                byte3 temp_position = voxel_position;
                if (get_octree_voxel(chunk, &temp_position, target_depth) == black_voxel) continue;
                const int rando = rand() % 1000;
                if (rando > 300) continue;
                const byte voxel = voxel_range.x + rand() % (voxel_range.y - voxel_range.x);
                byte2 set_voxel = (byte2) { voxel, target_depth };
                byte3 node_position = voxel_position;
                set_octree_voxel(chunk, &node_position, &set_voxel, 0);
            }
        }
    }
}

void vox_rubble(ChunkOctree *chunk, const byte target_depth, const byte3 size, const byte2 voxel_range, const int rubble_count, const byte rubble_height) {
    byte3 voxel_position;
    for (int j = 0; j < rubble_count; j++) {
        voxel_position.x = rand() % size.x;
        voxel_position.z = rand() % size.y;
        for (int k = 0; k < size.y; k++) {
            voxel_position.y = k;
            byte3 node_position = voxel_position;
            if (get_octree_voxel(chunk, &node_position, target_depth) == 0) {
                break;
            }
        }
        if (voxel_position.y > rubble_height) {
            continue;
        }
        byte voxel = voxel_range.x + rand() % (voxel_range.y - voxel_range.x);
        byte2 set_voxel = (byte2) { voxel, target_depth };
        byte3 node_position = voxel_position;
        set_octree_voxel(chunk, &node_position, &set_voxel, 0);
    }
}
