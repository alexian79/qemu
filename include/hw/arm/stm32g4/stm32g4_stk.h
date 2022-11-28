/* stm32g4_stk.h */
#ifndef INCLUDE_STM32G4_STK_H
#define INCLUDE_STM32G4_STK_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_STK "stm32g4_stk"
#define STM32G4_STK(obj) OBJECT_CHECK(STM32G4STKState, (obj), TYPE_STM32G4_STK)

typedef struct STM32G4STKState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t ctrl;
    uint32_t load;
    uint32_t val;
    uint32_t calib;
} STM32G4STKState;

#endif /* INCLUDE_STM32G4_STK_H */
