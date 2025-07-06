

const VoxelLinks* get_first_terrain_voxels(ecs_world_t *world, const VoxLink *voxLinks, int count) {
    ecs_entity_t realm = 0;
    for (int i = 0; i < count; i++) {
        zox_field_i(VoxLink, voxLinks, voxLink)
        if (!zox_valid(voxLink->value) || !zox_has(voxLink->value, RealmLink)) {
            continue;
        }
        realm = zox_get_value(voxLink->value, RealmLink)
        break;
    }
    if (!zox_valid(realm)) {
        return NULL;
    }
    zox_geter(realm, VoxelLinks, voxels)
    return voxels;
}

void get_block_collisions(ecs_world_t *world, const VoxelLinks *voxels, byte *collisions) {
    collisions[0] = 0;    // air
    for (int i = 0; i < voxels->length; i++) {
        const ecs_entity_t block = voxels->value[i];
        if (zox_valid(block)) {
            collisions[i + 1] = zox_gett_value(block, BlockCollider) != zox_block_air;
        } else {
            collisions[i + 1] = 0;
        }
    }
}