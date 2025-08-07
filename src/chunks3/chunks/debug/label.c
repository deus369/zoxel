uint get_label_chunk_link(ecs *world, const entity character, char *buffer, const uint size, uint index) {
    index += snprintf(buffer + index, size - index, "char [%s]\n", zox_get_name(character));

    // terrain
    zox_geter(character, VoxLink, voxLink)
    if (!zox_valid(voxLink->value)) {
        index += snprintf(buffer + index, size - index, " - has no terrain linked\n");
    } else {
        index += snprintf(buffer + index, size - index, " - is exploring [%s]\n", zox_get_name(voxLink->value));
    }

    // positions
    zox_geter_value(character, Position3D, float3, position)
    zox_geter_value(character, Euler, float3, euler)
    zox_geter_value(character, ChunkPosition, int3, chunk_position)
    index += snprintf(buffer + index, size - index, " - pos [%fx%fx%f]\n", position.x, position.y, position.z);
    index += snprintf(buffer + index, size - index, " - eul [%fx%fx%f]\n", euler.x, euler.y, euler.z);
    index += snprintf(buffer + index, size - index, " - in [%ix%ix%i]\n", chunk_position.x, chunk_position.y, chunk_position.z);

    // chunk
    zox_geter_value(character, ChunkLink, entity, chunk)
    if (!zox_valid(chunk)) {
        index += snprintf(buffer + index, size - index, "linked chunk [none]\n");
    } else {
        index += snprintf(buffer + index, size - index, "linked chunk [%s]\n", zox_get_name(chunk));
        zox_geter_value(chunk, ChunkPosition, int3, chunk_chunk_position)
        index += snprintf(buffer + index, size - index, " - at [%ix%ix%i]\n", chunk_chunk_position.x, chunk_chunk_position.y, chunk_chunk_position.z);
    }

    zox_geter_value(character, CameraLink, entity, camera)
    if (zox_valid(camera)) {
        index += snprintf(buffer + index, size - index, "cam [%s]\n", zox_get_name(camera));
        zox_geter_value(camera, Position3D, float3, camera_position)
        zox_geter_value(camera, Euler, float3, camera_euler)
        index += snprintf(buffer + index, size - index, " - pos [%fx%fx%f]\n", camera_position.x, camera_position.y, camera_position.z);
        index += snprintf(buffer + index, size - index, " - eul [%fx%fx%f]\n", camera_euler.x, camera_euler.y, camera_euler.z);
    }

    return index;
}