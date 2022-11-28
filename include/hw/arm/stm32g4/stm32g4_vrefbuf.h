/* stm32g4_vrefbuf.h */
#ifndef INCLUDE_STM32G4_VREFBUF_H
#define INCLUDE_STM32G4_VREFBUF_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_VREFBUF "stm32g4_vrefbuf"
#define STM32G4_VREFBUF(obj) OBJECT_CHECK(STM32G4VREFBUFState, (obj), \
    TYPE_STM32G4_VREFBUF)

typedef struct STM32G4VREFBUFState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t vrefbuf_csr;
    uint32_t vrefbuf_ccr;
} STM32G4VREFBUFState;

#endif /* INCLUDE_STM32G4_VREFBUF_H */
