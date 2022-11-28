/* stm32g4_gpiob.h */
#ifndef INCLUDE_STM32G4_GPIOB_H
#define INCLUDE_STM32G4_GPIOB_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_GPIOB "stm32g4_gpiob"
#define STM32G4_GPIOB(obj) OBJECT_CHECK(STM32G4GPIOBState, (obj), \
    TYPE_STM32G4_GPIOB)

typedef struct STM32G4GPIOBState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t moder;
    uint32_t otyper;
    uint32_t ospeedr;
    uint32_t pupdr;
    uint32_t idr;
    uint32_t odr;
    uint32_t bsrr;
    uint32_t lckr;
    uint32_t afrl;
    uint32_t afrh;
    uint32_t brr;
} STM32G4GPIOBState;

#endif /* INCLUDE_STM32G4_GPIOB_H */
