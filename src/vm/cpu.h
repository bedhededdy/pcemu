#ifndef _VM_CPU_H
#define _VM_CPU_H

#include <stdint.h>

#include "types.h"

const int VM_CPU_N_REGS = 16;

struct cpu {
    bus_t *bus;

    uint32_t pc;
    uint32_t sp;
    uint32_t bp;
    uint32_t cond; // Carry, Overflow, Negative, Zero
    uint32_t ctrl;

    uint64_t ir;  // Holds entire 64-bit instruction

    uint32_t r[VM_CPU_N_REGS];
};

void cpu_ctor(cpu_t *cpu, bus_t *bus);
void cpu_dtor(cpu_t *cpu);

void cpu_clock(cpu_t *cpu);

#endif
