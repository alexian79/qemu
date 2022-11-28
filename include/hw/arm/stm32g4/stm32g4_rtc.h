/* stm32g4_rtc.h */
#ifndef INCLUDE_STM32G4_RTC_H
#define INCLUDE_STM32G4_RTC_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_RTC "stm32g4_rtc"
#define STM32G4_RTC(obj) OBJECT_CHECK(STM32G4RTCState, (obj), TYPE_STM32G4_RTC)

typedef struct STM32G4RTCState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t tr;
    uint32_t dr;
    uint32_t ssr;
    uint32_t icsr;
    uint32_t prer;
    uint32_t wutr;
    uint32_t cr;
    uint32_t wpr;
    uint32_t calr;
    uint32_t shiftr;
    uint32_t tstr;
    uint32_t tsdr;
    uint32_t tsssr;
    uint32_t alrmar;
    uint32_t alrmassr;
    uint32_t alrmbr;
    uint32_t alrmbssr;
    uint32_t sr;
    uint32_t misr;
    uint32_t scr;
} STM32G4RTCState;

#endif /* INCLUDE_STM32G4_RTC_H */
