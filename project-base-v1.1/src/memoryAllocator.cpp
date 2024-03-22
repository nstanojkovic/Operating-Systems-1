//
// Created by os on 7/21/22.
//

#include "../h/memoryAllocator.hpp"


MemoryAllocator *MemoryAllocator::getInstance() {
    if(instance== nullptr){
        instance=new MemoryAllocator();
    }

    return instance;
}

MemoryAllocator* MemoryAllocator::instance= nullptr;
Data* MemoryAllocator::freeMemHead= nullptr;
Data* MemoryAllocator::dataMemHead= nullptr;
Data* MemoryAllocator::freeMemLast= nullptr;
Data* MemoryAllocator::dataMemLast= nullptr;
int MemoryAllocator::id= 0;

void MemoryAllocator::setFreeMemHead() {
    freeMemHead=(Data*)HEAP_START_ADDR;
    // freeMemHead->addr=(size_t*)(freeMemHead+sizeof (Data));

    freeMemHead->size=(size_t)((size_t*)HEAP_END_ADDR - (size_t*)HEAP_START_ADDR-sizeof(Data));
    freeMemHead->next= nullptr;

    dataMemHead= nullptr;
    dataMemLast= nullptr;
    freeMemLast=freeMemHead;


    id=id+1;

}

void *MemoryAllocator::_mem_alloc(size_t size) {

    if(id==0)setFreeMemHead();

    Data *blk=freeMemHead;
    for(;blk!= nullptr;blk=blk->next)
    {
        if(blk->size>=(size))break;
    }
    if(blk== nullptr) {
        __putc('s');
        return nullptr;
    }

    //Data* newFree=(Data*)((size_t*)blk->addr + size);

    Data* newFree=(Data*)((size_t*)blk+size+sizeof(Data));


    if(blk==freeMemHead){
        newFree->size=freeMemHead->size-size-sizeof(Data);


        newFree->next= freeMemHead->next;
        newFree->prev= nullptr;

        freeMemHead=newFree;
        if(freeMemHead->size<MEM_BLOCK_SIZE){
            freeMemHead= nullptr;
            freeMemLast= nullptr;
        }
        else if(!freeMemHead->next){
            freeMemLast=freeMemHead;
        }

    }
    else if(blk==freeMemLast && blk!=freeMemHead){

        freeMemLast=blk->prev;
        freeMemLast->next= nullptr;
    }else{

        blk->prev->next=blk->next;
        blk->next->prev=blk->prev;
    }

    blk->size=size;


    if(dataMemHead== nullptr){
        blk->next= nullptr;
        blk->prev= nullptr;
        blk->size=size;
        //    blk->addr=(size_t*)(blk+sizeof(Data));
        dataMemHead=blk;
        dataMemLast=dataMemHead;

    }
    else if(dataMemHead->next== nullptr){
        dataMemHead->next=blk;
        blk->next= nullptr;
        blk->prev=dataMemLast;

        dataMemLast=blk;


    }else{

        blk->prev=dataMemLast;
        blk->next= nullptr;
        dataMemLast->next=blk;
        dataMemLast=blk;
    }

    //  blk->addr=(size_t*)(blk+sizeof(Data));

    return (void*)(blk+sizeof(Data));

}


int MemoryAllocator::_mem_free(void *ptr) {

    if(dataMemHead== nullptr){

        return -1;

    }





    Data* d=dataMemHead;

    for(;d!= nullptr;d=d->next) {

        // if (d->addr == (size_t *) ptr) {

        if((size_t*)(d+sizeof (Data))==(size_t*)ptr){



            if (d == dataMemHead) {

                dataMemHead = dataMemHead->next;
                dataMemHead->prev= nullptr;
                dataMemLast= dataMemHead;

            }else if(d==dataMemLast){
                d->prev->next= nullptr;
                dataMemLast=d->prev;
                d->prev= nullptr;
                d->next= nullptr;

            }else{
                d->prev->next=d->next;
                if(d->next)
                    d->next->prev=d->prev;

            }


            if(!freeMemHead){
                d->next= nullptr;
                d->prev= nullptr;

                freeMemHead=d;
                freeMemLast=freeMemHead;

            }else if(freeMemHead->next== nullptr){
                freeMemHead->next=d;
                d->prev=freeMemHead;
                d->next= nullptr;
                freeMemLast=d;


            }
            else {

                d->next= nullptr;
                freeMemLast->next=d;
                d->prev=freeMemLast;
                freeMemLast=d;

            }

        }


    }
    return 0;
}
