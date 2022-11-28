/* stm32g4_opamp.h */
#ifndef INCLUDE_STM32G4_OPAMP_H
#define INCLUDE_STM32G4_OPAMP_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_OPAMP "stm32g4_opamp"
#define STM32G4_OPAMP(obj) OBJECT_CHECK(STM32G4OPAMPState, (obj), \
    TYPE_STM32G4_OPAMP)

typedef struct STM32G4OPAMPState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t opamp1_csr;
    uint32_t opamp2_csr;
    uint32_t opamp3_csr;
    uint32_t opamp4_csr;
    uint32_t opamp5_csr;
    uint32_t opamp6_csr;
    uint32_t opamp1_tcmr;
    uint32_t opamp2_tcmr;
    uint32_t opamp3_tcmr;
    uint32_t opamp4_tcmr;
    uint32_t opamp5_tcmr;
    uint32_t opamp6_tcmr;
} STM32G4OPAMPState;

#endif /* INCLUDE_STM32G4_OPAMP_H */
