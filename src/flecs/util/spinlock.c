#include <stdatomic.h>

typedef struct {
    atomic_flag flag;
} SpinLock;

#define SPINLOCK_INIT (SpinLock){ .flag = ATOMIC_FLAG_INIT }

static inline void spin_lock(SpinLock *lock) {
    while (atomic_flag_test_and_set_explicit(&lock->flag, memory_order_acquire)) {
        // optionally: sched_yield();
    }
}

static inline void spin_unlock(SpinLock *lock) {
    atomic_flag_clear_explicit(&lock->flag, memory_order_release);
}
