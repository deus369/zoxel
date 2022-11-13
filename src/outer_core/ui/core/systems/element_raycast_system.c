//! A system that casts a ray into the ui elements.
/**
 * Creates an external event when selects a entity. Can be used by AI to select ui too.
*/
void ElementRaycastSystem(ecs_iter_t *it)
{
    // printf("~uis_it~ [%i]\n", it->count);
    const Raycaster *raycasters = ecs_field(it, Raycaster, 1);
    RaycasterTarget *raycasterTargets = ecs_field(it, RaycasterTarget, 2);
    for (int i = 0; i < it->count; i++)
    {
        const Raycaster *raycaster = &raycasters[i];
        RaycasterTarget *raycasterTarget = &raycasterTargets[i];
        int ui_layer = -1;
        ecs_entity_t ui_selected = 0;
        SelectableState *ui_selected_selectableState = NULL;
        const int2 position = raycaster->value;
        ecs_iter_t uis_it = ecs_query_iter(it->world, it->ctx);
        while(ecs_query_next(&uis_it))
        {
            // printf("    - uis_it.count [%i] - (%i)\n", i, uis_it.count);
            const CanvasPixelPosition *canvasPixelPositions = ecs_field(&uis_it, CanvasPixelPosition, 2);
            const PixelSize *pixelSizes = ecs_field(&uis_it, PixelSize, 3);
            const ElementLayer *elementLayers = ecs_field(&uis_it, ElementLayer, 4);
            SelectableState *selectableStates = ecs_field(&uis_it, SelectableState, 5);
            for (int j = 0; j < uis_it.count; j++)
            {
                const CanvasPixelPosition *canvasPixelPosition2 = &canvasPixelPositions[j];
                const PixelSize *pixelSize2 = &pixelSizes[j];
                const ElementLayer *elementLayer = &elementLayers[j];
                const int2 *canvasPixelPosition = &canvasPixelPosition2->value;
                const int2 *pixelSize = &pixelSize2->value;
                // printf("ui raycasting [%lu] - [%i]\n", (long int) uis_it.entities[j], elementLayer->value);
                // centered
                SelectableState *selectableState = &selectableStates[j];
                bool was_raycasted = position.x >= canvasPixelPosition->x - pixelSize->x / 2 && position.x <= canvasPixelPosition->x + pixelSize->x / 2
                    && position.y >= canvasPixelPosition->y - pixelSize->y / 2 && position.y <= canvasPixelPosition->y + pixelSize->y / 2;
                if (was_raycasted && elementLayer->value > ui_layer)
                {
                    ui_layer = elementLayer->value;
                    ui_selected = uis_it.entities[j];
                    ui_selected_selectableState = selectableState;
                    /*printf("ui [%lu] raycasting position [%ix%i] ray([%ix%i]) :: size [%ix%i] Hit? %s screenSize [%ix%i]\n",
                        (long int) uis_it.entities[j],
                        canvasPixelPosition->x, canvasPixelPosition->y,
                        raycaster->value.x, raycaster->value.y,
                        pixelSize->x, pixelSize->y, was_raycasted ? "true" : "false",
                        screenDimensions.x, screenDimensions.y);*/
                }
                /*if (was_raycasted)
                {
                    printf("selectableState ui was raycasted [%lu]\n", (long int) uis_it.entities[j]);
                }
                else if (!was_raycasted)
                {
                    printf("selectableState ui was un raycasted [%lu]\n", (long int) uis_it.entities[j]);
                }*/
            }
        }
        if (raycasterTarget->value != ui_selected)
        {
            //! Deselect last ui.
            if (raycasterTarget->value != 0 && ecs_is_alive(world, raycasterTarget->value))
            {
                ecs_set(it->world, raycasterTarget->value, SelectableState, { 0 });
            }
            raycasterTarget->value = ui_selected;
            if (ui_layer != -1)
            {
                ui_selected_selectableState->value = 1;
            }
            // printf("    -> new target ui [%lu] \n", (long int) raycasterTarget->value);
        }
    }
}
ECS_SYSTEM_DECLARE(ElementRaycastSystem);


// cornered
//if (position.x >= pixelPosition->x && position.x <= pixelPosition->x + pixelSize->x
//    && position.y >= pixelPosition->y && position.y <= pixelPosition->y + pixelSize->y)