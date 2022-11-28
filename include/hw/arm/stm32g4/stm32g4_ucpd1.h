/* stm32g4_ucpd1.h */
#ifndef INCLUDE_STM32G4_UCPD1_H
#define INCLUDE_STM32G4_UCPD1_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_UCPD1 "stm32g4_ucpd1"
#define STM32G4_UCPD1(obj) OBJECT_CHECK(STM32G4UCPD1State, (obj), \
    TYPE_STM32G4_UCPD1)

typedef struct STM32G4UCPD1State {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cfg1;
    uint32_t cfg2;
    uint32_t cr;
    uint32_t imr;
    uint32_t sr;
    uint32_t icr;
    uint32_t tx_ordset;
    uint32_t tx_paysz;
    uint32_t txdr;
    uint32_t rx_ordset;
    uint32_t rx_paysz;
    uint32_t rxdr;
    uint32_t rx_ordext1;
    uint32_t rx_ordext2;
} STM32G4UCPD1State;

#endif /* INCLUDE_STM32G4_UCPD1_H */
