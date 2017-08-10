#ifndef THREADPOOL_H
#define THREADPOOL_H
#define THREADPOOL_MAX 1024
#include <pthread.h>

class threadPool
{
  private:
    pthread_t threads[THREADPOOL_MAX];

  public:
    threadPool();
    void create(void *(*callBackFunction)(void *dataPtr));
    void join();
    ~threadPool();
};

#endif /* THREADPOOL_H */