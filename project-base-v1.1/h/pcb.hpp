//
// Created by os on 7/17/22.
//

#ifndef PROJECT_BASE_V1_1_PCB_HPP
#define PROJECT_BASE_V1_1_PCB_HPP


#include "../lib/hw.h"

#include "scheduler.hpp"
#include "../lib/console.h"



extern  void petlja(void*);

class PCB {
public:
    ~PCB() { delete[] stack; }

    bool isFinished() const { return finished; }

    void setFinished(bool value) { finished = value; }

    uint64 getTimeSlice() const { return timeSlice; }

    using Body = void (*)(void*);


    static PCB *createThread(Body body,void*,void*);

    static void yield();

    static PCB *running;
    static int id;
    static bool provera();



private:
    PCB(Body body,void* arg,void* s) :
            timeSlice(DEFAULT_TIME_SLICE),
            finished(false)
    {
        this->body=body;
        this->argument=arg;
        this->stack=body != nullptr ?new uint64[STACK_SIZE] : 0;
       // this->stack=body != nullptr ?(uint64*)s : 0;

        context={(uint64) &threadWrapper,
                 stack != nullptr ? (uint64) &stack[STACK_SIZE] : 0
        };
        this->argument=arg;
        if (body != nullptr) {
            Scheduler::put(this);
        }
        if(id==2){
            idle=1;
        }else{
            idle=0;
        }


    }


    struct Context
    {
        uint64 ra;
        uint64 sp;
    };

    Body body;
    uint64 *stack;
    Context context;
    uint64 timeSlice;
    bool finished;
    void* argument;
    int idle;



    friend class Riscv;
    friend  class Semaphore;

    static void threadWrapper();

    static void contextSwitch(Context *oldContext, Context *runningContext);

    static void dispatch();
    static int exit();

    static uint64 timeSliceCounter;

    static uint64 constexpr STACK_SIZE = DEFAULT_STACK_SIZE;
    static uint64 constexpr TIME_SLICE = DEFAULT_TIME_SLICE;
};


#endif //PROJECT_BASE_V1_1_PCB_HPP