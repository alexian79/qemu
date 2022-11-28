/* stm32g4_pwr.h */
#ifndef INCLUDE_STM32G4_PWR_H
#define INCLUDE_STM32G4_PWR_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_PWR "stm32g4_pwr"
#define STM32G4_PWR(obj) OBJECT_CHECK(STM32G4PWRState, (obj), TYPE_STM32G4_PWR)

typedef struct STM32G4PWRState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cr1;
    uint32_t cr2;
    uint32_t cr3;
    uint32_t cr4;
    uint32_t sr1;
    uint32_t sr2;
    uint32_t scr;
    uint32_t pucra;
    uint32_t pdcra;
    uint32_t pucrb;
    uint32_t pdcrb;
    uint32_t pucrc;
    uint32_t pdcrc;
    uint32_t pucrd;
    uint32_t pdcrd;
    uint32_t pucre;
    uint32_t pdcre;
    uint32_t pucrf;
    uint32_t pdcrf;
    uint32_t pucrg;
    uint32_t pdcrg;
    uint32_t cr5;
} STM32G4PWRState;

#endif /* INCLUDE_STM32G4_PWR_H */
