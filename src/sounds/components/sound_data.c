#define MAX_SOUND_DATA (44100 * 4) // max time for sound 4 seconds
#define MAX_SOUND_INSTANCES 64

static float sound_pool[MAX_SOUND_INSTANCES][MAX_SOUND_DATA];
static byte sound_pool_used[MAX_SOUND_INSTANCES] = {0};

float* soundpool_alloc() {
    for (int i = 0; i < MAX_SOUND_INSTANCES; i++) {
        if (!sound_pool_used[i]) {
            sound_pool_used[i] = 1;
            return sound_pool[i];
        }
    }
    return NULL; // no free chunk
}

void soundpool_free(float* ptr) {
    for (int i = 0; i < MAX_SOUND_INSTANCES; i++) {
        if (sound_pool[i] == ptr) {
            sound_pool_used[i] = 0;
            return;
        }
    }
}

typedef struct {
    uint length;
    float* value;   // point to our sound pool
} SoundData;
zoxc_custom(SoundData);

ECS_DTOR(SoundData, ptr, {
    if (ptr->value) {
        soundpool_free(ptr->value);
    }
})

// zoxc_array_l(SoundData, float, max_sound_data);

