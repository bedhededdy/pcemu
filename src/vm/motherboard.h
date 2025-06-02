#ifndef _VM_MOTHERBOARD_H
#define _VM_MOTHERBOARD_H

#include "types.h"

struct motherboard {
    cpu_t cpu;
    bus_t bus;
};

void motherboard_ctor(motherboard_t *motherboard)
void motherboard_dtor(motherboard_t *motherboard);
void motherboard_boot(motherboard_t *motherboard);
void motherboard_reboot(motherboard_t *motherboard);

#endif

