void QuadsLabelSystem(ecs_iter_t *it) {
    unsigned char has_set = 0;   //! Skip changes if isn't has_set.
    char buffer[20];
    // const char* text = buffer;
    QuadsCount *quadsCount = ecs_field(it, QuadsCount, 2);
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 3);
    ZextData *zextDatas = ecs_field(it, ZextData, 4);
    for (int i = 0; i < it->count; i++) {
        if (quadsCount->value == triangles_count) continue;
        ZextDirty *zextDirty = &zextDirtys[i];
        ZextData *zextData = &zextDatas[i];
        quadsCount->value = triangles_count;
        if (!has_set) {
            has_set = 1;
            snprintf(buffer, sizeof(buffer), "triangles [%i]", triangles_count);
        }
        set_zext(zextData, buffer);
        zextDirty->value = 1;
    }
    if (!has_set) ecs_query_skip(it);
} zox_declare_system(QuadsLabelSystem)