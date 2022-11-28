/* stm32g4_fpu_cpacr.h */
#ifndef INCLUDE_STM32G4_FPU_CPACR_H
#define INCLUDE_STM32G4_FPU_CPACR_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_FPU_CPACR "stm32g4_fpu_cpacr"
#define STM32G4_FPU_CPACR(obj) OBJECT_CHECK(STM32G4FPUCPACRState, (obj), \
    TYPE_STM32G4_FPU_CPACR)

typedef struct STM32G4FPUCPACRState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cpacr;
} STM32G4FPUCPACRState;

#endif /* INCLUDE_STM32G4_FPU_CPACR_H */
