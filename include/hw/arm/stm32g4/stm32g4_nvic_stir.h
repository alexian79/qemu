/* stm32g4_nvic_stir.h */
#ifndef INCLUDE_STM32G4_NVIC_STIR_H
#define INCLUDE_STM32G4_NVIC_STIR_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_NVIC_STIR "stm32g4_nvic_stir"
#define STM32G4_NVIC_STIR(obj) OBJECT_CHECK(STM32G4NVICSTIRState, (obj), \
    TYPE_STM32G4_NVIC_STIR)

typedef struct STM32G4NVICSTIRState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t stir;
} STM32G4NVICSTIRState;

#endif /* INCLUDE_STM32G4_NVIC_STIR_H */
