/* stm32g4_i2c1.h */
#ifndef INCLUDE_STM32G4_I2C1_H
#define INCLUDE_STM32G4_I2C1_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_I2C1 "stm32g4_i2c1"
#define STM32G4_I2C1(obj) OBJECT_CHECK(STM32G4I2C1State, (obj), \
    TYPE_STM32G4_I2C1)

typedef struct STM32G4I2C1State {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cr1;
    uint32_t cr2;
    uint32_t oar1;
    uint32_t oar2;
    uint32_t timingr;
    uint32_t timeoutr;
    uint32_t isr;
    uint32_t icr;
    uint32_t pecr;
    uint32_t rxdr;
    uint32_t txdr;
} STM32G4I2C1State;

#endif /* INCLUDE_STM32G4_I2C1_H */
