// HMMmm
char* player_vox_model = "playerer"; // playerer player grazor slime mrpenguin
const double respawn_time = 15;

// shit remove this atm, it doubles up for coop
double run_speed = 1.8;
double run_accceleration = 2.2;
float backwards_multiplier = 0.8f;
float2 player_movement_power = { 17, 19 };
float2 max_velocity3D = { 1.24f, 1.4f };

const byte zox_players_reverse_x = 0;
const byte zox_players_reverse_y = 0;
const byte zox_players_reverse_rotate_x = 0;
const byte zox_players_reverse_rotate_y = 0;
const double gamepad_rotate_multiplier_x = 0.04;
const double gamepad_rotate_multiplier_y = 0.03;
const double mouse_rotate_multiplier = 0.0032; // 0.008;
const float touchscreen_rotate_multiplier = 0.6f;
const float min_mouse_delta3 = 0.01f;
const float min_mouse_delta2 = 24.0f;
const float max_mouse_delta3 = 60.0f;
const float max_mouse_delta4 = 120.0f;
const float max_mouse_delta2 = 200.0f;
const double max_rotate_speed = 0.2; //  0.23;
#define disable_player_rotate_alpha_force