void StreamPointSystem(ecs_iter_t *it)
{
    //! todo only check when Position3D changes.
    /*if (!ecs_query_changed(NULL, it))
    {
        // printf("Position3D has not changed.\n");
        return;
    }*/
    /*if (!ecs_query_changed(it->ctx, NULL))
    {
        printf("Position3D has not changed.\n");
        return;
    }*/
    // printf("Position3D has changed.\n");
    unsigned char did_update = 0;
    const int3 chunk_size = (int3) { 16, 16, 16 };
    const Position3D *position3Ds = ecs_field(it, Position3D, 2);
    StreamPoint *streamPoints = ecs_field(it, StreamPoint, 3);
    for (int i = 0; i < it->count; i++)
    {
        const Position3D *position3D = &position3Ds[i];
        int3 new_position = get_chunk_position(position3D->value, chunk_size);  // translate position to int3 chunk position
        // printf("Checking Streamer position3D: [%fx%fx%f] \n", position3D->value.x, position3D->value.y, position3D->value.z);
        StreamPoint *streamPoint = &streamPoints[i];
        if (!int3_equal(new_position, streamPoint->value))
        {
            streamPoint->value = new_position;
            did_update = 1;
            printf("Stream Point Updated [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
        }
    }
    // skip table updates here if no updates
    if (!did_update)
    {
        ecs_query_skip(it);
    }
}
zoxel_declare_system(StreamPointSystem)