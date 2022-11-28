/* stm32g4_quadspi.h */
#ifndef INCLUDE_STM32G4_QUADSPI_H
#define INCLUDE_STM32G4_QUADSPI_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_QUADSPI "stm32g4_quadspi"
#define STM32G4_QUADSPI(obj) OBJECT_CHECK(STM32G4QUADSPIState, (obj), \
    TYPE_STM32G4_QUADSPI)

typedef struct STM32G4QUADSPIState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cr;
    uint32_t dcr;
    uint32_t sr;
    uint32_t fcr;
    uint32_t dlr;
    uint32_t ccr;
    uint32_t ar;
    uint32_t abr;
    uint32_t dr;
    uint32_t psmkr;
    uint32_t psmar;
    uint32_t pir;
    uint32_t lptr;
} STM32G4QUADSPIState;

#endif /* INCLUDE_STM32G4_QUADSPI_H */
