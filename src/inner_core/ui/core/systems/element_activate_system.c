#ifdef zoxel_inputs
    void set_ui_clicked_mut(ecs_world_t *world, ecs_entity_t ui) {
        if (ecs_has(world, ui, Clickable)) {
            ClickableState *clickableState = ecs_get_mut(world, ui, ClickableState);
            clickableState->value = 1;
            ecs_modified(world, ui, ClickableState);
        }
    }

    //! Using mouse - or action - activate a ui element.
    void ElementActivateSystem(ecs_iter_t *it) {
        ecs_world_t *world = it->world;
        const Mouse *mouses = ecs_field(it, Mouse, 1);
        const RaycasterTarget *raycasterTargets = ecs_field(it, RaycasterTarget, 2);
        for (int i = 0; i < it->count; i++) {
            const RaycasterTarget *raycasterTarget = &raycasterTargets[i];
            if (raycasterTarget->value == 0) {
                continue;
            }
            // zoxel_log(" > raycasterTarget->value %lu\n", raycasterTarget->value);
            const Mouse *mouse = &mouses[i];
            if (mouse->left.pressed_this_frame) {
                // zoxel_log(" > button clicked [%lu]\n", raycasterTarget->value);
                // printf("Clicked UI: [%lu]\n", (long int) raycasterTarget->value);
                set_ui_clicked_mut(world, raycasterTarget->value);
                // zoxel_log("     + button Clickable\n", raycasterTarget->value);
                // how to do this best way?
                if (ecs_has(world, raycasterTarget->value, Dragable)) {
                    DragableState *dragableState = ecs_get_mut(world, raycasterTarget->value, DragableState);
                    DraggerLink *draggerLink = ecs_get_mut(world, raycasterTarget->value, DraggerLink);
                    dragableState->value = 1;
                    draggerLink->value = it->entities[i];
                    ecs_modified(world, raycasterTarget->value, DragableState);
                    ecs_modified(world, raycasterTarget->value, DraggerLink);
                    //ecs_set(it->world, raycasterTarget->value, DragableState, { 1 });
                    //ecs_set(it->world, raycasterTarget->value, DraggerLink, { it->entities[i] });
                }
            }
            // temporary - todo: rework raycaster data links
            const Gamepad *gamepad = ecs_get(world, gamepad_entity, Gamepad);
            if (gamepad->a.pressed_this_frame) {
                zoxel_log(" > boom\n");
                set_ui_clicked_mut(world, raycasterTarget->value);
            }
        }
    }
    zoxel_declare_system(ElementActivateSystem)
#endif

// ecs_set(world, raycasterTarget->value, ClickableState, { 1 });
/*ClickableState *clickableState = ecs_get_mut(world, raycasterTarget->value, ClickableState);
clickableState->value = 1;
ecs_modified(world, raycasterTarget->value, ClickableState);*/
// if (ecs_has(it->world, raycasterTarget->value, CloseButton))