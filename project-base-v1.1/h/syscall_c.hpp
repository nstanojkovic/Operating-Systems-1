//
// Created by os on 7/16/22.
//

#ifndef PROJECT_BASE_V1_1_SYSCALL_C_HPP
#define PROJECT_BASE_V1_1_SYSCALL_C_HPP

#include "../lib/hw.h"
#include "../lib/console.h"
//#include "../lib/mem.h"



extern  void* mem_alloc(size_t sz);
extern int mem_free(void*);





class PCB;
typedef PCB* thread_t;

extern int thread_create(
        thread_t* handle,
        void(*start_routine)(void*),
        void* arg

);


typedef struct Pomocna{

    void(*start)(void*);

}Pomocna;

extern void* nemanja();


extern int thread_exit();
extern void thread_dispatch();


class Semaphore;
typedef Semaphore* sem_t;

extern int sem_open(
        sem_t* handle,
        unsigned init

        );

extern int sem_wait (sem_t id);
extern int sem_signal (sem_t id);
extern int sem_close (sem_t id);

const int EOF = -1;

extern char getc ();
extern void putc(char);



#endif //PROJECT_BASE_V1_1_SYSCALL_C_HPP