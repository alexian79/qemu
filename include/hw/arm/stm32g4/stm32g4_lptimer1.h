/* stm32g4_lptimer1.h */
#ifndef INCLUDE_STM32G4_LPTIMER1_H
#define INCLUDE_STM32G4_LPTIMER1_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_LPTIMER1 "stm32g4_lptimer1"
#define STM32G4_LPTIMER1(obj) OBJECT_CHECK(STM32G4LPTIMER1State, (obj), \
    TYPE_STM32G4_LPTIMER1)

typedef struct STM32G4LPTIMER1State {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t isr;
    uint32_t icr;
    uint32_t ier;
    uint32_t cfgr;
    uint32_t cr;
    uint32_t cmp;
    uint32_t arr;
    uint32_t cnt;
    uint32_t or;
} STM32G4LPTIMER1State;

#endif /* INCLUDE_STM32G4_LPTIMER1_H */
