/* stm32g4_dmamux.h */
#ifndef INCLUDE_STM32G4_DMAMUX_H
#define INCLUDE_STM32G4_DMAMUX_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_DMAMUX "stm32g4_dmamux"
#define STM32G4_DMAMUX(obj) OBJECT_CHECK(STM32G4DMAMUXState, (obj), \
    TYPE_STM32G4_DMAMUX)

typedef struct STM32G4DMAMUXState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t c0cr;
    uint32_t c1cr;
    uint32_t c2cr;
    uint32_t c3cr;
    uint32_t c4cr;
    uint32_t c5cr;
    uint32_t c6cr;
    uint32_t c7cr;
    uint32_t c8cr;
    uint32_t c9cr;
    uint32_t c10cr;
    uint32_t c11cr;
    uint32_t c12cr;
    uint32_t c13cr;
    uint32_t c14cr;
    uint32_t c15cr;
    uint32_t csr;
    uint32_t cfr;
    uint32_t rg0cr;
    uint32_t rg1cr;
    uint32_t rg2cr;
    uint32_t rg3cr;
    uint32_t rgsr;
    uint32_t rgcfr;
} STM32G4DMAMUXState;

#endif /* INCLUDE_STM32G4_DMAMUX_H */
