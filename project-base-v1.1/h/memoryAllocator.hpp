//
// Created by os on 7/21/22.
//
#include "../lib/hw.h"
#include "../lib/console.h"

#ifndef PROJECT_BASE_V1_1_MEMORYALLOCATOR_HPP
#define PROJECT_BASE_V1_1_MEMORYALLOCATOR_HPP


 typedef struct Data{

  // size_t* addr;
    Data*prev;
    Data* next;
    size_t size;
}Data;


class MemoryAllocator{


public:
    static void* _mem_alloc(size_t size);

    static int _mem_free(void* ptr);
    static MemoryAllocator* getInstance();
    static Data* freeMemHead;
    static Data* dataMemHead;
    static Data* freeMemLast;
    static Data* dataMemLast;
private:
    static MemoryAllocator* instance;
    static void setFreeMemHead();

    MemoryAllocator(const MemoryAllocator&);
    MemoryAllocator(){
   setFreeMemHead();
    }
    static int id;

};

#endif //PROJECT_BASE_V1_1_MEMORYALLOCATOR_HPP
