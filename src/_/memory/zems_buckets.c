#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>

#define ZEMS_MAGIC 0xFEEDBABE
#define NUM_CLASSES 16

static const size_t class_sizes[NUM_CLASSES] = {
    8,         // 0: Tiny tokens
    16,        // 1
    32,        // 2
    64,        // 3
    128,       // 4
    256,       // 5
    512,       // 6
    1024,      // 7: Kilobyte kings
    2048,      // 8
    4096,      // 9
    8192,      // 10
    16384,     // 11
    32768,     // 12: Midweight muscle
    524288,    // 13: 512 KB — buffer territory
    4194304,   // 14: 4 MB — texture dominion
    16777216   // 15: 16 MB — megaboss arena
};


#define REFILL_COUNT 64

typedef struct BlockHeader {
    uint32_t magic;
    size_t capacity;
    int class_index;
    struct BlockHeader *next;
} BlockHeader;

static BlockHeader *free_lists[NUM_CLASSES] = { 0 };
static atomic_flag zems_lock = ATOMIC_FLAG_INIT;

static inline void lock_mem() {
    // while (atomic_flag_test_and_set_explicit(&zems_lock, memory_order_acquire));
}
static inline void unlock_mem() {
    // atomic_flag_clear_explicit(&zems_lock, memory_order_release);
}

void init_zems() {
    lock_mem();
    for (int i = 0; i < NUM_CLASSES; i++) {
        free_lists[i] = NULL;
    }
    unlock_mem();
}

void free_zems() {
    lock_mem();
    for (int i = 0; i < NUM_CLASSES; i++) {
        BlockHeader *hdr = free_lists[i];
        while (hdr) {
            BlockHeader *next = hdr->next;
            hdr->magic = 0;
            free(hdr);
            hdr = next;
        }
        free_lists[i] = NULL;
    }
    unlock_mem();
}

static void refill_class(int idx) {
    size_t size = class_sizes[idx];
    size_t full_size = sizeof(BlockHeader) + size;

    for (int i = 0; i < REFILL_COUNT; i++) {
        BlockHeader *hdr = (BlockHeader *) malloc(full_size);
        zox_log("-> [%i] new pool malloc [%i]", i, full_size);
        if (!hdr) {
            zox_log_error("[ZEMS] Failed to refill class %d", idx);
            abort();
        }
        hdr->magic = ZEMS_MAGIC;
        hdr->capacity = size;
        hdr->class_index = idx;

        lock_mem();
        hdr->next = free_lists[idx];
        free_lists[idx] = hdr;
        unlock_mem();
    }
}

void* zalloc(uint length) {
    if (length == 0) {
        return NULL;
    }
    size_t needed = (size_t)length;
    int idx = 0;
    while (idx < NUM_CLASSES && class_sizes[idx] < needed) {
        idx++;
    }

    if (idx == NUM_CLASSES) {
        zox_log_error("[ZEMS] Allocation too large: %zu bytes (limit %zu)", needed, class_sizes[NUM_CLASSES - 1]);
        return NULL;
    }

    lock_mem();
    BlockHeader *block = free_lists[idx];
    if (!block) {
        unlock_mem();
        refill_class(idx);
        lock_mem();
        block = free_lists[idx];
        if (!block) {
            unlock_mem();
            zox_log_error("[ZEMS] Failed to allocate block for class %d\n", idx);
            return NULL;
        }
    }

    free_lists[idx] = block->next;
    unlock_mem();

    block->magic = ZEMS_MAGIC;
    zox_log("+ zallocd [%i]", idx);
    return (void*)(block + 1);
}

void zee(void *ptr) {
    if (!ptr) {
        zox_log_error("missing pointer in zee");
        return;
    }

    BlockHeader *hdr = ((BlockHeader *)ptr) - 1;
    if (hdr->magic != ZEMS_MAGIC) {
        zox_log_error("[ZEMS] zee(): invalid or corrupted pointer %p (magic = 0x%X)", ptr, hdr->magic);
        return;
    }

    int idx = hdr->class_index;
    if (idx < 0 || idx >= NUM_CLASSES) {
        zox_log_error("[ZEMS] zee(): corrupt class_index %d", idx);
        return;
    }

    hdr->magic = 0; // poison

    lock_mem();
    hdr->next = free_lists[idx];
    free_lists[idx] = hdr;
    unlock_mem();
    zox_log("- zeed [%i]", idx);
}

void* rezalloc(void *ptr, uint new_length) {
    if (!ptr) return zalloc(new_length);
    if (new_length == 0) {
        zee(ptr);
        return NULL;
    }

    BlockHeader *old_hdr = (BlockHeader*)ptr - 1;
    if (old_hdr->magic != ZEMS_MAGIC) {
        zox_log_error("[ZEMS] rezalloc(): invalid pointer %p (magic = 0x%X)", ptr, old_hdr->magic);
        abort();
    }

    size_t old_capacity = old_hdr->capacity;
    int old_idx = old_hdr->class_index;

    if (old_idx >= 0 && old_idx < NUM_CLASSES && (size_t)new_length <= old_capacity) {
        return ptr;
    }

    void *new_ptr = zalloc(new_length);
    if (!new_ptr) {
        return NULL;
    }

    size_t copy_size = old_capacity < new_length ? old_capacity : new_length;
    memcpy(new_ptr, ptr, copy_size);
    zee(ptr);
    return new_ptr;
}
