//! Resets a single key!
void reset_key(PhysicalButton *key)
{
    if (key->pressed_this_frame)
    {
        key->pressed_this_frame = false;
    }
    if (key->released_this_frame)
    {
        key->released_this_frame = false;
    }
}

void reset_keyboard(ecs_world_t *world, ecs_entity_t keyboard_entity)
{
    if (!keyboard_entity || !ecs_is_alive(world, keyboard_entity))
    {
        return;
    }
    ecs_defer_begin(world);
    Keyboard *keyboard = ecs_get_mut(world, keyboard_entity, Keyboard);
    reset_key(&keyboard->space);
    reset_key(&keyboard->escape);
    reset_key(&keyboard->enter);
    reset_key(&keyboard->left_alt);
    reset_key(&keyboard->right_alt);
    reset_key(&keyboard->left_shift);
    reset_key(&keyboard->right_shift);
    reset_key(&keyboard->a);
    reset_key(&keyboard->b);
    reset_key(&keyboard->c);
    reset_key(&keyboard->d);
    reset_key(&keyboard->e);
    reset_key(&keyboard->f);
    reset_key(&keyboard->g);
    reset_key(&keyboard->h);
    reset_key(&keyboard->i);
    reset_key(&keyboard->j);
    reset_key(&keyboard->k);
    reset_key(&keyboard->l);
    reset_key(&keyboard->m);
    reset_key(&keyboard->n);
    reset_key(&keyboard->o);
    reset_key(&keyboard->p);
    reset_key(&keyboard->q);
    reset_key(&keyboard->r);
    reset_key(&keyboard->s);
    reset_key(&keyboard->t);
    reset_key(&keyboard->u);
    reset_key(&keyboard->v);
    reset_key(&keyboard->w);
    reset_key(&keyboard->x);
    reset_key(&keyboard->y);
    reset_key(&keyboard->z);
    reset_key(&keyboard->down);
    reset_key(&keyboard->up);
    reset_key(&keyboard->left);
    reset_key(&keyboard->right);
    ecs_modified(world, keyboard_entity, Keyboard);
    ecs_defer_end(world);
}