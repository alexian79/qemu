/* stm32g4_exti.h */
#ifndef INCLUDE_STM32G4_EXTI_H
#define INCLUDE_STM32G4_EXTI_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_EXTI "stm32g4_exti"
#define STM32G4_EXTI(obj) OBJECT_CHECK(STM32G4EXTIState, (obj), \
    TYPE_STM32G4_EXTI)

typedef struct STM32G4EXTIState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t imr1;
    uint32_t emr1;
    uint32_t rtsr1;
    uint32_t ftsr1;
    uint32_t swier1;
    uint32_t pr1;
    uint32_t imr2;
    uint32_t emr2;
    uint32_t rtsr2;
    uint32_t ftsr2;
    uint32_t swier2;
    uint32_t pr2;
} STM32G4EXTIState;

#endif /* INCLUDE_STM32G4_EXTI_H */
