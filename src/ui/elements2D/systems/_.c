#include "element_drag_system.c"
#include "scrollbar_system.c"
#include "elementbar2D_system.c"
#include "tooltip_system.c"

void define_systems_elements2D(ecs_world_t *world) {
    zox_system(ElementDragSystem, EcsPostLoad, [in] elements.core.DraggableState, [in] elements.core.DraggingDelta, [in] elements.core.DraggedLink)
    zox_system(ScrollbarSystem, EcsPostUpdate, [none] ScrollbarButton, [in] elements.core.DraggableState, [in] transforms2.d.PixelPosition, [in] transforms2.d.PixelSize, [in] hierarchys.ParentLink)
    zox_system(Elementbar2DSystem, EcsPostUpdate, [in] elements.core.ElementBar, [in] elements.core.ElementBarSize, [in] hierarchys.Children, [in] transforms2.d.PixelSize, [none] Elementbar2D)
    zox_system(TooltipSystem, EcsOnUpdate, [in] elements.core.SelectState, [in] elements.core.CanvasLink, [in] elements.core.TooltipEvent)
}