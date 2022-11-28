/* stm32g4_fpu.h */
#ifndef INCLUDE_STM32G4_FPU_H
#define INCLUDE_STM32G4_FPU_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_FPU "stm32g4_fpu"
#define STM32G4_FPU(obj) OBJECT_CHECK(STM32G4FPUState, (obj), TYPE_STM32G4_FPU)

typedef struct STM32G4FPUState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t fpccr;
    uint32_t fpcar;
    uint32_t fpscr;
} STM32G4FPUState;

#endif /* INCLUDE_STM32G4_FPU_H */
