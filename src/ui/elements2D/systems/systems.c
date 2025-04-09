#include "element_drag_system.c"
#include "scrollbar_system.c"
#include "elementbar2D_system.c"
#include "tooltip_system.c"

void define_systems_elements2D(ecs_world_t *world) {
    zox_system(ElementDragSystem, EcsPostLoad, [in] DraggableState, [in] DraggingDelta, [in] DraggedLink)
    zox_system(ScrollbarSystem, EcsPostUpdate, [none] ScrollbarButton, [in] DraggableState, [in] PixelPosition, [in] PixelSize, [in] ParentLink)
    zox_system(Elementbar2DSystem, EcsPostUpdate, [in] ElementBar, [in] ElementBarSize, [in] Children, [in] PixelSize, [none] Elementbar2D)
    zox_system(TooltipSystem, EcsOnUpdate, [in] SelectState, [in] CanvasLink, [in] TooltipEvent)
}