/* stm32g4_tamp.h */
#ifndef INCLUDE_STM32G4_TAMP_H
#define INCLUDE_STM32G4_TAMP_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_TAMP "stm32g4_tamp"
#define STM32G4_TAMP(obj) OBJECT_CHECK(STM32G4TAMPState, (obj), \
    TYPE_STM32G4_TAMP)

typedef struct STM32G4TAMPState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cr1;
    uint32_t cr2;
    uint32_t fltcr;
    uint32_t ier;
    uint32_t sr;
    uint32_t misr;
    uint32_t scr;
    uint32_t bkp0r;
    uint32_t bkp1r;
    uint32_t bkp2r;
    uint32_t bkp3r;
    uint32_t bkp4r;
    uint32_t bkp5r;
    uint32_t bkp6r;
    uint32_t bkp7r;
    uint32_t bkp8r;
    uint32_t bkp9r;
    uint32_t bkp10r;
    uint32_t bkp11r;
    uint32_t bkp12r;
    uint32_t bkp13r;
    uint32_t bkp14r;
    uint32_t bkp15r;
    uint32_t bkp16r;
    uint32_t bkp17r;
    uint32_t bkp18r;
    uint32_t bkp19r;
    uint32_t bkp20r;
    uint32_t bkp21r;
    uint32_t bkp22r;
    uint32_t bkp23r;
    uint32_t bkp24r;
    uint32_t bkp25r;
    uint32_t bkp26r;
    uint32_t bkp27r;
    uint32_t bkp28r;
    uint32_t bkp29r;
    uint32_t bkp30r;
    uint32_t bkp31r;
} STM32G4TAMPState;

#endif /* INCLUDE_STM32G4_TAMP_H */
