#ifndef _VM_BUS_H
#define _VM_BUS_H

#include <stdint.h>

#include "types.h"

struct bus {
    uint32_t *ram;
    size_t ram_size;
};

void bus_ctor(bus_t *bus);
void bus_dtor(bus_t *bus);

void bus_reset(bus_t *bus);

uint32_t bus_read(bus_t *bus, uint32_t addr);
void bus_write(bus_t *bus, uint32_t addr, uint32_t val);

#endif
