zox_tag(Element);
zox_tag(Element2D);
zox_tag(Canvas);
zox_tag(ElementRaycaster);
zox_tag(ElementBillboard);
zox_tag(BoundToCanvas);
zox_tag(CanvasOverlay);
zox_tag(Window);
zox_tag(WindowRaycastTarget);
zox_tag(ElementRender);
zox_tag(MouseElement);
zox_tag(Tooltip);
zoxc_byte(Layer2D);
zoxc_byte(ElementFontSize);
zoxc_float(ElementBar);
zoxc_float2(ElementBarSize);
zoxc_double(NavigatorTimer);
zoxc_int2(CanvasPosition);
zoxc_int2(ElementMargins);
zoxc_float2(Anchor);
zoxc_float2(AnchorSize);
zoxc_entity(CanvasLink);
zoxc_byte(HeaderHeight);
zoxc_entity(WindowRaycasted);
zoxc_entity(WindowTarget);
zoxc_entity(WindowToTop);
zoxc_byte(WindowsLayers);
zoxc_byte(WindowsCount);
zoxc_byte(SetWindowLayer);
zoxc_byte(WindowLayer);
zoxc_byte(ElementLayer);
zoxc_byte(InitializeElement);
zox_tag(ClickMakeSound);
zox_tag(Selectable);
zox_tag(Clickable);
zox_tag(Dragable);
zox_tag(IgnoreWindowLayering);
zoxc_int2(DraggingDelta);
zoxc_int4(DraggableLimits);
zoxc_entity(Clicker);
zoxc_entity(ClickingEntity);
zoxc_entity(DraggerLink);
zoxc_entity(DraggedLink);
zoxc_entity(ElementLink);
zoxc_entity(UIHolderLink);
zoxc_entities(ElementLinks)
zoxc_child(ElementHolder, ElementLinks)
zoxc_text(TooltipText)
// states
zoxc_byte(NavigatorState);
zoxc_byte(DraggableState);
zoxc_byte(SelectState);
zoxc_byte(ActiveState);
zoxc_byte(ClickState);
zoxc_byte(ActiveStateDirty);

#include "click_event.c"
#include "tooltip_event.c"
#include "slide_event.c"

// move to hlp sub folder
entity get_linked_canvas(ecs* world, entity e) {
    return zox_valid(e) && zox_has(e, CanvasLink) ? zox_gett_value(e, CanvasLink) : 0;
}

void define_components_elements_core(ecs *world) {
    zox_define_tag(Element);
    zox_define_tag(Element2D);
    zox_define_tag(Canvas);
    zox_define_tag(ElementRaycaster);
    zox_define_tag(BoundToCanvas);
    zox_define_tag(CanvasOverlay);
    zox_define_tag(Window);
    zox_define_tag(WindowRaycastTarget);
    zox_define_tag(ElementRender);
    zox_define_tag(MouseElement);
    zox_define_tag(IgnoreWindowLayering);
    zox_define_tag(Tooltip);
    zoxd_byte(Layer2D);
    zoxd_byte(ElementFontSize);
    zox_define_component_float(ElementBar);
    zox_define_component_int2(CanvasPosition);
    zox_define_component_int2(ElementMargins);
    zox_define_component_float2(Anchor);
    zox_define_component_float2(AnchorSize);
    zox_define_component_float2(ElementBarSize);
    zox_define_component(NavigatorTimer);
    zox_define_component_entity(CanvasLink);
    zoxd_byte(HeaderHeight);
    zox_define_component_entity(WindowRaycasted);
    zox_define_component_entity(WindowTarget);
    zox_define_component_entity(WindowToTop);
    zoxd_byte(WindowsLayers);
    zoxd_byte(WindowsCount);
    zoxd_byte(SetWindowLayer);
    zoxd_byte(WindowLayer);
    zoxd_byte(ElementLayer);
    zoxd_byte(InitializeElement);
    zox_define_tag(ClickMakeSound);
    zox_define_tag(Selectable);
    zox_define_tag(Clickable);
    zox_define_tag(Dragable);
    zox_define_component_entity(ClickingEntity);
    zox_define_component_entity(Clicker);
    zox_define_component_entity(ElementLink);
    zox_define_component_int2(DraggingDelta);
    zox_define_component_int4(DraggableLimits);
    zox_define_component_entity(DraggerLink);
    zox_define_component_entity(DraggedLink);
    zoxd_text(TooltipText);
    zox_define_component(UIHolderLink);
    zox_define_entities_component(ElementLinks);
    zox_define_component_entities_child(ElementHolder);
    zox_define_component(ClickEvent);
    zox_define_component(TooltipEvent);
    zox_define_component(SlideEvent);

    // States
    zoxd_byte(DraggableState);
    zoxd_byte(NavigatorState);
    zoxd_byte(SelectState);
    zoxd_byte(ActiveState);
    zoxd_byte(ClickState);
    zoxd_byte(ActiveStateDirty);
}