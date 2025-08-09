zox_hashmap_component(ChunkLinks, int3)
/*zoxc(ChunkLinks, int3_hashmap*)

void dispose_hashmap_int3(ecs *world, int3_hashmap* hashmap) {
    if (!hashmap || !hashmap->data || !hashmap->size) {
        return;
    }
    for (int j = 0; j < hashmap->size; j++) {
        int3_hashmap_pair *pair = hashmap->data[j];
        while (pair) {
            const entity e = pair->value;
            if (zox_valid(e)) {
                zox_delete(e)
            }
            pair = pair->next;
        }
    }
    int3_hashmap_dispose(hashmap);
}

void on_destroyed_ChunkLinks(iter *it) {
    zox_field_world()
    zox_field_out(ChunkLinks, components, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ChunkLinks, components, component)
        if (component->value) {
            int3_hashmap* hashmap = component->value;
            dispose_hashmap_int3(world, hashmap);
            component->value = NULL;
        }
    }
}*/