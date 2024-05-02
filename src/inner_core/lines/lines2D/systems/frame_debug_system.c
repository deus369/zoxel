// sets the lines height based on frame times
void FrameDebugSystem(ecs_iter_t *it) {
    const double pixel_height_per_ms = 5;
    int2 limits = (int2) { 4, 320 };
    zox_field_in(ChildIndex, childIndexs, 2)
    zox_field_out(LineLocalPosition2D, lineLocalPosition2Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ChildIndex, childIndexs, childIndex)
        zox_field_i_out(LineLocalPosition2D, lineLocalPosition2Ds, lineLocalPosition2D)
        int new_height = (int) (zox_delta_times[childIndex->value] * 1000 * pixel_height_per_ms);
        if (new_height < limits.x) new_height = limits.x;
        else if (new_height > limits.y) new_height = limits.y;
        lineLocalPosition2D->value.w = new_height;
    }
} zox_declare_system(FrameDebugSystem)
