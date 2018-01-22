//
// Created by kostarubtsov1990 on 22/01/18.
//

#include "ThreadPool.h"
#include <unistd.h>



ThreadPool::ThreadPool(int threadsNum) : stopped(false){
    threads = new pthread_t [threadsNum];
    for (int i = 0; i < threadsNum; i++) {
        pthread_create(threads + i, NULL, Execute, this);
    }
    pthread_mutex_init(&lock, NULL);

}

void* ThreadPool::Execute(void *args) {
    ThreadPool* pool = (ThreadPool*)args;
    pool->ExecuteTask();
}

void ThreadPool::AddTask(Task *task) {
    taskQueue.push(task);
}

void ThreadPool::ExecuteTask() {
    while (!stopped) {
        pthread_mutex_lock(&lock);
        if (!taskQueue.empty()) {
            Task* task = taskQueue.front();
            taskQueue.pop();
            pthread_mutex_unlock(&lock);
            task->execute();
            //need to check this line of code
            delete task;
        }
        else{
            pthread_mutex_unlock(&lock);
            sleep(1);
        }
    }
}

void ThreadPool::Terminate() {
    pthread_mutex_destroy(&lock);
    stopped = true;
}

ThreadPool::~ThreadPool() {
    delete[] threads;
    //also need to delete all the remaining task that are not yet completed
}