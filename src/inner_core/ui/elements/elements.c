#ifndef zoxel_ui_elements
#define zoxel_ui_elements

// components
zox_declare_tag(Label)            // UI extras, make extra ui module?
zox_declare_tag(Button)           //! A generic ui button for clicking.
zox_declare_tag(Window)           //! A ui window.
zox_declare_tag(Header)           //! A ui window header.
zox_declare_tag(CloseButton)      //! A ui window close button
zox_declare_tag(Statbar)
zox_declare_tag(Scrollbar)
zox_declare_tag(ScrollbarButton)
zox_component_byte(ListUIMax)
// prefabs
#include "prefabs/label.c"
#include "prefabs/label_background.c"
#include "prefabs/button.c"
#include "prefabs/header.c"
#include "prefabs/window.c"
#include "prefabs/scrollbar.c"
#include "prefabs/ui_list.c"
#include "prefabs/statbar3D.c"
// systems
#include "systems/button_click_sound_system.c"
#include "systems/element_drag_system.c"
#include "systems/scrollbar_system.c"
// functions
#include "fun/button_event_close_window.c"

// uses resizes the mesh
void on_resized_element(ecs_world_t *world, ecs_entity_t e, int2 pixel_size, float2 canvas_size) {
    if (!headless && zox_has(e, MeshVertices2D)) {
        const MeshAlignment *meshAlignment = zox_get(e, MeshAlignment)
        MeshVertices2D *meshVertices2D = zox_get_mut(e, MeshVertices2D)
        float2 scale2D = (float2) { pixel_size.x / canvas_size.y, pixel_size.y / canvas_size.y };
        set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(meshAlignment->value), 4, scale2D);
        zox_modified(e, MeshVertices2D)
        zox_set(e, MeshDirty, { 1 })
        zox_set(e, GenerateTexture, { 1 })
        #ifdef debug_ui_scaling
            zox_log("        -> Scaling: [%fx%f]\n", scale2D.x, scale2D.y)
        #endif
        if (zox_has(e, Window)) {
            const Children *children = zox_get(e, Children);
            ecs_entity_t header = children->value[0];
            int2 header_size = (int2) { pixel_size.x, zox_gett_value(header, PixelSize).y };
            zox_set(header, PixelSize, { header_size })
            zox_set(header, TextureSize, { header_size })
            on_resized_element(world, header, header_size, canvas_size);
            // zox_log("   > header_height: %f\n", header_height)
            if (children->length > 1) {
                ecs_entity_t scrollbar = children->value[1];
                if (zox_has(scrollbar, Scrollbar)) {
                    int2 scrollbar_size = (int2) { zox_gett_value(scrollbar, PixelSize).x, pixel_size.y };
                    zox_set(scrollbar, PixelSize, { scrollbar_size })
                    zox_set(scrollbar, TextureSize, { scrollbar_size })
                    on_resized_element(world, scrollbar, scrollbar_size, canvas_size);
                    const Children *scrollbar_children = zox_get(scrollbar, Children);
                    ecs_entity_t scrollbar_front = scrollbar_children->value[0];
                    zox_set(scrollbar_front, DraggableLimits, { (int2) { 0, (scrollbar_size.y / 2) - scrollbar_size.x / 2 } })
                }
            }
            const Children *header_children = zox_get(header, Children);
            if (header_children->length > 1) {
                float2 header_position = zox_get_value(header, Position2D)
                ecs_entity_t close_button = header_children->value[1];
                int2 close_button_position = zox_get_value(close_button, PixelPosition)
                float2 close_button_anchor = zox_get_value(close_button, Anchor)
                on_element_parent_updated(world, close_button, close_button_position, close_button_anchor, header_position, header_size, canvas_size);
            }
        }
    }
}

void spawn_prefabs_elements(ecs_world_t *world) {
    spawn_prefab_label(world);
    spawn_prefab_label_background(world);
    spawn_prefab_button(world);
    spawn_prefab_window(world);
    spawn_prefab_header(world);
    spawn_prefab_scrollbar(world);
    spawn_prefab_scrollbar_front(world);
    spawn_prefab_ui_list(world);
    spawn_prefab_statbar3D(world);
    spawn_prefab_statbar3D_front(world);
}

zox_begin_module(Elements)
// component defines
zox_define_tag(Label)
zox_define_tag(Button)
zox_define_tag(Window)
zox_define_tag(Header)
zox_define_tag(CloseButton)
zox_define_tag(Statbar)
zox_define_tag(Scrollbar)
zox_define_tag(ScrollbarButton)
zox_define_component(ListUIMax)
// system defines
zox_system(ElementDragSystem, EcsPostLoad, [in] DraggableState, [in] DraggingDelta, [in] DraggedLink)
zox_system(ButtonClickSoundSystem, EcsPostUpdate, [none] Button, [in] ClickState) // move this to core
zox_system(ScrollbarSystem, EcsPostUpdate, [none] ScrollbarButton, [in] DraggableState, [in] PixelPosition, [in] PixelSize, [in] ParentLink)
// zox_system_1(ScrollbarSystem, main_thread_pipeline, [none] ScrollbarButton, [in] DraggableState, [in] PixelPosition)
zoxel_end_module(Elements)

#endif
