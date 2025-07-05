ecs_entity_t test_elementbar2D_front = 0;

void test_key_element_front2D(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_f) {
        // zox_log("> [%lu] test statbar_front2D\n", test_elementbar2D_front)
        zox_log("> test statbar_front2D")
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