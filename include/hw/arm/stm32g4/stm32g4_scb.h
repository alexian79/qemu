/* stm32g4_scb.h */
#ifndef INCLUDE_STM32G4_SCB_H
#define INCLUDE_STM32G4_SCB_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_SCB "stm32g4_scb"
#define STM32G4_SCB(obj) OBJECT_CHECK(STM32G4SCBState, (obj), TYPE_STM32G4_SCB)

typedef struct STM32G4SCBState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cpuid;
    uint32_t icsr;
    uint32_t vtor;
    uint32_t aircr;
    uint32_t scr;
    uint32_t ccr;
    uint32_t shpr1;
    uint32_t shpr2;
    uint32_t shpr3;
    uint32_t shcsr;
    uint32_t cfsr_ufsr_bfsr_mmfsr;
    uint32_t hfsr;
    uint32_t mmfar;
    uint32_t bfar;
    uint32_t afsr;
} STM32G4SCBState;

#endif /* INCLUDE_STM32G4_SCB_H */
