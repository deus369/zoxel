void fill_new_octree(VoxelNode* node, const byte voxel, byte depth) {
    if (!node) {
        return;
    }
    node->value = voxel;
    if (depth) {
        depth--;
        open_new_VoxelNode(node);
        if (!node) {
            zox_log_error("[fill_new_octree] node failed to open");
            return; // sometimes they fail
        }
        VoxelNode* kids = get_children_VoxelNode(node);
        for (byte i = 0; i < octree_length; i++) {
            fill_new_octree(&kids[i], voxel, depth);
        }
    }
}

void random_fill_octree(VoxelNode* node, byte voxel, byte depth) {
    node->value = voxel;
    if (depth > 0) {
        depth--;
        open_new_VoxelNode(node);
        VoxelNode* kids = get_children_VoxelNode(node);
        for (int i = 0; i < octree_length; i++) {
            random_fill_octree(&kids[i], voxel, depth);
        }
    } else {
        if (rand() % 101 >= fill_octree_random_rate) {
            node->value = 0;
        } else if (rand() % 101 >= fill_octree_random_rate2) {
            node->value = 2;
        } else if (rand() % 101 >= fill_octree_random_rate3) {
            node->value = 3;
        }
    }
}

void fill_octree(VoxelNode* node, const byte voxel, byte depth) {
    node->value = voxel;
    if (depth > 0) {
        depth--;
        open_new_VoxelNode(node);
        VoxelNode* kids = get_children_VoxelNode(node);
        for (byte i = 0; i < octree_length; i++) {
            fill_octree(&kids[i], voxel, depth);
        }
    }
}

VoxelNode* set_voxel(const SetVoxelTargetData *datam, SetVoxelData data) {
    byte depth_reached = data.depth == datam->depth;
    if (datam->effect_nodes && !depth_reached && is_closed_VoxelNode(data.node)) {
        open_new_VoxelNode(data.node);
        VoxelNode* kids = get_children_VoxelNode(data.node);
        for (byte i = 0; i < octree_length; i++) {
            kids[i].value = data.node->value;
        }
    }
    // wait this overrides child nodes, rather than reevaluating them
    if (depth_reached || datam->voxel) {
        data.node->value = datam->voxel;
    }
    if (depth_reached || !has_children_VoxelNode(data.node)) {
        return data.node;
    }
    const byte dividor = powers_of_two_byte[datam->depth - data.depth - 1]; // difference LoD
    byte3 node_position = (byte3) { data.position.x / dividor, data.position.y / dividor, data.position.z / dividor };
    byte3_modulus_byte(&data.position, dividor);
    VoxelNode* kids = get_children_VoxelNode(data.node);
    data.node = &kids[byte3_octree_array_index(node_position)];
    data.depth++;
    return set_voxel(datam, data);
}

void set_octree_voxel(VoxelNode *node, byte3 *position, const byte2 *set_octree_data, byte depth) {
    const SetVoxelTargetData datam = { .depth = set_octree_data->y, .voxel = set_octree_data->x };
    SetVoxelData data = { .node = node, .position = *position, .depth = depth };
    set_voxel(&datam, data);
}

void set_octree_voxel_final(
    VoxelNode* node,
    byte3* position,
    const byte2 data,
    byte depth)
{
    if (depth == data.y || !has_children_VoxelNode(node)) {
        node->value = data.x;
        return;
    }
    depth++;
    byte dividor = powers_of_two_byte[data.y - depth];   // starts at chunk_length, ends at 1
    byte3 node_position = (byte3) {
        position->x / dividor,
        position->y / dividor,
        position->z / dividor
    };
    byte3_modulus_byte(position, dividor);
    byte i = byte3_octree_array_index(node_position);
    VoxelNode* kids = get_children_VoxelNode(node);
    set_octree_voxel_final(&kids[i], position, data, depth);
}