#ifdef zox_windows

    typedef SRWLOCK SpinLock;
    #define SPINLOCK_INIT ((SpinLock)SRWLOCK_INIT)

    static inline void spinlock_init(SpinLock *lock) {
        InitializeSRWLock(lock);
    }

    static inline void spin_lock(SpinLock *lock) {
        AcquireSRWLockExclusive(lock);
    }

    static inline void spin_unlock(SpinLock *lock) {
        ReleaseSRWLockExclusive(lock);
    }



    /*#include <stdatomic.h>

    typedef struct {
        atomic_flag flag;
    } SpinLock;

    #define SPINLOCK_INIT (SpinLock){ .flag = ATOMIC_FLAG_INIT }

    static inline void spin_lock(SpinLock *lock) {

    }

    static inline void spin_unlock(SpinLock *lock) {

    }*/

#else

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

#endif