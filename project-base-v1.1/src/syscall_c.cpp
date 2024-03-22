//
// Created by os on 7/16/22.
//

#include "../h/syscall_c.hpp"
#include "../lib/console.h"
#include "../lib/hw.h"
#include "../h/riscv.hpp"



void*  mem_alloc(size_t sz){

    //  if(sz<64 || sz>1024)sz=64;

if(sz<MEM_BLOCK_SIZE)sz=MEM_BLOCK_SIZE;
    if(sz%MEM_BLOCK_SIZE!=0){
        sz=((sz/MEM_BLOCK_SIZE)+1)*MEM_BLOCK_SIZE;
    }

    uint64 volatile szz=(uint64)sz;
    __asm__ volatile("mv a1,%0"::"r"(szz));

    uint64 volatile kod=0x0000000000000001UL;

    __asm__ volatile("mv a0,%0" :: "r" (kod));


    __asm__ volatile("ecall");

  uint64   a;
    __asm__ volatile ("mv %0,a0":"=r" (a));


    return (void*)a;


}



int mem_free(void* p) {


    uint64 volatile pp=(uint64)p;
    __asm__ volatile("mv a1,%0"::"r"(pp));

    uint64 volatile kod=0x0000000000000002UL;
    __asm__ volatile("mv a0,%0"::"r" (kod));

    __asm__ volatile("ecall");

    uint64 bb;
    __asm__ volatile ("mv %0,a0":"=r" (bb));

    return (int)bb;

}





int thread_create(
        thread_t* handle,
        void(*start_routine)(void*),
        void* arg
){



    Pomocna p;
    p.start=start_routine;

    uint64* volatile parametar=(uint64*)(&p);
    uint64 volatile pp=*(parametar);


    uint64* volatile parametar1=(uint64*)handle;
    uint64 volatile pp1=(*parametar1);
    __asm__ volatile("mv a1,%0"::"r"(pp1));


    uint64 volatile argument=(uint64)arg;
    __asm__ volatile("mv a6,%0"::"r"(argument));

    uint64 volatile stack_space;
    stack_space=((uint64)(mem_alloc(DEFAULT_STACK_SIZE)));
   // uint64* volatile stack_space=new uint64[DEFAULT_STACK_SIZE];
    __asm__ volatile("mv a7,%0"::"r" ((uint64)stack_space));





    uint64 volatile kod=0x00000000000000011UL;
    __asm__ volatile("mv a0,%0"::"r" (kod));


    __asm__ volatile("mv a2,%0"::"r"(pp));






    __asm__ volatile("ecall");

    uint64 bb;
    __asm__ volatile ("mv %0,a0":"=r" (bb));
    return (int)bb;

}
void thread_dispatch(){
    uint64 volatile kod=0x00000000000000013UL;
    __asm__ volatile("mv a0,%0"::"r" (kod));
    __asm__ volatile("ecall");
}

int thread_exit(){
    uint64 volatile kod=0x00000000000000012UL;
    __asm__ volatile("mv a0,%0"::"r" (kod));
    __asm__ volatile("ecall");

    uint64 bb;
    __asm__ volatile ("mv %0,a0":"=r" (bb));
    return (int)bb;
}

void* nemanja(){
    while(1){

    }
}

int sem_open(sem_t *handle,unsigned  init) {


    __asm__ volatile("mv a2,%0"::"r"((int)(init)));



    uint64 volatile h=(uint64)handle;

    __asm__ volatile("mv a1,%0"::"r"(h));




    uint64 volatile kod=0x00000000000000021UL;
    __asm__ volatile("mv a0,%0"::"r" (kod));
    __asm__ volatile("ecall");

    Semaphore* pr=(Semaphore*)(*handle);
    if(pr){

    }

    uint64 bb;
    __asm__ volatile ("mv %0,a0":"=r" (bb));
    return (int)bb;
}

int sem_wait(sem_t id) {

    uint64 volatile h=(uint64)id;

    __asm__ volatile("mv a1,%0"::"r"(h));

    uint64 volatile kod=0x00000000000000023UL;
    __asm__ volatile("mv a0,%0"::"r" (kod));

    __asm__ volatile("ecall");

    /*  uint64 bb;
      __asm__ volatile ("mv %0,a0":"=r" (bb));
      return (int)bb;

      */
    return 0;

}

int sem_signal(sem_t id) {

    uint64 volatile h=(uint64)id;

    __asm__ volatile("mv a1,%0"::"r"(h));

    uint64 volatile kod=0x00000000000000024UL;
    __asm__ volatile("mv a0,%0"::"r" (kod));

    __asm__ volatile("ecall");

    /*  uint64 bb;
      __asm__ volatile ("mv %0,a0":"=r" (bb));
      return (int)bb;

      */
    return 0;
}
int sem_close(sem_t id){

    uint64 volatile h=(uint64)id;

    __asm__ volatile("mv a1,%0"::"r"(h));

    uint64 volatile kod=0x00000000000000022UL;
    __asm__ volatile("mv a0,%0"::"r" (kod));

    __asm__ volatile("ecall");

    /*  uint64 bb;
      __asm__ volatile ("mv %0,a0":"=r" (bb));
      return (int)bb;

      */
    return 0;

}


char getc (){
    uint64 volatile kod=0x00000000000000041UL;
    __asm__ volatile("mv a0,%0"::"r" (kod));

    __asm__ volatile("ecall");

    uint64 bb;
    __asm__ volatile ("mv %0,a0":"=r" (bb));
    return (int)bb;

}
void putc(char a){
    uint64 volatile aa=a;

    __asm__ volatile("mv a1,%0"::"r" (aa));

    uint64 volatile kod=0x00000000000000042UL;
    __asm__ volatile("mv a0,%0"::"r" (kod));

    __asm__ volatile("ecall");


}




