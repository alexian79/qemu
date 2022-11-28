/* stm32g4_cordic.h */
#ifndef INCLUDE_STM32G4_CORDIC_H
#define INCLUDE_STM32G4_CORDIC_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_CORDIC "stm32g4_cordic"
#define STM32G4_CORDIC(obj) OBJECT_CHECK(STM32G4CORDICState, (obj), \
    TYPE_STM32G4_CORDIC)

typedef struct STM32G4CORDICState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t csr;
    uint32_t wdata;
    uint32_t rdata;
} STM32G4CORDICState;

#endif /* INCLUDE_STM32G4_CORDIC_H */
