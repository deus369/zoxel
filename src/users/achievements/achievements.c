#ifndef zox_achievements
#define zox_achievements

zox_declare_user_data(Achievement)
// Realm Contains all Achievements
// Save/Load Players progress - per save game
// Toast UI -> show popup at top right when completed - this will trigger steam achievements at bottom right
// Make sure to disable Steam Achievements while testing

zox_begin_module(Achievements)
zox_define_user_data(Achievement)
zoxel_end_module(Achievements)

#endif
