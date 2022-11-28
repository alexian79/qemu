/* stm32g4_rng.h */
#ifndef INCLUDE_STM32G4_RNG_H
#define INCLUDE_STM32G4_RNG_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_RNG "stm32g4_rng"
#define STM32G4_RNG(obj) OBJECT_CHECK(STM32G4RNGState, (obj), TYPE_STM32G4_RNG)

typedef struct STM32G4RNGState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cr;
    uint32_t sr;
    uint32_t dr;
} STM32G4RNGState;

#endif /* INCLUDE_STM32G4_RNG_H */
