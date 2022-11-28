/* stm32g4_tim16.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_tim16.h"
#include "migration/vmstate.h"

#define STM32G4_TIM16_MMIO TYPE_STM32G4_TIM16 "_mmio"
#define STM32G4_TIM16_MMIO_SIZE 0x3E8

static uint64_t stm32g4_tim16_mmio_read(void *opaque, hwaddr offset,
                                        unsigned size)
{
    STM32G4TIM16State *s = STM32G4_TIM16(opaque);
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
        /* CCMR1_Output, capture/compare mode register (output mode) */
        ret = s->ccmr1_output;
        break;

    case 0x01C ... 0x01F:
        /* CCMR1_Input, capture/compare mode register 1 (input mode) */
        ret = s->ccmr1_input;
        break;

    case 0x024 ... 0x027:
        /* CCER, capture/compare enable register */
        ret = s->ccer;
        break;

    case 0x028 ... 0x02B:
        /* CNT, counter */
        ret = s->cnt;
        break;

    case 0x02C ... 0x02F:
        /* PSC, prescaler */
        ret = s->psc;
        break;

    case 0x030 ... 0x033:
        /* ARR, auto-reload register */
        ret = s->arr;
        break;

    case 0x034 ... 0x037:
        /* RCR, repetition counter register */
        ret = s->rcr;
        break;

    case 0x038 ... 0x03B:
        /* CCR1, capture/compare register 1 */
        ret = s->ccr1;
        break;

    case 0x048 ... 0x04B:
        /* BDTR, break and dead-time register */
        ret = s->bdtr;
        break;

    case 0x058 ... 0x05B:
        /* DTR2, timer Deadtime Register 2 */
        ret = s->dtr2;
        break;

    case 0x060 ... 0x063:
        /* TISEL, TIM timer input selection register */
        ret = s->tisel;
        break;

    case 0x064 ... 0x067:
        /* AF1, TIM alternate function option register 1 */
        ret = s->af1;
        break;

    case 0x068 ... 0x06B:
        /* AF2, TIM alternate function option register 2 */
        ret = s->af2;
        break;

    case 0x3E0 ... 0x3E3:
        /* DCR, DMA control register */
        ret = s->dcr;
        break;

    case 0x3E4 ... 0x3E7:
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

