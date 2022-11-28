/* stm32g4_sai.h */
#ifndef INCLUDE_STM32G4_SAI_H
#define INCLUDE_STM32G4_SAI_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_SAI "stm32g4_sai"
#define STM32G4_SAI(obj) OBJECT_CHECK(STM32G4SAIState, (obj), TYPE_STM32G4_SAI)

typedef struct STM32G4SAIState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t acr1;
    uint32_t acr2;
    uint32_t afrcr;
    uint32_t aslotr;
    uint32_t aim;
    uint32_t asr;
    uint32_t aclrfr;
    uint32_t adr;
    uint32_t bcr1;
    uint32_t bcr2;
    uint32_t bfrcr;
    uint32_t bslotr;
    uint32_t bim;
    uint32_t bsr;
    uint32_t bclrfr;
    uint32_t bdr;
    uint32_t pdmcr;
    uint32_t pdmdly;
} STM32G4SAIState;

#endif /* INCLUDE_STM32G4_SAI_H */
