/* stm32g4_spi1.h */
#ifndef INCLUDE_STM32G4_SPI1_H
#define INCLUDE_STM32G4_SPI1_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_SPI1 "stm32g4_spi1"
#define STM32G4_SPI1(obj) OBJECT_CHECK(STM32G4SPI1State, (obj), \
    TYPE_STM32G4_SPI1)

typedef struct STM32G4SPI1State {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cr1;
    uint32_t cr2;
    uint32_t sr;
    uint32_t dr;
    uint32_t crcpr;
    uint32_t rxcrcr;
    uint32_t txcrcr;
    uint32_t i2scfgr;
    uint32_t i2spr;
} STM32G4SPI1State;

#endif /* INCLUDE_STM32G4_SPI1_H */
