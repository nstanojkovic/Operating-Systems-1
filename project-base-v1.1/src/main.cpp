//
// Created by marko on 20.4.22..
//



/*extern "C"{
#include "../h/syscall_c.hpp"
}
 */


#include "../h/userMain.hpp"
#include "../h/riscv.hpp"
#include "../lib/hw.h"
#include "../lib/console.h"
//#include "../lib/mem.h"
#include "../h/syscall_c.hpp"
#include "../h/memoryAllocator.hpp"


#include "../test/buffer.hpp"

//Semaphore* waitForAll;



uint64 prekidna;
int main()
{
     prekidna=Riscv::r_stvec();


   Riscv::w_stvec((uint64) &Riscv::supervisorTrap);

    //Riscv::mc_sstatus(Riscv::SSTATUS_SPP);



//    MemoryAllocator::_mem_alloc(60);
 //   putc('A');

  /* if(MemoryAllocator::_mem_free(MemoryAllocator::_mem_alloc(60))==0){
       putc('D');
   }
   else{
       putc('A');
   }*/



//Data* d1=(Data*) mem_alloc(1024);
//Data* d2=(Data*) mem_alloc(130);
//Data* d3=(Data*) mem_alloc(50);
  //  putc('a');
//if(d3){

//}
/*if(mem_free(d3)==0){
    putc('a');
}else{
    putc('n');
}
  if(mem_free(d2)==0){
        putc('a');
    }else{
        putc('n');
    }
    if(mem_free(d1)==0){
        putc('a');
    }else{
        putc('n');
    }

    Data* d4=(Data*) mem_alloc(1024);
    Data* d5=(Data*) mem_alloc(130);
    Data* d6=(Data*) mem_alloc(50);

    if(mem_free(d4)==0){
        putc('a');
    }else{
        putc('n');
    }
    if(mem_free(d5)==0){
        putc('a');
    }else{
        putc('n');
    }
    if(mem_free(d6)==0){
        putc('a');
    }else{
        putc('n');
    }*/



userMain();



return 0;


}
