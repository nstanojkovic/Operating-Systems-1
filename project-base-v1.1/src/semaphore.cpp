//
// Created by os on 7/23/22.
//


#include "../h/semaphore.hpp"

uint64 s = 0;

#define LOCK() while(copy_and_swap(s, 0, 1))
#define UNLOCK() while(copy_and_swap(s, 1, 0))



void Semaphore::wait(Semaphore* sem) {


if(--sem->init<0) {

   /* if(PCB::running->idle==1 && Scheduler::broj>1){
         // __putc('s');
        PCB *old = PCB::running;
        if (!old->isFinished()) { Scheduler::put(old); }
        PCB::running = Scheduler::get();

    }*/

   if(Scheduler::broj>0) {
       sem->blocked.addLast(PCB::running);

       PCB *oldRunning = PCB::running;
       PCB *newRunning = PCB::running = Scheduler::get();


       PCB::contextSwitch(&oldRunning->context, &newRunning->context);
   }else{
       //sem->init++;
   }

}




}

void Semaphore::signal(Semaphore* sem) {

    int n=++sem->init;

    if(n==0 ) {
        if (sem->blocked.broj > 0)
            Scheduler::put(sem->blocked.removeFirst());


    }else if(n<0 && Scheduler::broj==(-n)){
        if (sem->blocked.broj > 0)
            Scheduler::put(sem->blocked.removeFirst());
    }






}

Semaphore *Semaphore::createSemaphore(int in) {
    return new Semaphore(in);
}

void Semaphore::close(Semaphore* s) {

    while(s->blocked.peekFirst()){Scheduler::put(s->blocked.removeFirst());
    }
   s->init=0;



}




