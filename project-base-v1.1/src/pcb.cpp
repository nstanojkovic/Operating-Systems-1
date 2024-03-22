//
// Created by os on 7/17/22.
//


#include "../h/pcb.hpp"
#include "../h/riscv.hpp"





void petlja(void* s){
    while(1){
        __putc('Y');

    }
}






PCB *PCB::running = nullptr;

uint64 PCB::timeSliceCounter = 0;
int PCB::id=0;


PCB *PCB::createThread(Body body,void* arg,void* s)
{

    id=id+1;
    if(id==1){
    Scheduler::put(createThread(&petlja, nullptr,new uint64[DEFAULT_STACK_SIZE]));


    }

    return new PCB(body, arg,s);
}




void PCB::yield()
{

    uint64 volatile kod=0x0000000000000014UL;

    __asm__ volatile("mv a0,%0"::"r" (kod));
    __asm__ volatile ("ecall");
}

void PCB::dispatch()
{
    if(Scheduler::broj==1){
       PCB *old = running;
      //  if (!old->isFinished()) { Scheduler::put(old); }
     // running = Scheduler::get();
      //  if (old != running)
       PCB::contextSwitch(&old->context, &running->context);
    }
    else {
        if (running == nullptr)
            running = Scheduler::get();
        PCB *old = running;
        if (!old->isFinished()) { Scheduler::put(old); }
        running = Scheduler::get();

        PCB::contextSwitch(&old->context, &running->context);

    }
}

void PCB::threadWrapper()
{

    Riscv::popSppSpie();

    running->body(running->argument);
    running->setFinished(true);
    PCB::dispatch();

}
int PCB::exit() {
    PCB* current=PCB::running;
    running->setFinished(true);
    dispatch();
    if(current==running){
        return 0;
    }
    else{
        return -5;
    }
}

bool PCB::provera() {
    if(running->idle==1)return true;
    return false;
}




