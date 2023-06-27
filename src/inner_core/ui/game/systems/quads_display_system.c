void QuadsLabelSystem(ecs_iter_t *it) {
    unsigned char updated = 0;   //! Skip changes if isn't updated.
    char buffer[20];
    // const char* text = buffer;
    QuadsCount *quadsCount = ecs_field(it, QuadsCount, 2);
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 3);
    ZextData *zextDatas = ecs_field(it, ZextData, 4);
    for (int i = 0; i < it->count; i++) {
        if (quadsCount->value == tri_count) continue;
        ZextDirty *zextDirty = &zextDirtys[i];
        ZextData *zextData = &zextDatas[i];
        quadsCount->value = tri_count;
        if (!updated) {
            updated = 1;
            snprintf(buffer, sizeof(buffer), "Triangles %i", tri_count);
        }
        set_zext(zextData, buffer);
        zextDirty->value = 1;
    }
    if (!updated) {
        ecs_query_skip(it);
        // free(buffer);
    }
} zox_declare_system(QuadsLabelSystem)