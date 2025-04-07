#ifndef zox_elements2D
#define zox_elements2D

ecs_entity_t test_elementbar2D_front = 0;
zox_declare_tag(Label)
zox_declare_tag(Button)
zox_declare_tag(CloseButton)
zox_declare_tag(Icon)
zox_declare_tag(IconFrame)
zox_declare_tag(IconLabel)
zox_declare_tag(Header)
zox_declare_tag(Body)
zox_declare_tag(Scrollbar)
zox_declare_tag(ScrollbarButton)
zox_declare_tag(Elementbar2D)
zox_component_byte(IconType)
zox_component_byte(ListUIMax)
zox_component_byte(IconIndex)
zox_component_entity(IconFramePrefabLink)
#include "data/data.c"
#include "prefabs/prefabs.c"
#include "util/button_event_close_window.c"
#include "util/resize_util.c"
#include "util/navigation_util.c"
#include "util/position_util.c"
#include "systems/element_drag_system.c"
#include "systems/scrollbar_system.c"
#include "systems/elementbar2D_system.c"

void test_key_element_front2D(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_f) {
        // zox_log("> [%lu] test statbar_front2D\n", test_elementbar2D_front)
        zox_log_line("> test statbar_front2D")
        if (!zox_valid(test_elementbar2D_front)) {
            zox_log("   - [%lu] bad statbar_front2D\n", test_elementbar2D_front)
        } else {
            const ecs_entity_t e = test_elementbar2D_front;
            zox_log("   - [%s] checking\n", zox_get_name(e))
            zox_log("   - MeshDirty [%i]\n", zox_gett_value(e, MeshDirty))
            zox_log("   - MeshIndicies? [%i]\n", zox_has(e, MeshIndicies))
            zox_log("   - MeshVertices2D? [%i]\n", zox_has(e, MeshVertices2D))
            zox_log("   - MeshUVs? [%i]\n", zox_has(e, MeshUVs))
            zox_log("   - MeshGPULink? [%i]\n", zox_has(e, MeshGPULink))
            zox_log("   - UvsGPULink? [%i]\n", zox_has(e, UvsGPULink))
            zox_set(e, MeshDirty, { mesh_state_upload })
        }
    }
}

zox_begin_module(Elements2D)
    zox_define_tag(Label)
    zox_define_tag(Button)
    zox_define_tag(Icon)
    zox_define_tag(IconFrame)
    zox_define_tag(IconLabel)
    zox_define_tag(Header)
    zox_define_tag(Body)
    zox_define_tag(CloseButton)
    zox_define_tag(Scrollbar)
    zox_define_tag(ScrollbarButton)
    zox_define_tag(Elementbar2D)
    zox_define_component_byte(IconType)
    zox_define_component_byte(ListUIMax)
    zox_define_component_byte(IconIndex)
    zox_define_component_entity(IconFramePrefabLink)
    zox_system(ElementDragSystem, EcsPostLoad, [in] DraggableState, [in] DraggingDelta, [in] DraggedLink)
    zox_system(ScrollbarSystem, EcsPostUpdate, [none] ScrollbarButton, [in] DraggableState, [in] PixelPosition, [in] PixelSize, [in] ParentLink)
    zox_system(Elementbar2DSystem, EcsPostUpdate, [in] ElementBar, [in] ElementBarSize, [in] Children, [in] PixelSize, [none] Elementbar2D)
    spawn_prefabs_elements(world);
    // add_hook_key_down(test_key_element_front2D);
zox_end_module(Elements2D)

#endif
