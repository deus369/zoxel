#ifndef zoxel_ui_elements
#define zoxel_ui_elements

// settings
#include "settings/settings.c"
// components
zox_declare_tag(Label)            // UI extras, make extra ui module?
zox_declare_tag(Button)           //! A generic ui button for clicking.
zox_declare_tag(Header)           //! A ui window header.
zox_declare_tag(CloseButton)      //! A ui window close button
// todo: move these too stats_ui
zox_declare_tag(Statbar)
zox_declare_tag(Scrollbar)
zox_declare_tag(ScrollbarButton)
zox_component_byte(ListUIMax)
// datas
#include "data/spawn_element_data.c"
// prefabs
#include "prefabs/label.c"
#include "prefabs/label_background.c"
#include "prefabs/button.c"
#include "prefabs/header.c"
#include "prefabs/window.c"
#include "prefabs/scrollbar_front.c"
#include "prefabs/scrollbar.c"
#include "prefabs/ui_list.c"
#include "prefabs/elementbar2D_front.c"
#include "prefabs/elementbar2D.c"
#include "prefabs/elementbar3D_front.c"
#include "prefabs/elementbar3D.c"
// functions
#include "fun/button_event_close_window.c"
#include "util/resize_util.c"
#include "util/navigation_util.c"
// systems
#include "systems/element_drag_system.c"
#include "systems/scrollbar_system.c"

void spawn_prefabs_elements(ecs_world_t *world) {
    spawn_prefab_label(world);
    spawn_prefab_label_background(world);
    spawn_prefab_button(world);
    spawn_prefab_window(world);
    spawn_prefab_header(world);
    spawn_prefab_scrollbar(world);
    spawn_prefab_scrollbar_front(world);
    spawn_prefab_ui_list(world);
    spawn_prefab_elementbar2D(world);
    spawn_prefab_elementbar2D_front(world);
    spawn_prefab_elementbar3D(world);
    spawn_prefab_elementbar3D_front(world);
}

zox_begin_module(Elements)
// component defines
zox_define_tag(Label)
zox_define_tag(Button)
zox_define_tag(Header)
zox_define_tag(CloseButton)
zox_define_tag(Statbar)
zox_define_tag(Scrollbar)
zox_define_tag(ScrollbarButton)
zox_define_component(ListUIMax)
// system defines
zox_system(ElementDragSystem, EcsPostLoad, [in] DraggableState, [in] DraggingDelta, [in] DraggedLink)
zox_system(ScrollbarSystem, EcsPostUpdate, [none] ScrollbarButton, [in] DraggableState, [in] PixelPosition, [in] PixelSize, [in] ParentLink)
zoxel_end_module(Elements)

#endif
