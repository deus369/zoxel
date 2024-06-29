typedef struct {
    uint32_t seed;
} SaveRealm;
SaveRealm realm_save;

// clearing:
// memset(&myGame, 0, sizeof(GameSave));
load_and_save_data(SaveRealm, realm)
