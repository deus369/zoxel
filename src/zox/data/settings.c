// shared boot things
extern unsigned char is_split_screen;
extern ecs_entity_t fps_display;
#define main_camera_rotation_speed 60 * 0.22f
ecs_entity_t zoxel_main_menu;
float4 main_menu_rotation_speed;
typedef unsigned char (*boot_zox)(ecs_world_t*);
boot_zox boot_event;
