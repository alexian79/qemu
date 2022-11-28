/* stm32g4_exti.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_exti.h"
#include "migration/vmstate.h"

#define STM32G4_EXTI_MMIO TYPE_STM32G4_EXTI "_mmio"
#define STM32G4_EXTI_MMIO_SIZE 0x38

static uint64_t stm32g4_exti_mmio_read(void *opaque, hwaddr offset,
                                       unsigned size)
{
    STM32G4EXTIState *s = STM32G4_EXTI(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* IMR1, Interrupt mask register */
        ret = s->imr1;
        break;

    case 0x04 ... 0x07:
        /* EMR1, Event mask register */
        ret = s->emr1;
        break;

    case 0x08 ... 0x0B:
        /* RTSR1, Rising Trigger selection register */
        ret = s->rtsr1;
        break;

    case 0x0C ... 0x0F:
        /* FTSR1, Falling Trigger selection register */
        ret = s->ftsr1;
        break;

    case 0x10 ... 0x13:
        /* SWIER1, Software interrupt event register */
        ret = s->swier1;
        break;

    case 0x14 ... 0x17:
        /* PR1, Pending register */
        ret = s->pr1;
        break;

    case 0x20 ... 0x23:
        /* IMR2, Interrupt mask register */
        ret = s->imr2;
        break;

    case 0x24 ... 0x27:
        /* EMR2, Event mask register */
        ret = s->emr2;
        break;

    case 0x28 ... 0x2B:
        /* RTSR2, Rising Trigger selection register */
        ret = s->rtsr2;
        break;

    case 0x2C ... 0x2F:
        /* FTSR2, Falling Trigger selection register */
        ret = s->ftsr2;
        break;

    case 0x30 ... 0x33:
        /* SWIER2, Software interrupt event register */
        ret = s->swier2;
        break;

    case 0x34 ... 0x37:
        /* PR2, Pending register */
        ret = s->pr2;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_exti_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                    unsigned size)
{
    STM32G4EXTIState *s = STM32G4_EXTI(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* IMR1, Interrupt mask register */
        s->imr1 = value;
        break;

    case 0x04 ... 0x07:
        /* EMR1, Event mask register */
        s->emr1 = value;
        break;

    case 0x08 ... 0x0B:
        /* RTSR1, Rising Trigger selection register */
        s->rtsr1 = value;
        break;

    case 0x0C ... 0x0F:
        /* FTSR1, Falling Trigger selection register */
        s->ftsr1 = value;
        break;

    case 0x10 ... 0x13:
        /* SWIER1, Software interrupt event register */
        s->swier1 = value;
        break;

    case 0x14 ... 0x17:
        /* PR1, Pending register */
        s->pr1 = value;
        break;

    case 0x20 ... 0x23:
        /* IMR2, Interrupt mask register */
        s->imr2 = value;
        break;

    case 0x24 ... 0x27:
        /* EMR2, Event mask register */
        s->emr2 = value;
        break;

    case 0x28 ... 0x2B:
        /* RTSR2, Rising Trigger selection register */
        s->rtsr2 = value;
        break;

    case 0x2C ... 0x2F:
        /* FTSR2, Falling Trigger selection register */
        s->ftsr2 = value;
        break;

    case 0x30 ... 0x33:
        /* SWIER2, Software interrupt event register */
        s->swier2 = value;
        break;

    case 0x34 ... 0x37:
        /* PR2, Pending register */
        s->pr2 = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_exti_mmio_ops = {
    .read = stm32g4_exti_mmio_read,
    .write = stm32g4_exti_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_exti_instance_init(Object *obj)
{
    STM32G4EXTIState *s = STM32G4_EXTI(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_exti_mmio_ops, s,
                          STM32G4_EXTI_MMIO, STM32G4_EXTI_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_exti_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4EXTIState *s = STM32G4_EXTI(dev);
}

static void stm32g4_exti_reset(DeviceState *dev)
{
    STM32G4EXTIState *s = STM32G4_EXTI(dev);

    s->imr1 = 0xFF820000;
    s->emr1 = 0x00000000;
    s->rtsr1 = 0x00000000;
    s->ftsr1 = 0x00000000;
    s->swier1 = 0x00000000;
    s->pr1 = 0x00000000;
    s->imr2 = 0xFFFFFF87;
    s->emr2 = 0x00000000;
    s->rtsr2 = 0x00000000;
    s->ftsr2 = 0x00000000;
    s->swier2 = 0x00000000;
    s->pr2 = 0x00000000;
}

static void stm32g4_exti_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4EXTIState *s = STM32G4_EXTI(dev);
}

static Property stm32g4_exti_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_exti = {
    .name = "stm32g4_exti",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(imr1, STM32G4EXTIState),
        VMSTATE_UINT32(emr1, STM32G4EXTIState),
        VMSTATE_UINT32(rtsr1, STM32G4EXTIState),
        VMSTATE_UINT32(ftsr1, STM32G4EXTIState),
        VMSTATE_UINT32(swier1, STM32G4EXTIState),
        VMSTATE_UINT32(pr1, STM32G4EXTIState),
        VMSTATE_UINT32(imr2, STM32G4EXTIState),
        VMSTATE_UINT32(emr2, STM32G4EXTIState),
        VMSTATE_UINT32(rtsr2, STM32G4EXTIState),
        VMSTATE_UINT32(ftsr2, STM32G4EXTIState),
        VMSTATE_UINT32(swier2, STM32G4EXTIState),
        VMSTATE_UINT32(pr2, STM32G4EXTIState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_exti_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_exti_realize;
    dc->reset     = stm32g4_exti_reset;
    dc->unrealize = stm32g4_exti_unrealize;
    dc->vmsd      = &vmstate_stm32g4_exti;
    device_class_set_props(dc, stm32g4_exti_properties);
}

static TypeInfo stm32g4_exti_info = {
    .name          = TYPE_STM32G4_EXTI,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4EXTIState),
    .instance_init = stm32g4_exti_instance_init,
    .class_init    = stm32g4_exti_class_init
};

static void stm32g4_exti_register_types(void)
{
    type_register_static(&stm32g4_exti_info);
}

type_init(stm32g4_exti_register_types)
