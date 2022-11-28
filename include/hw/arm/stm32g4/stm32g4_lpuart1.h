/* stm32g4_lpuart1.h */
#ifndef INCLUDE_STM32G4_LPUART1_H
#define INCLUDE_STM32G4_LPUART1_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_LPUART1 "stm32g4_lpuart1"
#define STM32G4_LPUART1(obj) OBJECT_CHECK(STM32G4LPUART1State, (obj), \
    TYPE_STM32G4_LPUART1)

typedef struct STM32G4LPUART1State {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cr1;
    uint32_t cr2;
    uint32_t cr3;
    uint32_t brr;
    uint32_t rqr;
    uint32_t isr;
    uint32_t icr;
    uint32_t rdr;
    uint32_t tdr;
    uint32_t presc;
} STM32G4LPUART1State;

#endif /* INCLUDE_STM32G4_LPUART1_H */
