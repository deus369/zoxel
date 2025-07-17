typedef struct {
    uint seed;
} SaveRealm;
SaveRealm realm_save;
// memset(&myGame, 0, sizeof(GameSave));
create_load_and_save_functions(SaveRealm, realm)
