/* stm32g4_dac1.h */
#ifndef INCLUDE_STM32G4_DAC1_H
#define INCLUDE_STM32G4_DAC1_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_DAC1 "stm32g4_dac1"
#define STM32G4_DAC1(obj) OBJECT_CHECK(STM32G4DAC1State, (obj), \
    TYPE_STM32G4_DAC1)

typedef struct STM32G4DAC1State {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t dac_cr;
    uint32_t dac_swtrgr;
    uint32_t dac_dhr12r1;
    uint32_t dac_dhr12l1;
    uint32_t dac_dhr8r1;
    uint32_t dac_dhr12r2;
    uint32_t dac_dhr12l2;
    uint32_t dac_dhr8r2;
    uint32_t dac_dhr12rd;
    uint32_t dac_dhr12ld;
    uint32_t dac_dhr8rd;
    uint32_t dac_dor1;
    uint32_t dac_dor2;
    uint32_t dac_sr;
    uint32_t dac_ccr;
    uint32_t dac_mcr;
    uint32_t dac_shsr1;
    uint32_t dac_shsr2;
    uint32_t dac_shhr;
    uint32_t dac_shrr;
    uint32_t dac_str1;
    uint32_t dac_str2;
    uint32_t dac_stmodr;
} STM32G4DAC1State;

#endif /* INCLUDE_STM32G4_DAC1_H */
