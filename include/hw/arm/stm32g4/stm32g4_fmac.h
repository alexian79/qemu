/* stm32g4_fmac.h */
#ifndef INCLUDE_STM32G4_FMAC_H
#define INCLUDE_STM32G4_FMAC_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_FMAC "stm32g4_fmac"
#define STM32G4_FMAC(obj) OBJECT_CHECK(STM32G4FMACState, (obj), \
    TYPE_STM32G4_FMAC)

typedef struct STM32G4FMACState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t x1bufcfg;
    uint32_t x2bufcfg;
    uint32_t ybufcfg;
    uint32_t param;
    uint32_t cr;
    uint32_t sr;
    uint32_t wdata;
    uint32_t rdata;
} STM32G4FMACState;

#endif /* INCLUDE_STM32G4_FMAC_H */
