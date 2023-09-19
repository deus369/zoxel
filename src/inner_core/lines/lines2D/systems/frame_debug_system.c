// sets the lines height based on frame times
void FrameDebugSystem(ecs_iter_t *it) {
    int2 limits = (int2) { 10, 360 };
    const ChildIndex *childIndexs = ecs_field(it, ChildIndex, 2);
    LineLocalPosition2D *lineLocalPosition2Ds = ecs_field(it, LineLocalPosition2D, 3);
    // LinePosition2D *linePosition2Ds = ecs_field(it, LinePosition2D, 3);
    for (int i = 0; i < it->count; i++) {
        const ChildIndex *childIndex = &childIndexs[i];
        LineLocalPosition2D *lineLocalPosition2D = &lineLocalPosition2Ds[i];
        // LinePosition2D *linePosition2D = &linePosition2Ds[i];
        int new_height = (int) (zox_delta_times[childIndex->value] * 8000);
        if (new_height < limits.x) new_height = limits.x;
        else if (new_height > limits.y) new_height = limits.y;
        // zoxel_log(" > height [%i]\n", new_height);
        // int new_height = zox_delta_times[i];
        lineLocalPosition2D->value.w = new_height;
    }
} zox_declare_system(FrameDebugSystem)