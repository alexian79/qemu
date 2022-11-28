/* stm32g4_crc.h */
#ifndef INCLUDE_STM32G4_CRC_H
#define INCLUDE_STM32G4_CRC_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_CRC "stm32g4_crc"
#define STM32G4_CRC(obj) OBJECT_CHECK(STM32G4CRCState, (obj), TYPE_STM32G4_CRC)

typedef struct STM32G4CRCState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t dr;
    uint32_t idr;
    uint32_t cr;
    uint32_t init;
    uint32_t pol;
} STM32G4CRCState;

#endif /* INCLUDE_STM32G4_CRC_H */
