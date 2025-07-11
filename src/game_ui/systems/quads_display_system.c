void QuadsLabelSystem(ecs_iter_t *it) {
    const int triangles_count = MeshIndicies_memorys_allocated * 3;
    char buffer[32];
    //byte system_updated = 0;
    zox_field_out(QuadsCount, quadsCounts, 2)
    zox_field_out(ZextDirty, zextDirtys, 3)
    zox_field_out(TextData, textDatas, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ZextDirty, zextDirtys, zextDirty)
        if (zextDirty->value) continue;
        zox_field_o(QuadsCount, quadsCounts, quadsCount)
        if (quadsCount->value == triangles_count) continue;
        zox_field_o(TextData, textDatas, textData)
        quadsCount->value = triangles_count;
        //if (!system_updated) {
            //system_updated = 1;
        snprintf(buffer, sizeof(buffer), "triangles [%i]", triangles_count);
        //}
        set_zext(textData, buffer);
        zextDirty->value = 1;
    }
#ifndef zoxel_on_windows
    //if (!system_updated) zox_skip()   // skip changes if isn't has_set
#endif
} zox_declare_system(QuadsLabelSystem)
