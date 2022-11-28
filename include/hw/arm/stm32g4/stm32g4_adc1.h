/* stm32g4_adc1.h */
#ifndef INCLUDE_STM32G4_ADC1_H
#define INCLUDE_STM32G4_ADC1_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_ADC1 "stm32g4_adc1"
#define STM32G4_ADC1(obj) OBJECT_CHECK(STM32G4ADC1State, (obj), \
    TYPE_STM32G4_ADC1)

typedef struct STM32G4ADC1State {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t isr;
    uint32_t ier;
    uint32_t cr;
    uint32_t cfgr;
    uint32_t cfgr2;
    uint32_t smpr1;
    uint32_t smpr2;
    uint32_t tr1;
    uint32_t tr2;
    uint32_t tr3;
    uint32_t sqr1;
    uint32_t sqr2;
    uint32_t sqr3;
    uint32_t sqr4;
    uint32_t dr;
    uint32_t jsqr;
    uint32_t ofr1;
    uint32_t ofr2;
    uint32_t ofr3;
    uint32_t ofr4;
    uint32_t jdr1;
    uint32_t jdr2;
    uint32_t jdr3;
    uint32_t jdr4;
    uint32_t awd2cr;
    uint32_t awd3cr;
    uint32_t difsel;
    uint32_t calfact;
    uint32_t gcomp;
} STM32G4ADC1State;

#endif /* INCLUDE_STM32G4_ADC1_H */
