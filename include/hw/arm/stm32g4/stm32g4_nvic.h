/* stm32g4_nvic.h */
#ifndef INCLUDE_STM32G4_NVIC_H
#define INCLUDE_STM32G4_NVIC_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_NVIC "stm32g4_nvic"
#define STM32G4_NVIC(obj) OBJECT_CHECK(STM32G4NVICState, (obj), \
    TYPE_STM32G4_NVIC)

typedef struct STM32G4NVICState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t iser0;
    uint32_t iser1;
    uint32_t iser2;
    uint32_t iser3;
    uint32_t icer0;
    uint32_t icer1;
    uint32_t icer2;
    uint32_t icer3;
    uint32_t ispr0;
    uint32_t ispr1;
    uint32_t ispr2;
    uint32_t ispr3;
    uint32_t icpr0;
    uint32_t icpr1;
    uint32_t icpr2;
    uint32_t icpr3;
    uint32_t iabr0;
    uint32_t iabr1;
    uint32_t iabr2;
    uint32_t iabr3;
    uint32_t ipr0;
    uint32_t ipr1;
    uint32_t ipr2;
    uint32_t ipr3;
    uint32_t ipr4;
    uint32_t ipr5;
    uint32_t ipr6;
    uint32_t ipr7;
    uint32_t ipr8;
    uint32_t ipr9;
    uint32_t ipr10;
    uint32_t ipr11;
    uint32_t ipr12;
    uint32_t ipr13;
    uint32_t ipr14;
    uint32_t ipr15;
    uint32_t ipr16;
    uint32_t ipr17;
    uint32_t ipr18;
    uint32_t ipr19;
    uint32_t ipr20;
    uint32_t ipr21;
    uint32_t ipr22;
    uint32_t ipr23;
    uint32_t ipr24;
    uint32_t ipr25;
} STM32G4NVICState;

#endif /* INCLUDE_STM32G4_NVIC_H */
