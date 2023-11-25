void QuadsLabelSystem(ecs_iter_t *it) {
    const int triangles_count = MeshIndicies_memorys_allocated * 3;
    char buffer[32];
    unsigned char system_updated = 0;
    // const char* text = buffer;
    QuadsCount *quadsCounts = ecs_field(it, QuadsCount, 2);
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 3);
    ZextData *zextDatas = ecs_field(it, ZextData, 4);
    for (int i = 0; i < it->count; i++) {
        QuadsCount *quadsCount = &quadsCounts[i];
        if (quadsCount->value == triangles_count) continue;
        ZextDirty *zextDirty = &zextDirtys[i];
        ZextData *zextData = &zextDatas[i];
        quadsCount->value = triangles_count;
        if (!system_updated) {
            system_updated = 1;
            snprintf(buffer, sizeof(buffer), "triangles [%i]", triangles_count);
        }
        set_zext(zextData, buffer);
        zextDirty->value = 1;
    }
#ifndef zoxel_on_windows
    if (!system_updated) ecs_query_skip(it);   // skip changes if isn't has_set
#endif
} zox_declare_system(QuadsLabelSystem)
