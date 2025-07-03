#include "realm.c"
#include "character.c"
#include "label.c"

void set_linked_item(ecs_world_t *world, const ecs_entity_t user, const int index, const ecs_entity_t e) {
    if (!zox_has(user, ItemLinks)) {
        return;
    }
    zox_get_muter(user, ItemLinks, datas)
    if (index >= datas->length) {
        return;
    }
    datas->value[index] = e;
}