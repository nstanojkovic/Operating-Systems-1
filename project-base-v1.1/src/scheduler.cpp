//
// Created by marko on 20.4.22..
//

#include "../h/scheduler.hpp"
//#include "../h/pcb.hpp"

List<PCB> Scheduler::readyThreadQueue;


PCB *Scheduler::get()
{
    PCB* p=readyThreadQueue.removeFirst();
    broj=readyThreadQueue.broj;
    return p;
}

void Scheduler::put(PCB *thread)
{
    readyThreadQueue.addLast(thread);
    broj=readyThreadQueue.broj;
}

Scheduler *Scheduler::getInstance() {
    if(instance== nullptr){
        instance=new Scheduler();
    }

    return instance;
}

Scheduler* Scheduler::instance= nullptr;
int Scheduler::broj=readyThreadQueue.broj;





