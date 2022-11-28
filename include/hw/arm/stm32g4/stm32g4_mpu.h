/* stm32g4_mpu.h */
#ifndef INCLUDE_STM32G4_MPU_H
#define INCLUDE_STM32G4_MPU_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_MPU "stm32g4_mpu"
#define STM32G4_MPU(obj) OBJECT_CHECK(STM32G4MPUState, (obj), TYPE_STM32G4_MPU)

typedef struct STM32G4MPUState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t typer;
    uint32_t ctrl;
    uint32_t rnr;
    uint32_t rbar;
    uint32_t rasr;
} STM32G4MPUState;

#endif /* INCLUDE_STM32G4_MPU_H */
