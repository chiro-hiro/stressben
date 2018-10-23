#include "threadPool.h"

threadPool::threadPool() {}

void threadPool::create(void *(*callBackFunction)(void *dataPtr)) {
    for (int i = 0; i < THREADPOOL_MAX; i++) {
        pthread_create(&threads[i], NULL, callBackFunction, NULL);
    }
}

void threadPool::join() {
    for (int i = 0; i < THREADPOOL_MAX; i++) {
        pthread_join(threads[i], NULL);
    }
}

threadPool::~threadPool() {}