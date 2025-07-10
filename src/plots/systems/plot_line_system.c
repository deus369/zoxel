// sets the lines height based on frame times
// todo: use PlotData
void PlotLineSystem(ecs_iter_t *it) {
    const double pixel_height_per_ms = 5;
    int2 limits = (int2) { 4, 320 };
    zox_field_world()
    zox_sys_begin()
    zox_sys_in(ParentLink)
    zox_sys_in(ChildIndex)
    zox_sys_out(LineLocalPosition2D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ParentLink, parentLink)
        zox_sys_i(ChildIndex, childIndex)
        zox_sys_o(LineLocalPosition2D, lineLocalPosition2D)
        if (!parentLink->value || !zox_has(parentLink->value, PlotDataDouble)) {
            zox_log(" > no PlotDataDouble found on parent\n")
            continue;
        }
        zox_geter(parentLink->value, PlotDataDouble, data)
        if (childIndex->value >= data->length) {
            zox_log(" > index [%i] out of bounds for PlotLineSystem\n", childIndex->value, data->length)
            continue;
        }
        double this_time = data->value[childIndex->value];
        int new_height = (int) (this_time * 1000 * pixel_height_per_ms);
        if (new_height < limits.x) {
            new_height = limits.x;
        } else if (new_height > limits.y) {
            new_height = limits.y;
        }
        lineLocalPosition2D->value.w = new_height;
    }
} zox_declare_system(PlotLineSystem)
