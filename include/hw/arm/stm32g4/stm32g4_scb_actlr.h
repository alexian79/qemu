/* stm32g4_scb_actlr.h */
#ifndef INCLUDE_STM32G4_SCB_ACTLR_H
#define INCLUDE_STM32G4_SCB_ACTLR_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_SCB_ACTLR "stm32g4_scb_actlr"
#define STM32G4_SCB_ACTLR(obj) OBJECT_CHECK(STM32G4SCBACTLRState, (obj), \
    TYPE_STM32G4_SCB_ACTLR)

typedef struct STM32G4SCBACTLRState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t actrl;
} STM32G4SCBACTLRState;

#endif /* INCLUDE_STM32G4_SCB_ACTLR_H */
