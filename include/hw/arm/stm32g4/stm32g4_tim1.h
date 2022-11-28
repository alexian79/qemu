/* stm32g4_tim1.h */
#ifndef INCLUDE_STM32G4_TIM1_H
#define INCLUDE_STM32G4_TIM1_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_TIM1 "stm32g4_tim1"
#define STM32G4_TIM1(obj) OBJECT_CHECK(STM32G4TIM1State, (obj), \
    TYPE_STM32G4_TIM1)

typedef struct STM32G4TIM1State {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cr1;
    uint32_t cr2;
    uint32_t smcr;
    uint32_t dier;
    uint32_t sr;
    uint32_t egr;
    uint32_t ccmr1_output;
    uint32_t ccmr1_input;
    uint32_t ccmr2_output;
    uint32_t ccmr2_input;
    uint32_t ccer;
    uint32_t cnt;
    uint32_t psc;
    uint32_t arr;
    uint32_t rcr;
    uint32_t ccr1;
    uint32_t ccr2;
    uint32_t ccr3;
    uint32_t ccr4;
    uint32_t bdtr;
    uint32_t ccr5;
    uint32_t ccr6;
    uint32_t ccmr3_output;
    uint32_t dtr2;
    uint32_t ecr;
    uint32_t tisel;
    uint32_t af1;
    uint32_t af2;
    uint32_t dcr;
    uint32_t dmar;
} STM32G4TIM1State;

#endif /* INCLUDE_STM32G4_TIM1_H */
