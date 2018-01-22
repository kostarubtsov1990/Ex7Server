//
// Created by kostarubtsov1990 on 22/01/18.
//

#include "Task.h"



Task::Task(void *(* func)(void* args), void *args):func(func), args(args) {}

void Task::execute() {
    func(args);
}