static void stm32g4_tim16_mmio_write(void *opaque, hwaddr offset,
                                     uint64_t value, unsigned size)
{
    STM32G4TIM16State *s = STM32G4_TIM16(opaque);

    switch (offset) {
    case 0x000 ... 0x003:
        /* CR1, control register 1 */
        s->cr1 = value;
        break;

    case 0x004 ... 0x007:
        /* CR2, control register 2 */
        s->cr2 = value;
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
        /* CCMR1_Output, capture/compare mode register (output mode) */
        s->ccmr1_output = value;
        break;

    case 0x01C ... 0x01F:
        /* CCMR1_Input, capture/compare mode register 1 (input mode) */
        s->ccmr1_input = value;
        break;

    case 0x024 ... 0x027:
        /* CCER, capture/compare enable register */
        s->ccer = value;
        break;

    case 0x028 ... 0x02B:
        /* CNT, counter */
        s->cnt = value;
        break;

    case 0x02C ... 0x02F:
        /* PSC, prescaler */
        s->psc = value;
        break;

    case 0x030 ... 0x033:
        /* ARR, auto-reload register */
        s->arr = value;
        break;

    case 0x034 ... 0x037:
        /* RCR, repetition counter register */
        s->rcr = value;
        break;

    case 0x038 ... 0x03B:
        /* CCR1, capture/compare register 1 */
        s->ccr1 = value;
        break;

    case 0x048 ... 0x04B:
        /* BDTR, break and dead-time register */
        s->bdtr = value;
        break;

    case 0x058 ... 0x05B:
        /* DTR2, timer Deadtime Register 2 */
        s->dtr2 = value;
        break;

    case 0x060 ... 0x063:
        /* TISEL, TIM timer input selection register */
        s->tisel = value;
        break;

    case 0x064 ... 0x067:
        /* AF1, TIM alternate function option register 1 */
        s->af1 = value;
        break;

    case 0x068 ... 0x06B:
        /* AF2, TIM alternate function option register 2 */
        s->af2 = value;
        break;

    case 0x3E0 ... 0x3E3:
        /* DCR, DMA control register */
        s->dcr = value;
        break;

    case 0x3E4 ... 0x3E7:
        /* DMAR, DMA address for full transfer */
        s->dmar = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_tim16_mmio_ops = {
    .read = stm32g4_tim16_mmio_read,
    .write = stm32g4_tim16_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_tim16_instance_init(Object *obj)
{
    STM32G4TIM16State *s = STM32G4_TIM16(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_tim16_mmio_ops, s,
                          STM32G4_TIM16_MMIO, STM32G4_TIM16_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_tim16_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4TIM16State *s = STM32G4_TIM16(dev);
}

static void stm32g4_tim16_reset(DeviceState *dev)
{
    STM32G4TIM16State *s = STM32G4_TIM16(dev);

    s->cr1 = 0x00000000;
    s->cr2 = 0x00000000;
    s->dier = 0x00000000;
    s->sr = 0x00000000;
    s->egr = 0x00000000;
    s->ccmr1_output = 0x00000000;
    s->ccmr1_input = 0x00000000;
    s->ccer = 0x00000000;
    s->cnt = 0x00000000;
    s->psc = 0x00000000;
    s->arr = 0x0000FFFF;
    s->rcr = 0x00000000;
    s->ccr1 = 0x00000000;
    s->bdtr = 0x00000000;
    s->dtr2 = 0x00000000;
    s->tisel = 0x00000000;
    s->af1 = 0x00000000;
    s->af2 = 0x00000000;
    s->dcr = 0x00000000;
    s->dmar = 0x00000000;
}

static void stm32g4_tim16_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4TIM16State *s = STM32G4_TIM16(dev);
}

static Property stm32g4_tim16_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_tim16 = {
    .name = "stm32g4_tim16",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cr1, STM32G4TIM16State),
        VMSTATE_UINT32(cr2, STM32G4TIM16State),
        VMSTATE_UINT32(dier, STM32G4TIM16State),
        VMSTATE_UINT32(sr, STM32G4TIM16State),
        VMSTATE_UINT32(egr, STM32G4TIM16State),
        VMSTATE_UINT32(ccmr1_output, STM32G4TIM16State),
        VMSTATE_UINT32(ccmr1_input, STM32G4TIM16State),
        VMSTATE_UINT32(ccer, STM32G4TIM16State),
        VMSTATE_UINT32(cnt, STM32G4TIM16State),
        VMSTATE_UINT32(psc, STM32G4TIM16State),
        VMSTATE_UINT32(arr, STM32G4TIM16State),
        VMSTATE_UINT32(rcr, STM32G4TIM16State),
        VMSTATE_UINT32(ccr1, STM32G4TIM16State),
        VMSTATE_UINT32(bdtr, STM32G4TIM16State),
        VMSTATE_UINT32(dtr2, STM32G4TIM16State),
        VMSTATE_UINT32(tisel, STM32G4TIM16State),
        VMSTATE_UINT32(af1, STM32G4TIM16State),
        VMSTATE_UINT32(af2, STM32G4TIM16State),
        VMSTATE_UINT32(dcr, STM32G4TIM16State),
        VMSTATE_UINT32(dmar, STM32G4TIM16State),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_tim16_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_tim16_realize;
    dc->reset     = stm32g4_tim16_reset;
    dc->unrealize = stm32g4_tim16_unrealize;
    dc->vmsd      = &vmstate_stm32g4_tim16;
    device_class_set_props(dc, stm32g4_tim16_properties);
}

static TypeInfo stm32g4_tim16_info = {
    .name          = TYPE_STM32G4_TIM16,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4TIM16State),
    .instance_init = stm32g4_tim16_instance_init,
    .class_init    = stm32g4_tim16_class_init
};

static void stm32g4_tim16_register_types(void)
{
    type_register_static(&stm32g4_tim16_info);
}

type_init(stm32g4_tim16_register_types)
