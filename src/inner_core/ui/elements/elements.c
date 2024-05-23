#ifndef zox_ui_elements
#define zox_ui_elements

#include "settings/settings.c"
zox_declare_tag(Label)
zox_declare_tag(Button)
zox_declare_tag(CloseButton)
zox_declare_tag(Icon)
zox_declare_tag(IconFrame)
zox_declare_tag(Header)
zox_declare_tag(Scrollbar)
zox_declare_tag(ScrollbarButton)
zox_component_byte(ListUIMax)
#include "data/spawn_button.c"
#include "data/spawn_header.c"
#include "data/spawn_window.c"
#include "data/spawn_icon.c"
#include "data/spawn_icon_frame.c"
#include "prefabs/prefabs.c"
#include "fun/button_event_close_window.c"
#include "util/resize_util.c"
#include "util/navigation_util.c"
#include "systems/element_drag_system.c"
#include "systems/scrollbar_system.c"

zox_begin_module(Elements)
zox_define_tag(Label)
zox_define_tag(Button)
zox_define_tag(Icon)
zox_define_tag(IconFrame)
zox_define_tag(Header)
zox_define_tag(CloseButton)
zox_define_tag(Scrollbar)
zox_define_tag(ScrollbarButton)
zox_define_component(ListUIMax)
zox_system(ElementDragSystem, EcsPostLoad, [in] DraggableState, [in] DraggingDelta, [in] DraggedLink)
zox_system(ScrollbarSystem, EcsPostUpdate, [none] ScrollbarButton, [in] DraggableState, [in] PixelPosition, [in] PixelSize, [in] ParentLink)
spawn_prefabs_elements(world);
zoxel_end_module(Elements)

#endif
