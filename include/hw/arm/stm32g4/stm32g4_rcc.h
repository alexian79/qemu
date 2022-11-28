/* stm32g4_rcc.h */
#ifndef INCLUDE_STM32G4_RCC_H
#define INCLUDE_STM32G4_RCC_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_RCC "stm32g4_rcc"
#define STM32G4_RCC(obj) OBJECT_CHECK(STM32G4RCCState, (obj), TYPE_STM32G4_RCC)

typedef struct STM32G4RCCState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cr;
    uint32_t icscr;
    uint32_t cfgr;
    uint32_t pllsyscfgr;
    uint32_t cier;
    uint32_t cifr;
    uint32_t cicr;
    uint32_t ahb1rstr;
    uint32_t ahb2rstr;
    uint32_t ahb3rstr;
    uint32_t apb1rstr1;
    uint32_t apb1rstr2;
    uint32_t apb2rstr;
    uint32_t ahb1enr;
    uint32_t ahb2enr;
    uint32_t ahb3enr;
    uint32_t apb1enr1;
    uint32_t apb1enr2;
    uint32_t apb2enr;
    uint32_t ahb1smenr;
    uint32_t ahb2smenr;
    uint32_t ahb3smenr;
    uint32_t apb1smenr1;
    uint32_t apb1smenr2;
    uint32_t apb2smenr;
    uint32_t ccipr1;
    uint32_t bdcr;
    uint32_t csr;
    uint32_t crrcr;
    uint32_t ccipr2;
} STM32G4RCCState;

#endif /* INCLUDE_STM32G4_RCC_H */
