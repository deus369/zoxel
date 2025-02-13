// sets the lines height based on frame times
// todo: use PlotData
void PlotLineSystem(ecs_iter_t *it) {
    const double pixel_height_per_ms = 5;
    int2 limits = (int2) { 4, 320 };
    zox_field_world()
    zox_field_in(ParentLink, parentLinks, 1)
    zox_field_in(ChildIndex, childIndexs, 2)
    zox_field_out(LineLocalPosition2D, lineLocalPosition2Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ParentLink, parentLinks, parentLink)
        if (!parentLink->value) continue;
        if (!zox_has(parentLink->value, PlotDataDouble)) {
            zox_log(" > no PlotDataDouble found on parent\n")
            continue;
        }
        zox_field_i(ChildIndex, childIndexs, childIndex)
        const PlotDataDouble *data = zox_get(parentLink->value, PlotDataDouble)
        if (childIndex->value >= data->length) {
            zox_log(" > index [%i] out of bounds for PlotLineSystem\n", childIndex->value, data->length)
            continue;
        }
        zox_field_o(LineLocalPosition2D, lineLocalPosition2Ds, lineLocalPosition2D)
        double this_time = data->value[childIndex->value];
        int new_height = (int) (this_time * 1000 * pixel_height_per_ms);
        if (new_height < limits.x) new_height = limits.x;
        else if (new_height > limits.y) new_height = limits.y;
        lineLocalPosition2D->value.w = new_height;
    }
} zox_declare_system(PlotLineSystem)
