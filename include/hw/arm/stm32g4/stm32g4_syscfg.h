/* stm32g4_syscfg.h */
#ifndef INCLUDE_STM32G4_SYSCFG_H
#define INCLUDE_STM32G4_SYSCFG_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_SYSCFG "stm32g4_syscfg"
#define STM32G4_SYSCFG(obj) OBJECT_CHECK(STM32G4SYSCFGState, (obj), \
    TYPE_STM32G4_SYSCFG)

typedef struct STM32G4SYSCFGState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t memrmp;
    uint32_t cfgr1;
    uint32_t exticr1;
    uint32_t exticr2;
    uint32_t exticr3;
    uint32_t exticr4;
    uint32_t scsr;
    uint32_t cfgr2;
    uint32_t swpr;
    uint32_t skr;
} STM32G4SYSCFGState;

#endif /* INCLUDE_STM32G4_SYSCFG_H */
