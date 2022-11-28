/* stm32g4_wwdg.h */
#ifndef INCLUDE_STM32G4_WWDG_H
#define INCLUDE_STM32G4_WWDG_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_WWDG "stm32g4_wwdg"
#define STM32G4_WWDG(obj) OBJECT_CHECK(STM32G4WWDGState, (obj), \
    TYPE_STM32G4_WWDG)

typedef struct STM32G4WWDGState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t cr;
    uint32_t cfr;
    uint32_t sr;
} STM32G4WWDGState;

#endif /* INCLUDE_STM32G4_WWDG_H */
