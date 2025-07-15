uint get_label_chunk_link(ecs_world_t *world, const ecs_entity_t character, char *buffer, const uint size, uint index) {
    index += snprintf(buffer + index, size - index, "[%s]\n", zox_get_name(character));

    // terrain
    zox_geter(character, VoxLink, voxLink)
    if (!zox_valid(voxLink->value)) {
        index += snprintf(buffer + index, size - index, " - has no terrain linked\n");
    } else {
        index += snprintf(buffer + index, size - index, " - is exploring [%s]\n", zox_get_name(voxLink->value));
    }

    // positions
    zox_geter(character, Position3D, position3D)
    index += snprintf(buffer + index, size - index, " - at [%fx%fx%f]\n", position3D->value.x, position3D->value.y, position3D->value.z);
    zox_geter(character, ChunkPosition, chunkPosition)
    index += snprintf(buffer + index, size - index, " - in [%ix%ix%i]\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);

    // chunk
    zox_geter(character, ChunkLink, chunkLink)
    if (!zox_valid(chunkLink->value)) {
        index += snprintf(buffer + index, size - index, " - has no chunk linked\n");
    } else {
        zox_geter(chunkLink->value, ChunkPosition, chunk_chunk_position)
        index += snprintf(buffer + index, size - index, " - is linked to [%ix%ix%i]\n", chunk_chunk_position->value.x, chunk_chunk_position->value.y, chunk_chunk_position->value.z);
    }
    return index;
}