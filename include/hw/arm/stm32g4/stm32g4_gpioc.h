/* stm32g4_gpioc.h */
#ifndef INCLUDE_STM32G4_GPIOC_H
#define INCLUDE_STM32G4_GPIOC_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_GPIOC "stm32g4_gpioc"
#define STM32G4_GPIOC(obj) OBJECT_CHECK(STM32G4GPIOCState, (obj), \
    TYPE_STM32G4_GPIOC)

typedef struct STM32G4GPIOCState {
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
} STM32G4GPIOCState;

#endif /* INCLUDE_STM32G4_GPIOC_H */
