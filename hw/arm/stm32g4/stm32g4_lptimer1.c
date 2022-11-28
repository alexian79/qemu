/* stm32g4_lptimer1.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_lptimer1.h"
#include "migration/vmstate.h"

#define STM32G4_LPTIMER1_MMIO TYPE_STM32G4_LPTIMER1 "_mmio"
#define STM32G4_LPTIMER1_MMIO_SIZE 0x24

static uint64_t stm32g4_lptimer1_mmio_read(void *opaque, hwaddr offset,
                                           unsigned size)
{
    STM32G4LPTIMER1State *s = STM32G4_LPTIMER1(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* ISR, Interrupt and Status Register */
        ret = s->isr;
        break;

    case 0x04 ... 0x07:
        /* ICR, Interrupt Clear Register */
        ret = s->icr;
        break;

    case 0x08 ... 0x0B:
        /* IER, Interrupt Enable Register */
        ret = s->ier;
        break;

    case 0x0C ... 0x0F:
        /* CFGR, Configuration Register */
        ret = s->cfgr;
        break;

    case 0x10 ... 0x13:
        /* CR, Control Register */
        ret = s->cr;
        break;

    case 0x14 ... 0x17:
        /* CMP, Compare Register */
        ret = s->cmp;
        break;

    case 0x18 ... 0x1B:
        /* ARR, Autoreload Register */
        ret = s->arr;
        break;

    case 0x1C ... 0x1F:
        /* CNT, Counter Register */
        ret = s->cnt;
        break;

    case 0x20 ... 0x23:
        /* OR, option register */
        ret = s->or;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_lptimer1_mmio_write(void *opaque, hwaddr offset,
                                        uint64_t value, unsigned size)
{
    STM32G4LPTIMER1State *s = STM32G4_LPTIMER1(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* ISR, Interrupt and Status Register */
        s->isr = value;
        break;

    case 0x04 ... 0x07:
        /* ICR, Interrupt Clear Register */
        s->icr = value;
        break;

    case 0x08 ... 0x0B:
        /* IER, Interrupt Enable Register */
        s->ier = value;
        break;

    case 0x0C ... 0x0F:
        /* CFGR, Configuration Register */
        s->cfgr = value;
        break;

    case 0x10 ... 0x13:
        /* CR, Control Register */
        s->cr = value;
        break;

    case 0x14 ... 0x17:
        /* CMP, Compare Register */
        s->cmp = value;
        break;

    case 0x18 ... 0x1B:
        /* ARR, Autoreload Register */
        s->arr = value;
        break;

    case 0x1C ... 0x1F:
        /* CNT, Counter Register */
        s->cnt = value;
        break;

    case 0x20 ... 0x23:
        /* OR, option register */
        s->or = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_lptimer1_mmio_ops = {
    .read = stm32g4_lptimer1_mmio_read,
    .write = stm32g4_lptimer1_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_lptimer1_instance_init(Object *obj)
{
    STM32G4LPTIMER1State *s = STM32G4_LPTIMER1(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_lptimer1_mmio_ops, s,
                          STM32G4_LPTIMER1_MMIO, STM32G4_LPTIMER1_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_lptimer1_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4LPTIMER1State *s = STM32G4_LPTIMER1(dev);
}

static void stm32g4_lptimer1_reset(DeviceState *dev)
{
    STM32G4LPTIMER1State *s = STM32G4_LPTIMER1(dev);

    s->isr = 0x00000000;
    s->icr = 0x00000000;
    s->ier = 0x00000000;
    s->cfgr = 0x00000000;
    s->cr = 0x00000000;
    s->cmp = 0x00000000;
    s->arr = 0x00000001;
    s->cnt = 0x00000000;
    s->or = 0x00000000;
}

static void stm32g4_lptimer1_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4LPTIMER1State *s = STM32G4_LPTIMER1(dev);
}

static Property stm32g4_lptimer1_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_lptimer1 = {
    .name = "stm32g4_lptimer1",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(isr, STM32G4LPTIMER1State),
        VMSTATE_UINT32(icr, STM32G4LPTIMER1State),
        VMSTATE_UINT32(ier, STM32G4LPTIMER1State),
        VMSTATE_UINT32(cfgr, STM32G4LPTIMER1State),
        VMSTATE_UINT32(cr, STM32G4LPTIMER1State),
        VMSTATE_UINT32(cmp, STM32G4LPTIMER1State),
        VMSTATE_UINT32(arr, STM32G4LPTIMER1State),
        VMSTATE_UINT32(cnt, STM32G4LPTIMER1State),
        VMSTATE_UINT32(or, STM32G4LPTIMER1State),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_lptimer1_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_lptimer1_realize;
    dc->reset     = stm32g4_lptimer1_reset;
    dc->unrealize = stm32g4_lptimer1_unrealize;
    dc->vmsd      = &vmstate_stm32g4_lptimer1;
    device_class_set_props(dc, stm32g4_lptimer1_properties);
}

static TypeInfo stm32g4_lptimer1_info = {
    .name          = TYPE_STM32G4_LPTIMER1,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4LPTIMER1State),
    .instance_init = stm32g4_lptimer1_instance_init,
    .class_init    = stm32g4_lptimer1_class_init
};

static void stm32g4_lptimer1_register_types(void)
{
    type_register_static(&stm32g4_lptimer1_info);
}

type_init(stm32g4_lptimer1_register_types)
