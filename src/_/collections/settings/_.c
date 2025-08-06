const uint max_safety_checks_hashmap = 1024;
#ifndef zox_windows
    const byte hashmap_safety_locks = 1;
    const byte nodes_w_safety_locks = 1;
    const byte nodes_r_safety_locks = 1;
#else
    const byte hashmap_safety_locks = 1;
    const byte nodes_w_safety_locks = 1;
    const byte nodes_r_safety_locks = 1;
#endif


#ifdef zox_windows

    typedef SRWLOCK zox_lock;
    #define ZOX_LOCK_INIT SRWLOCK_INIT

    #define zox_lock_init(lock_ptr)       InitializeSRWLock(lock_ptr)
    #define zox_lock_destroy(lock_ptr)    ((void)0)  /* SRWLOCK doesn't need destroy */

    #define zox_lock_read(lock_ptr)       AcquireSRWLockShared((PSRWLOCK)(zox_lock*)lock_ptr)
    #define zox_lock_write(lock_ptr)      AcquireSRWLockExclusive((PSRWLOCK)(zox_lock*)lock_ptr)

    #define zox_unlock_read(lock_ptr)     ReleaseSRWLockShared((PSRWLOCK)(zox_lock*)lock_ptr)
    #define zox_unlock_write(lock_ptr)    ReleaseSRWLockExclusive((PSRWLOCK)(zox_lock*)lock_ptr)

#else

    typedef pthread_rwlock_t zox_lock;
    #define ZOX_LOCK_INIT PTHREAD_RWLOCK_INITIALIZER

    #define zox_lock_init(lock_ptr)       pthread_rwlock_init(lock_ptr, NULL)
    #define zox_lock_destroy(lock_ptr)    pthread_rwlock_destroy(lock_ptr)

    #define zox_lock_read(lock_ptr)       pthread_rwlock_rdlock((pthread_rwlock_t*)lock_ptr)
    #define zox_lock_write(lock_ptr)      pthread_rwlock_wrlock((pthread_rwlock_t*)lock_ptr)

    #define zox_unlock_read(lock_ptr)     pthread_rwlock_unlock((pthread_rwlock_t*)lock_ptr)
    #define zox_unlock_write(lock_ptr)    pthread_rwlock_unlock((pthread_rwlock_t*)lock_ptr)
#endif