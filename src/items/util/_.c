#include "character.c"
#include "label.c"

void set_linked_item(ecs_world_t *world,
    const ecs_entity_t user,
    const int index,
    const ecs_entity_t e)
{
    if (!zox_valid(user) || !zox_has(user, ItemLinks)) {
        return;
    }
    zox_mut_begin(user, ItemLinks, datas)
    if (index >= datas->length) {
        return;
    }
    datas->value[index] = e;
    zox_mut_end(user, ItemLinks)
}