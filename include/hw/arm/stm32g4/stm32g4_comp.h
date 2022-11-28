/* stm32g4_comp.h */
#ifndef INCLUDE_STM32G4_COMP_H
#define INCLUDE_STM32G4_COMP_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_COMP "stm32g4_comp"
#define STM32G4_COMP(obj) OBJECT_CHECK(STM32G4COMPState, (obj), \
    TYPE_STM32G4_COMP)

typedef struct STM32G4COMPState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t comp_c1csr;
    uint32_t comp_c2csr;
    uint32_t comp_c3csr;
    uint32_t comp_c4csr;
    uint32_t comp_c5csr;
    uint32_t comp_c6csr;
    uint32_t comp_c7csr;
} STM32G4COMPState;

#endif /* INCLUDE_STM32G4_COMP_H */
