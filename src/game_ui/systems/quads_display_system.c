void QuadsLabelSystem(ecs_iter_t *it) {
    const int triangles_count = MeshIndicies_memorys_allocated * 3;
    char buffer[32];
    //byte system_updated = 0;
    zox_sys_begin()
    zox_sys_out(QuadsCount)
    zox_sys_out(ZextDirty)
    zox_sys_out(TextData)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(ZextDirty, zextDirty)
        zox_sys_o(QuadsCount, quadsCount)
        zox_sys_o(TextData, textData)
        if (zextDirty->value) continue;
        if (quadsCount->value == triangles_count) continue;
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
