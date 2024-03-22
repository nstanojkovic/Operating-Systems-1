//
// Created by marko on 20.4.22..
//


#include "../h/syscall_c.hpp"
//#include "../h/memoryAllocator.hpp"
#include "../lib/mem.h"





void *operator new(size_t sz)
{

  if(sz<MEM_BLOCK_SIZE){
        sz=MEM_BLOCK_SIZE;
    }
    else if(sz%MEM_BLOCK_SIZE!=0){
        sz=((sz/MEM_BLOCK_SIZE)+1)*MEM_BLOCK_SIZE;
    }

    return __mem_alloc(sz);

}

void *operator new[](size_t sz)
{
    if(sz<MEM_BLOCK_SIZE){
        sz=MEM_BLOCK_SIZE;
    }
    else if(sz%MEM_BLOCK_SIZE!=0){
        sz=((sz/MEM_BLOCK_SIZE)+1)*MEM_BLOCK_SIZE;
    }

    return __mem_alloc(sz);
}

void operator delete(void *p) noexcept
{
__mem_free(p);

}

void operator delete[](void *p) noexcept
{
__mem_free(p);

}