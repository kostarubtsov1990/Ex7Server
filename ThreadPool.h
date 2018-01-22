//
// Created by kostarubtsov1990 on 22/01/18.
//

#ifndef EX5SERVER_THREADPOOL_H
#define EX5SERVER_THREADPOOL_H


#include "Task.h"
#include <queue>
#include <pthread.h>

using namespace std;


class ThreadPool {
public:
    ThreadPool(int threadsNum);
    void AddTask(Task * task);
    void Terminate();
    virtual ~ThreadPool();

private:
    queue <Task*> taskQueue;
    pthread_t* threads;
    void ExecuteTask();
    bool stopped;
    pthread_mutex_t lock;

    static void * Execute(void* args);

};


#endif //EX5SERVER_THREADPOOL_H
