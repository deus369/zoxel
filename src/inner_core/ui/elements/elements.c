#ifndef zoxel_ui_elements
#define zoxel_ui_elements

#include "settings/settings.c"
zox_declare_tag(Label)            // UI extras, make extra ui module?
zox_declare_tag(Button)           //! A generic ui button for clicking.
zox_declare_tag(Header)           //! A ui window header.
zox_declare_tag(CloseButton)      //! A ui window close button
zox_declare_tag(Scrollbar)
zox_declare_tag(ScrollbarButton)
zox_component_byte(ListUIMax)
#include "data/spawn_button.c"
#include "data/spawn_header.c"
#include "data/spawn_window.c"
#include "prefabs/prefabs.c"
#include "fun/button_event_close_window.c"
#include "util/resize_util.c"
#include "util/navigation_util.c"
#include "systems/element_drag_system.c"
#include "systems/scrollbar_system.c"

zox_begin_module(Elements)
zox_define_tag(Label)
zox_define_tag(Button)
zox_define_tag(Header)
zox_define_tag(CloseButton)
zox_define_tag(Scrollbar)
zox_define_tag(ScrollbarButton)
zox_define_component(ListUIMax)
zox_system(ElementDragSystem, EcsPostLoad, [in] DraggableState, [in] DraggingDelta, [in] DraggedLink)
zox_system(ScrollbarSystem, EcsPostUpdate, [none] ScrollbarButton, [in] DraggableState, [in] PixelPosition, [in] PixelSize, [in] ParentLink)
zoxel_end_module(Elements)

#endif
