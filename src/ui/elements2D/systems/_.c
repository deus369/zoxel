#include "element_drag_system.c"
#include "scrollbar_system.c"
#include "elementbar2D_system.c"
#include "tooltip_system.c"
#include "slide_event_system.c"

void define_systems_elements2D(ecs_world_t *world) {
    zox_system(ElementDragSystem, EcsPostLoad,
        [in] elements.core.DraggableState,
        [in] elements.core.DraggingDelta,
        [in] elements.core.DraggedLink)
    zox_system(ScrollbarSystem, EcsPostUpdate,
        [none] ScrollbarButton,
        [in] elements.core.DraggableState,
        [in] layouts2.PixelPosition,
        [in] layouts2.PixelSize,
        [in] hierarchys.ParentLink)
    zox_system(Elementbar2DSystem, EcsPostUpdate,
        [in] elements.core.ElementBar,
        [in] elements.core.ElementBarSize,
        [in] hierarchys.Children,
        [in] layouts2.PixelSize,
        [none] Elementbar2D)
    zox_system(TooltipSystem, EcsOnUpdate,
        [in] elements.core.SelectState,
        [in] elements.core.CanvasLink,
        [in] elements.core.TooltipEvent)
    zox_system(SlideEventSystem, EcsOnUpdate,
        [in] elements.core.SlideEvent,
        [in] elements.core.DraggableState,
        [in] elements.core.DraggerLink,
        [in] elements.core.DraggableLimits,
        [in] layouts2.PixelPosition)
}