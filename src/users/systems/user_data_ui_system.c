// todo: SelectedEvent, Deselected Event, or, SelectState = SelectedThisFrame, Selected, Deselected, None
// todo: Give item a texture, spawn as icon!
void UserIconFrameSystem(ecs_iter_t *it) {
    zox_field_in(SelectState, selectStates, 1)
    zox_field_in(UserDataLink, userDataLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(SelectState, selectStates, selectState)
        if (!selectState->value) continue;
        zox_field_i(UserDataLink, userDataLinks, userDataLink)
        if (!userDataLink->value) {
            zox_log(" + selecting blank item ui\n")
            continue;
        }
        // zox_log(" + selecting user element: %s\n", zox_get_name(userDataLink->value))
        const ZoxName *zox_name = zox_get(userDataLink->value, ZoxName)
        if (zox_name) {
            char *name_string = convert_zext_to_text(zox_name->value, zox_name->length);
            zox_log(" + selecting item ui [%s]\n", name_string)
            free(name_string);
        } else {
            zox_log(" + selecting item ui [%lu]\n", userDataLink->value)
        }
    }
} zox_declare_system(UserIconFrameSystem)
