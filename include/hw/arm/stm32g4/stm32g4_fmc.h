/* stm32g4_fmc.h */
#ifndef INCLUDE_STM32G4_FMC_H
#define INCLUDE_STM32G4_FMC_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_FMC "stm32g4_fmc"
#define STM32G4_FMC(obj) OBJECT_CHECK(STM32G4FMCState, (obj), TYPE_STM32G4_FMC)

typedef struct STM32G4FMCState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t bcr1;
    uint32_t btr1;
    uint32_t bcr2;
    uint32_t btr2;
    uint32_t bcr3;
    uint32_t btr3;
    uint32_t bcr4;
    uint32_t btr4;
    uint32_t pcscntr;
    uint32_t pcr;
    uint32_t sr;
    uint32_t pmem;
    uint32_t patt;
    uint32_t eccr;
    uint32_t bwtr1;
    uint32_t bwtr2;
    uint32_t bwtr3;
    uint32_t bwtr4;
} STM32G4FMCState;

#endif /* INCLUDE_STM32G4_FMC_H */
