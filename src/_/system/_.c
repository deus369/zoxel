static __thread int local_thread_index = -1;

int get_thread_index() {
    if (local_thread_index == -1) {
        static int next_index = 0;
        static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_lock(&lock);
        local_thread_index = next_index++;
        pthread_mutex_unlock(&lock);
    }
    return local_thread_index;
}