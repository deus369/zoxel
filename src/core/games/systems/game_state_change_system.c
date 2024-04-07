// when state changes, we can do events here
//      game has children which includes all players
//      game_state_start > game_state_menu = load main menu for player 1
//      game_state_menu > pre play = unload main menu, load a countdown / load ui
//      game_state_pre_play > play = load game, load player characters
//      game_state_play > game_state_paused = pause entities in game
//      game_state_paused > game_state_play = unpause entities
//      game_state_play | game_state_paused > game_state_end = go to exit ui
//      game_state_end > game_state_menu = return to main menu scene + ui

