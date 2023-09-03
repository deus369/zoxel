extern int characters_count;

void GameDebugLabelSystem(ecs_iter_t *it) {
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
    ZextData *zextDatas = ecs_field(it, ZextData, 3);
    for (int i = 0; i < it->count; i++) {
        ZextDirty *zextDirty = &zextDirtys[i];
        ZextData *zextData = &zextDatas[i];
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "Characters %i", characters_count);
        if (!is_zext(zextData, buffer)) {
            set_zext(zextData, buffer);
            zextDirty->value = 1;
        }
    }
    // if (!has_set) ecs_query_skip(it);
} zox_declare_system(GameDebugLabelSystem)