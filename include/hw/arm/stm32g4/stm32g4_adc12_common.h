/* stm32g4_adc12_common.h */
#ifndef INCLUDE_STM32G4_ADC12_COMMON_H
#define INCLUDE_STM32G4_ADC12_COMMON_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_ADC12_COMMON "stm32g4_adc12_common"
#define STM32G4_ADC12_COMMON(obj) OBJECT_CHECK(STM32G4ADC12CommonState, (obj), \
    TYPE_STM32G4_ADC12_COMMON)

typedef struct STM32G4ADC12CommonState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t csr;
    uint32_t ccr;
    uint32_t cdr;
} STM32G4ADC12CommonState;

#endif /* INCLUDE_STM32G4_ADC12_COMMON_H */
