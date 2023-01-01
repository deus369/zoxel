// start screen when player first inputs with a device
#define game_state_start 0x00

// main menu and starting game state
#define game_state_menu 0x01

// starting game, loading things, count down
#define game_state_pre_play 0x02

// playing inside game
#define game_state_play 0x03

// paused the game
#define game_state_paused 0x04

// end of level ui, before going back to main menu
#define game_state_end 0x05