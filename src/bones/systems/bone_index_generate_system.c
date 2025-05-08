// todo: Shapes on bones used for setting verts, spheres of influence
// todo: use SphereRadius float per bone for a simple radius

void BoneIndexGenerateSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(MeshDirty, meshDirtys, 1)
    zox_field_in(MeshVertices, meshVerticess, 2)
    zox_field_in(BoneLinks, boneLinkss, 3)
    // outputting the generated weights
    zox_field_out(BoneIndexes, boneIndexess, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MeshDirty, meshDirtys, meshDirty)
        if (meshDirty->value != mesh_state_generate) {
            continue;
        }
        zox_field_i(MeshVertices, meshVerticess, meshVertices)
        zox_field_i(BoneLinks, boneLinkss, boneLinks)
        // get all children bone positions and sizes
        float3 bone_positions[boneLinks->length];
        float3 bone_sizes[boneLinks->length];
        float3 bones_bounds_lower[boneLinks->length];
        float3 bones_bounds_upper[boneLinks->length];
        for (int j = 0; j < boneLinks->length; j++) {
            const ecs_entity_t bone = boneLinks->value[j];
            bone_positions[j] = zox_get_value(bone, BonePosition)
            bone_sizes[j] = zox_get_value(bone, BoneSize)
            const float3 half_size = bone_sizes[j]; // float3_multiply_float(bone_sizes[j], 0.5f);
            bones_bounds_lower[j] = float3_sub(bone_positions[j], half_size);
            bones_bounds_upper[j] = float3_add(bone_positions[j], half_size);
        }
        zox_field_o(BoneIndexes, boneIndexess, boneIndexes)
        resize_memory_component(BoneIndexes, boneIndexes, byte, meshVertices->length)
        for (int j = 0; j < meshVertices->length; j++) {
            const float3 position = meshVertices->value[j];
            boneIndexes->value[j] = 0;
            for (int k = boneLinks->length - 1; k >= 0; k--) {
                const float3 lower = bones_bounds_lower[k];
                const float3 upper = bones_bounds_upper[k];
                // check in constraints
                if (position.x >= lower.x && position.x <= upper.x && position.y >= lower.y && position.y <= upper.y && position.z >= lower.z && position.z <= upper.z) {
                    boneIndexes->value[j] = k;
                    /*if (k == 1) {
                        zox_log("Bone Vert Index Found: %i (vert %i)\n", k, j)
                    }*/
                    break;
                }
                /*if (j >= meshVertices->length - 100) {
                    zox_log("Bone Vert Index Found: %i (vert %i)\n", k, j)
                    zox_log_line("  > position: %fx%fx%f", position.x, position.y, position.z)
                    zox_log_line("  > lower: %fx%fx%f", lower.x, lower.y, lower.z)
                    zox_log_line("  > upper: %fx%fx%f", upper.x, upper.y, upper.z)
                }*/
            }
            // for each position, check all bones, and see if it is within them
            //if (position.y >= 0.12f * 0.5f) boneIndexes->value[j] = 1;
            //else boneIndexes->value[j] = 0;
        }
    }
} zox_declare_system(BoneIndexGenerateSystem)
