/* stm32g4_flash.h */
#ifndef INCLUDE_STM32G4_FLASH_H
#define INCLUDE_STM32G4_FLASH_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_FLASH "stm32g4_flash"
#define STM32G4_FLASH(obj) OBJECT_CHECK(STM32G4FLASHState, (obj), \
    TYPE_STM32G4_FLASH)

typedef struct STM32G4FLASHState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t acr;
    uint32_t pdkeyr;
    uint32_t keyr;
    uint32_t optkeyr;
    uint32_t sr;
    uint32_t cr;
    uint32_t eccr;
    uint32_t optr;
    uint32_t pcrop1sr;
    uint32_t pcrop1er;
    uint32_t wrp1ar;
    uint32_t wrp1br;
    uint32_t pcrop2sr;
    uint32_t pcrop2er;
    uint32_t wrp2ar;
    uint32_t wrp2br;
    uint32_t sec1r;
    uint32_t sec2r;
} STM32G4FLASHState;

#endif /* INCLUDE_STM32G4_FLASH_H */
