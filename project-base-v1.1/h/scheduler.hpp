//
// Created by marko on 20.4.22..
//

#ifndef OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_SCHEDULER_HPP
#define OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_SCHEDULER_HPP

#include "list.hpp"



class PCB;


class Scheduler
{
private:
    static List<PCB> readyThreadQueue;

public:
    static PCB *get();

    static void put(PCB *thread);
    static Scheduler* getInstance();
    static int broj;



private:
    static Scheduler* instance;

    Scheduler(const Scheduler&);
    Scheduler(){


    }



};

#endif //OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_SCHEDULER_HPP