/* stm32g4_tim6.h */
#ifndef INCLUDE_STM32G4_TIM6_H
#define INCLUDE_STM32G4_TIM6_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_TIM6 "stm32g4_tim6"
#define STM32G4_TIM6(obj) OBJECT_CHECK(STM32G4TIM6State, (obj), \
    TYPE_STM32G4_TIM6)

typedef struct STM32G4TIM6State {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cr1;
    uint32_t cr2;
    uint32_t dier;
    uint32_t sr;
    uint32_t egr;
    uint32_t cnt;
    uint32_t psc;
    uint32_t arr;
} STM32G4TIM6State;

#endif /* INCLUDE_STM32G4_TIM6_H */
