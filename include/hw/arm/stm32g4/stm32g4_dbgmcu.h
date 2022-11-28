/* stm32g4_dbgmcu.h */
#ifndef INCLUDE_STM32G4_DBGMCU_H
#define INCLUDE_STM32G4_DBGMCU_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_DBGMCU "stm32g4_dbgmcu"
#define STM32G4_DBGMCU(obj) OBJECT_CHECK(STM32G4DBGMCUState, (obj), \
    TYPE_STM32G4_DBGMCU)

typedef struct STM32G4DBGMCUState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t idcode;
    uint32_t cr;
    uint32_t apb1l_fz;
    uint32_t apb1h_fz;
    uint32_t apb2_fz;
} STM32G4DBGMCUState;

#endif /* INCLUDE_STM32G4_DBGMCU_H */
