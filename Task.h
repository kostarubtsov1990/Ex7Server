//
// Created by kostarubtsov1990 on 22/01/18.
//

#ifndef EX5SERVER_TASK_H
#define EX5SERVER_TASK_H


class Task {
public:
    Task(void* (*func)(void* args), void* args);

    void execute ();

private:
    void * (*func)(void *args);
    void *args;
};


#endif //EX5SERVER_TASK_H
