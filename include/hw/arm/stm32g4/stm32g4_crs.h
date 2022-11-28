/* stm32g4_crs.h */
#ifndef INCLUDE_STM32G4_CRS_H
#define INCLUDE_STM32G4_CRS_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_CRS "stm32g4_crs"
#define STM32G4_CRS(obj) OBJECT_CHECK(STM32G4CRSState, (obj), TYPE_STM32G4_CRS)

typedef struct STM32G4CRSState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cr;
    uint32_t cfgr;
    uint32_t isr;
    uint32_t icr;
} STM32G4CRSState;

#endif /* INCLUDE_STM32G4_CRS_H */
