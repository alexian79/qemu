/* stm32g4_fdcan.h */
#ifndef INCLUDE_STM32G4_FDCAN_H
#define INCLUDE_STM32G4_FDCAN_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_FDCAN "stm32g4_fdcan"
#define STM32G4_FDCAN(obj) OBJECT_CHECK(STM32G4FDCANState, (obj), \
    TYPE_STM32G4_FDCAN)

typedef struct STM32G4FDCANState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t crel;
    uint32_t endn;
    uint32_t dbtp;
    uint32_t test;
    uint32_t rwd;
    uint32_t cccr;
    uint32_t nbtp;
    uint32_t tscc;
    uint32_t tscv;
    uint32_t tocc;
    uint32_t tocv;
    uint32_t ecr;
    uint32_t psr;
    uint32_t tdcr;
    uint32_t ir;
    uint32_t ie;
    uint32_t ils;
    uint32_t ile;
    uint32_t rxgfc;
    uint32_t xidam;
    uint32_t hpms;
    uint32_t rxf0s;
    uint32_t rxf0a;
    uint32_t rxf1s;
    uint32_t rxf1a;
    uint32_t txbc;
    uint32_t txfqs;
    uint32_t txbrp;
    uint32_t txbar;
    uint32_t txbcr;
    uint32_t txbto;
    uint32_t txbcf;
    uint32_t txbtie;
    uint32_t txbcie;
    uint32_t txefs;
    uint32_t txefa;
    uint32_t ckdiv;
} STM32G4FDCANState;

#endif /* INCLUDE_STM32G4_FDCAN_H */
