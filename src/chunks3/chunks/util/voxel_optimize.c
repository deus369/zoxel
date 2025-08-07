//! Closes all solid nodes, as well as air nodes, after terrain system generates it.
/*void close_solid_nodes(ecs *world, VoxelNode *node) {
    if (!has_children_VoxelNode(node)) {
        return;
    }
    // for all children nodes - only check higher nodes if closed children
    VoxelNode* kids = get_children_VoxelNode(node);
    for (byte i = 0; i < octree_length; i++) {
        close_solid_nodes(world, &kids[i]);
    }
    byte all_solid = 1;
    byte all_air = 1;
    for (byte i = 0; i < octree_length; i++) {
        // if child node is open still, don't close
        VoxelNode* child = &kids[i];
        if (is_opened_VoxelNode(child)) {
            all_solid = 0;
            all_air = 0;
            break;
        }
        // checks if all solid or all air
        if (!child->value) {
            all_solid = 0;
        } else if (child->value) {
            all_air = 0;
        }
        if (!all_solid && !all_air) {
            break;
        }
    }
    if (all_solid || all_air) {
        close_VoxelNode(world, node);
    }
}*/

// used just by vox files
void optimize_solid_nodes(VoxelNode *node) {
    if (!has_children_VoxelNode(node)) {
        return;
    }
    VoxelNode* kids = get_children_VoxelNode(node);
    for (byte i = 0; i < octree_length; i++) {
        optimize_solid_nodes(&kids[i]);
    }
    byte voxel_types = 0;
    // byte2 *voxel_counts = malloc(sizeof(byte2) * octree_length);
    byte2 voxel_counts[octree_length];
    for (byte i = 0; i < octree_length; i++) {
        byte node_value = kids[i].value;
        if (node_value == 0) {
            continue;
        }
        byte has_counted = 0;
        for (byte j = 0; j < voxel_types; j++) {
            has_counted = voxel_counts[j].x == node_value;
            if (has_counted) {
                voxel_counts[j].y++;
                break;
            }
        }
        if (!has_counted) {
            voxel_counts[voxel_types].x = node_value;
            voxel_counts[voxel_types].y = 0;
            voxel_types++;
        }
    }
    byte2 biggest_count = byte2_zero;
    for (byte j = 0; j < voxel_types; j++) {
        if (voxel_counts[j].y > biggest_count.y) {
            biggest_count = voxel_counts[j];
        }
    }
    if (biggest_count.x != 0) {
        node->value = biggest_count.x;
    }
    // free(voxel_counts);
}