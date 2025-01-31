void set_new_socket(ecs_world_t *world, ecs_entity_t e, int port) {
    zox_set(e, SocketLink, { open_socket(port) })
}

ECS_DTOR(SocketLink, ptr, {
    if (ptr->value != -1) {
        if (close(ptr->value) < 0) perror(" ! [SocketLink] failed to close");
        ptr->value = -1;
    }
})
