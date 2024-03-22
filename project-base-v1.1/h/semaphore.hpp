//
// Created by os on 7/23/22.
//

#ifndef PROJECT_BASE_V1_1_SEMAPHORE_HPP
#define PROJECT_BASE_V1_1_SEMAPHORE_HPP

#include "list.hpp"
#include "pcb.hpp"
#include "syscall_c.hpp"


extern "C" uint64 copy_and_swap(uint64 &lock, uint64 expected, uint64 desired);
class Semaphore{

private:
    int init;
    List<PCB> blocked;
    int broj;

public:
 //   ~Semaphore(){delete this;}

    int getInit() const {
        return init;
    }
    static Semaphore* createSemaphore(int in);



    Semaphore (int init):init(init){
        broj=0;

}
   static void wait(Semaphore*);

    static void signal(Semaphore*);
    static void close(Semaphore*);

};



#endif //PROJECT_BASE_V1_1_SEMAPHORE_HPP
