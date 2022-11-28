/* stm32g4_dma1.h */
#ifndef INCLUDE_STM32G4_DMA1_H
#define INCLUDE_STM32G4_DMA1_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_DMA1 "stm32g4_dma1"
#define STM32G4_DMA1(obj) OBJECT_CHECK(STM32G4DMA1State, (obj), \
    TYPE_STM32G4_DMA1)

typedef struct STM32G4DMA1State {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t isr;
    uint32_t ifcr;
    uint32_t ccr1;
    uint32_t cndtr1;
    uint32_t cpar1;
    uint32_t cmar1;
    uint32_t ccr2;
    uint32_t cndtr2;
    uint32_t cpar2;
    uint32_t cmar2;
    uint32_t ccr3;
    uint32_t cndtr3;
    uint32_t cpar3;
    uint32_t cmar3;
    uint32_t ccr4;
    uint32_t cndtr4;
    uint32_t cpar4;
    uint32_t cmar4;
    uint32_t ccr5;
    uint32_t cndtr5;
    uint32_t cpar5;
    uint32_t cmar5;
    uint32_t ccr6;
    uint32_t cndtr6;
    uint32_t cpar6;
    uint32_t cmar6;
    uint32_t ccr7;
    uint32_t cndtr7;
    uint32_t cpar7;
    uint32_t cmar7;
    uint32_t ccr8;
    uint32_t cndtr8;
    uint32_t cpar8;
    uint32_t cmar8;
} STM32G4DMA1State;

#endif /* INCLUDE_STM32G4_DMA1_H */
