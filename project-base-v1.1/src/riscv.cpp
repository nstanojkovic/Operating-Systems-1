//
// Created by marko on 20.4.22..
//

#include "../h/riscv.hpp"


#include "../h/pcb.hpp"
#include "../h/semaphore.hpp"
#include "../h/main.hpp"


void Riscv::popSppSpie()
{
    __asm__ volatile("csrw sepc, ra");
    __asm__ volatile("sret");
}

void Riscv::handleSupervisorTrap() {

    uint64 scause = r_scause();
    /* if (scause == 0x0000000000000008UL || scause == 0x0000000000000009UL)
     {
         // interrupt: no; cause code: environment call from U-mode(8) or S-mode(9)
         uint64 volatile sepc = r_sepc() + 4;
         uint64 volatile sstatus = r_sstatus();
         PCB::timeSliceCounter = 0;
         PCB::dispatch();
         w_sstatus(sstatus);
         w_sepc(sepc);
     }
     else if (scause == 0x8000000000000001UL)
     {
         // interrupt: yes; cause code: supervisor software interrupt (CLINT; machine timer interrupt)
         mc_sip(SIP_SSIP);
         TCB::timeSliceCounter++;
         if (TCB::timeSliceCounter >= TCB::running->getTimeSlice())
         {
             uint64 volatile sepc = r_sepc();
             uint64 volatile sstatus = r_sstatus();
             TCB::timeSliceCounter = 0;
             TCB::dispatch();
             w_sstatus(sstatus);
             w_sepc(sepc);
         }
     }
     else if (scause == 0x8000000000000009UL)
     {
         // interrupt: yes; cause code: supervisor external interrupt (PLIC; could be keyboard)
         console_handler();
     }
     else */if (scause == 0x0000000000000009UL) {


        uint64 volatile kod;
        __asm__ volatile ("mv %0,a0":"=r" (kod));


        if (kod == 0x01) {

            uint64 volatile sepc = r_sepc() + 4;
            w_sepc(sepc);



            uint64 volatile parametar;

            __asm__ volatile ("mv %0,a1":"=r" (parametar));
            size_t volatile sz = (size_t) parametar;

            uint64 volatile sstatus = r_sstatus();
            void *volatile a = (void *) (__mem_alloc(sz));
            w_sstatus(sstatus);
            uint64 volatile aa = (uint64) a;


            __asm__ volatile("mv a0,%0"::"r" (aa));



        } else if (kod == 0x02) {

            uint64 volatile sepc = r_sepc() + 4;
            w_sepc(sepc);

            uint64 volatile parametar;

            __asm__ volatile ("mv %0,a1":"=r" (parametar));

            uint64 *volatile parametar1 = (uint64 *) (&parametar);


            uint64 m = __mem_free(parametar1);

            __asm__ volatile("mv a0,%0"::"r" (m));


        } else if (kod == 0x11) {

            uint64 volatile sepc = r_sepc() + 4;
            w_sepc(sepc);


            uint64 volatile parametar1;
            uint64 volatile parametar2;
            uint64 volatile parametar4;
            uint64 volatile parametar3;


            __asm__ volatile ("mv %0,a1":"=r" (parametar1));
            __asm__ volatile ("mv %0,a2":"=r" (parametar2));
            __asm__ volatile ("mv %0,a6":"=r" (parametar3));
            __asm__ volatile ("mv %0,a7":"=r" (parametar4));


            uint64 *volatile adresa = (uint64 *) (&parametar2);
            Pomocna *volatile adresa1 = (Pomocna *) adresa;
            Pomocna volatile pomocna = (Pomocna) (*adresa1);

            uint64 *volatile rucka1 = (uint64 *) (&parametar1);
            PCB *volatile rucka = (PCB *) rucka1;




            //__asm__ volatile("ld t0, 0 * 8(a1)");



            rucka = PCB::createThread(pomocna.start, (void *) (parametar3), (void *) (parametar4));

            uint64 a;

            if (rucka) {
                a = 0;
            } else {
                a = -5;
            }

            __asm__ volatile("mv a0,%0"::"r" (a));


        } else if (kod == 0x13) {
            uint64 volatile sepc = r_sepc() + 4;
            uint64 volatile sstatus = r_sstatus();
            PCB::timeSliceCounter = 0;
            PCB::dispatch();
            w_sstatus(sstatus);
            w_sepc(sepc);

        } else if (kod == 0x12) {
            uint64 volatile sepc = r_sepc() + 4;
            uint64 volatile sstatus = r_sstatus();
            PCB::timeSliceCounter = 0;

            __asm__ volatile("mv a0,%0"::"r" (PCB::exit()));

            w_sstatus(sstatus);
            w_sepc(sepc);

        } else if (kod == 0x14) {
            uint64 volatile sepc = r_sepc() + 4;
            uint64 volatile sstatus = r_sstatus();
            //PCB::timeSliceCounter = 0;
            PCB *oldRunning = PCB::running;
            PCB *newRunning = PCB::running = Scheduler::get();


             if (oldRunning != newRunning)
            PCB::contextSwitch(&oldRunning->context, &newRunning->context);
            w_sstatus(sstatus);
            w_sepc(sepc);
        } else if (kod == 0x21) {
            uint64 volatile sepc = r_sepc() + 4;
            w_sepc(sepc);
            //PCB::timeSliceCounter = 0;

            uint64 volatile hh;
            uint64 volatile init;

            __asm__ volatile ("mv %0,a1":"=r" (hh));
            __asm__ volatile ("mv %0,a2":"=r" (init));


            Semaphore *handle1 = Semaphore::createSemaphore(init);
            uint64 volatile aa;
            if ((handle1) != nullptr) {
                aa = -1;
            } else {
                aa = 0;
            }

            Semaphore **handle = (Semaphore **) (hh);
            (*handle) = (Semaphore *) (handle1);

            if (*handle) {
                aa = 0;
            } else {
                aa = -1;
            }


            __asm__ volatile("mv a0,%0"::"r" (aa));


        } else if (kod == 0x23) {
            uint64 volatile sepc = r_sepc() + 4;
            w_sepc(sepc);
            uint64 volatile sstatus = r_sstatus();

            //PCB::timeSliceCounter = 0;

            uint64 volatile hh;


            __asm__ volatile ("mv %0,a1":"=r" (hh));


            Semaphore *id = (Semaphore *) (hh);


            Semaphore::wait(id);


            w_sstatus(sstatus);

        } else if (kod == 0x24) {

            uint64 volatile sepc = r_sepc() + 4;
            w_sepc(sepc);
            uint64 volatile sstatus = r_sstatus();
            //PCB::timeSliceCounter = 0;

            uint64 volatile hh;


            __asm__ volatile ("mv %0,a1":"=r" (hh));


            Semaphore *id = (Semaphore *) (hh);


            Semaphore::signal(id);

            w_sstatus(sstatus);

        } else if (kod == 0x22) {
            uint64 volatile sepc = r_sepc() + 4;
            w_sepc(sepc);
            uint64 volatile sstatus = r_sstatus();

            uint64 volatile hh;


            __asm__ volatile ("mv %0,a1":"=r" (hh));


            Semaphore *id = (Semaphore *) (hh);


            Semaphore::close(id);


            w_sstatus(sstatus);

        } else if (kod == 0x41) {

            uint64 volatile sstatus = r_sstatus();
            uint64 volatile sepc = r_sepc();


            Riscv::w_stvec(prekidna);
            char pom=__getc();
            // __asm__ volatile("mv a0,%0" :: "r" (a));
            Riscv::w_stvec((uint64) &Riscv::supervisorTrap);






            w_sstatus(sstatus);

            __asm__ volatile("mv a0,%0"::"r" (pom));


            sepc = sepc + 4;
            w_sepc(sepc);

        }else if(kod==0x42){

            uint64 volatile sepc = r_sepc();
            uint64 volatile sstatus=r_sstatus();

            uint64 volatile karakter;
            __asm__ volatile ("mv %0,a1":"=r" (karakter));
            __putc(karakter);

            w_sstatus(sstatus);
            sepc = sepc + 4;
            w_sepc(sepc);

        }




    }
}

