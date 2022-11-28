/* stm32g4_iwdg.h */
#ifndef INCLUDE_STM32G4_IWDG_H
#define INCLUDE_STM32G4_IWDG_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_IWDG "stm32g4_iwdg"
#define STM32G4_IWDG(obj) OBJECT_CHECK(STM32G4IWDGState, (obj), \
    TYPE_STM32G4_IWDG)

typedef struct STM32G4IWDGState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t kr;
    uint32_t pr;
    uint32_t rlr;
    uint32_t sr;
    uint32_t winr;
} STM32G4IWDGState;

#endif /* INCLUDE_STM32G4_IWDG_H */
