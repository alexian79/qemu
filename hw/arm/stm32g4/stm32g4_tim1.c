/* stm32g4_tim1.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_tim1.h"
#include "migration/vmstate.h"

#define STM32G4_TIM1_MMIO TYPE_STM32G4_TIM1 "_mmio"
#define STM32G4_TIM1_MMIO_SIZE 0x3EC

static uint64_t stm32g4_tim1_mmio_read(void *opaque, hwaddr offset,
                                       unsigned size)
{
    STM32G4TIM1State *s = STM32G4_TIM1(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x000 ... 0x003:
        /* CR1, control register 1 */
        ret = s->cr1;
        break;

    case 0x004 ... 0x007:
        /* CR2, control register 2 */
        ret = s->cr2;
        break;

    case 0x008 ... 0x00B:
        /* SMCR, slave mode control register */
        ret = s->smcr;
        break;

    case 0x00C ... 0x00F:
        /* DIER, DMA/Interrupt enable register */
        ret = s->dier;
        break;

    case 0x010 ... 0x013:
        /* SR, status register */
        ret = s->sr;
        break;

    case 0x014 ... 0x017:
        /* EGR, event generation register */
        ret = s->egr;
        break;

    case 0x018 ... 0x01B:
        /* CCMR1_Output, capture/compare mode register 1 (output mode) */
        ret = s->ccmr1_output;
        break;

    case 0x01C ... 0x01F:
        /* CCMR1_Input, capture/compare mode register 1 (input mode) */
        ret = s->ccmr1_input;
        break;

    case 0x020 ... 0x023:
        /* CCMR2_Output, capture/compare mode register 2 (output mode) */
        ret = s->ccmr2_output;
        break;

    case 0x024 ... 0x027:
        /* CCMR2_Input, capture/compare mode register 2 (input mode) */
        ret = s->ccmr2_input;
        break;

    case 0x028 ... 0x02B:
        /* CCER, capture/compare enable register */
        ret = s->ccer;
        break;

    case 0x02C ... 0x02F:
        /* CNT, counter */
        ret = s->cnt;
        break;

    case 0x030 ... 0x033:
        /* PSC, prescaler */
        ret = s->psc;
        break;

    case 0x034 ... 0x037:
        /* ARR, auto-reload register */
        ret = s->arr;
        break;

    case 0x038 ... 0x03B:
        /* RCR, repetition counter register */
        ret = s->rcr;
        break;

    case 0x03C ... 0x03F:
        /* CCR1, capture/compare register 1 */
        ret = s->ccr1;
        break;

    case 0x040 ... 0x043:
        /* CCR2, capture/compare register 2 */
        ret = s->ccr2;
        break;

    case 0x044 ... 0x047:
        /* CCR3, capture/compare register 3 */
        ret = s->ccr3;
        break;

    case 0x048 ... 0x04B:
        /* CCR4, capture/compare register 4 */
        ret = s->ccr4;
        break;

    case 0x04C ... 0x04F:
        /* BDTR, break and dead-time register */
        ret = s->bdtr;
        break;

    case 0x050 ... 0x053:
        /* CCR5, capture/compare register 4 */
        ret = s->ccr5;
        break;

    case 0x054 ... 0x057:
        /* CCR6, capture/compare register 4 */
        ret = s->ccr6;
        break;

    case 0x058 ... 0x05B:
        /* CCMR3_Output, capture/compare mode register 2 (output mode) */
        ret = s->ccmr3_output;
        break;

    case 0x05C ... 0x05F:
        /* DTR2, timer Deadtime Register 2 */
        ret = s->dtr2;
        break;

    case 0x060 ... 0x063:
        /* ECR, DMA control register */
        ret = s->ecr;
        break;

    case 0x064 ... 0x067:
        /* TISEL, TIM timer input selection register */
        ret = s->tisel;
        break;

    case 0x068 ... 0x06B:
        /* AF1, TIM alternate function option register 1 */
        ret = s->af1;
        break;

    case 0x06C ... 0x06F:
        /* AF2, TIM alternate function option register 2 */
        ret = s->af2;
        break;

    case 0x3E4 ... 0x3E7:
        /* DCR, control register */
        ret = s->dcr;
        break;

    case 0x3E8 ... 0x3EB:
        /* DMAR, DMA address for full transfer */
        ret = s->dmar;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_tim1_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                    unsigned size)
{
    STM32G4TIM1State *s = STM32G4_TIM1(opaque);

    switch (offset) {
    case 0x000 ... 0x003:
        /* CR1, control register 1 */
        s->cr1 = value;
        break;

    case 0x004 ... 0x007:
        /* CR2, control register 2 */
        s->cr2 = value;
        break;

    case 0x008 ... 0x00B:
        /* SMCR, slave mode control register */
        s->smcr = value;
        break;

    case 0x00C ... 0x00F:
        /* DIER, DMA/Interrupt enable register */
        s->dier = value;
        break;

    case 0x010 ... 0x013:
        /* SR, status register */
        s->sr = value;
        break;

    case 0x014 ... 0x017:
        /* EGR, event generation register */
        s->egr = value;
        break;

    case 0x018 ... 0x01B:
        /* CCMR1_Output, capture/compare mode register 1 (output mode) */
        s->ccmr1_output = value;
        break;

    case 0x01C ... 0x01F:
        /* CCMR1_Input, capture/compare mode register 1 (input mode) */
        s->ccmr1_input = value;
        break;

    case 0x020 ... 0x023:
        /* CCMR2_Output, capture/compare mode register 2 (output mode) */
        s->ccmr2_output = value;
        break;

    case 0x024 ... 0x027:
        /* CCMR2_Input, capture/compare mode register 2 (input mode) */
        s->ccmr2_input = value;
        break;

    case 0x028 ... 0x02B:
        /* CCER, capture/compare enable register */
        s->ccer = value;
        break;

    case 0x02C ... 0x02F:
        /* CNT, counter */
        s->cnt = value;
        break;

    case 0x030 ... 0x033:
        /* PSC, prescaler */
        s->psc = value;
        break;

    case 0x034 ... 0x037:
        /* ARR, auto-reload register */
        s->arr = value;
        break;

    case 0x038 ... 0x03B:
        /* RCR, repetition counter register */
        s->rcr = value;
        break;

    case 0x03C ... 0x03F:
        /* CCR1, capture/compare register 1 */
        s->ccr1 = value;
        break;

    case 0x040 ... 0x043:
        /* CCR2, capture/compare register 2 */
        s->ccr2 = value;
        break;

    case 0x044 ... 0x047:
        /* CCR3, capture/compare register 3 */
        s->ccr3 = value;
        break;

    case 0x048 ... 0x04B:
        /* CCR4, capture/compare register 4 */
        s->ccr4 = value;
        break;

    case 0x04C ... 0x04F:
        /* BDTR, break and dead-time register */
        s->bdtr = value;
        break;

    case 0x050 ... 0x053:
        /* CCR5, capture/compare register 4 */
        s->ccr5 = value;
        break;

    case 0x054 ... 0x057:
        /* CCR6, capture/compare register 4 */
        s->ccr6 = value;
        break;

    case 0x058 ... 0x05B:
        /* CCMR3_Output, capture/compare mode register 2 (output mode) */
        s->ccmr3_output = value;
        break;

    case 0x05C ... 0x05F:
        /* DTR2, timer Deadtime Register 2 */
        s->dtr2 = value;
        break;

    case 0x060 ... 0x063:
        /* ECR, DMA control register */
        s->ecr = value;
        break;

    case 0x064 ... 0x067:
        /* TISEL, TIM timer input selection register */
        s->tisel = value;
        break;

    case 0x068 ... 0x06B:
        /* AF1, TIM alternate function option register 1 */
        s->af1 = value;
        break;

    case 0x06C ... 0x06F:
        /* AF2, TIM alternate function option register 2 */
        s->af2 = value;
        break;

    case 0x3E4 ... 0x3E7:
        /* DCR, control register */
        s->dcr = value;
        break;

    case 0x3E8 ... 0x3EB:
        /* DMAR, DMA address for full transfer */
        s->dmar = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_tim1_mmio_ops = {
    .read = stm32g4_tim1_mmio_read,
    .write = stm32g4_tim1_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_tim1_instance_init(Object *obj)
{
    STM32G4TIM1State *s = STM32G4_TIM1(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_tim1_mmio_ops, s,
                          STM32G4_TIM1_MMIO, STM32G4_TIM1_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_tim1_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4TIM1State *s = STM32G4_TIM1(dev);
}

static void stm32g4_tim1_reset(DeviceState *dev)
{
    STM32G4TIM1State *s = STM32G4_TIM1(dev);

    s->cr1 = 0x00000000;
    s->cr2 = 0x00000000;
    s->smcr = 0x00000000;
    s->dier = 0x00000000;
    s->sr = 0x00000000;
    s->egr = 0x00000000;
    s->ccmr1_output = 0x00000000;
    s->ccmr1_input = 0x00000000;
    s->ccmr2_output = 0x00000000;
    s->ccmr2_input = 0x00000000;
    s->ccer = 0x00000000;
    s->cnt = 0x00000000;
    s->psc = 0x00000000;
    s->arr = 0x0000FFFF;
    s->rcr = 0x00000000;
    s->ccr1 = 0x00000000;
    s->ccr2 = 0x00000000;
    s->ccr3 = 0x00000000;
    s->ccr4 = 0x00000000;
    s->bdtr = 0x00000000;
    s->ccr5 = 0x00000000;
    s->ccr6 = 0x00000000;
    s->ccmr3_output = 0x00000000;
    s->dtr2 = 0x00000000;
    s->ecr = 0x00000000;
    s->tisel = 0x00000000;
    s->af1 = 0x00000000;
    s->af2 = 0x00000000;
    s->dcr = 0x00000000;
    s->dmar = 0x00000000;
}

static void stm32g4_tim1_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4TIM1State *s = STM32G4_TIM1(dev);
}

static Property stm32g4_tim1_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_tim1 = {
    .name = "stm32g4_tim1",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cr1, STM32G4TIM1State),
        VMSTATE_UINT32(cr2, STM32G4TIM1State),
        VMSTATE_UINT32(smcr, STM32G4TIM1State),
        VMSTATE_UINT32(dier, STM32G4TIM1State),
        VMSTATE_UINT32(sr, STM32G4TIM1State),
        VMSTATE_UINT32(egr, STM32G4TIM1State),
        VMSTATE_UINT32(ccmr1_output, STM32G4TIM1State),
        VMSTATE_UINT32(ccmr1_input, STM32G4TIM1State),
        VMSTATE_UINT32(ccmr2_output, STM32G4TIM1State),
        VMSTATE_UINT32(ccmr2_input, STM32G4TIM1State),
        VMSTATE_UINT32(ccer, STM32G4TIM1State),
        VMSTATE_UINT32(cnt, STM32G4TIM1State),
        VMSTATE_UINT32(psc, STM32G4TIM1State),
        VMSTATE_UINT32(arr, STM32G4TIM1State),
        VMSTATE_UINT32(rcr, STM32G4TIM1State),
        VMSTATE_UINT32(ccr1, STM32G4TIM1State),
        VMSTATE_UINT32(ccr2, STM32G4TIM1State),
        VMSTATE_UINT32(ccr3, STM32G4TIM1State),
        VMSTATE_UINT32(ccr4, STM32G4TIM1State),
        VMSTATE_UINT32(bdtr, STM32G4TIM1State),
        VMSTATE_UINT32(ccr5, STM32G4TIM1State),
        VMSTATE_UINT32(ccr6, STM32G4TIM1State),
        VMSTATE_UINT32(ccmr3_output, STM32G4TIM1State),
        VMSTATE_UINT32(dtr2, STM32G4TIM1State),
        VMSTATE_UINT32(ecr, STM32G4TIM1State),
        VMSTATE_UINT32(tisel, STM32G4TIM1State),
        VMSTATE_UINT32(af1, STM32G4TIM1State),
        VMSTATE_UINT32(af2, STM32G4TIM1State),
        VMSTATE_UINT32(dcr, STM32G4TIM1State),
        VMSTATE_UINT32(dmar, STM32G4TIM1State),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_tim1_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_tim1_realize;
    dc->reset     = stm32g4_tim1_reset;
    dc->unrealize = stm32g4_tim1_unrealize;
    dc->vmsd      = &vmstate_stm32g4_tim1;
    device_class_set_props(dc, stm32g4_tim1_properties);
}

static TypeInfo stm32g4_tim1_info = {
    .name          = TYPE_STM32G4_TIM1,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4TIM1State),
    .instance_init = stm32g4_tim1_instance_init,
    .class_init    = stm32g4_tim1_class_init
};

static void stm32g4_tim1_register_types(void)
{
    type_register_static(&stm32g4_tim1_info);
}

type_init(stm32g4_tim1_register_types)
