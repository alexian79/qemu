/* stm32g4_gpioc.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_gpioc.h"
#include "migration/vmstate.h"

#define STM32G4_GPIOC_MMIO TYPE_STM32G4_GPIOC "_mmio"
#define STM32G4_GPIOC_MMIO_SIZE 0x2C

static uint64_t stm32g4_gpioc_mmio_read(void *opaque, hwaddr offset,
                                        unsigned size)
{
    STM32G4GPIOCState *s = STM32G4_GPIOC(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* MODER, GPIO port mode register */
        ret = s->moder;
        break;

    case 0x04 ... 0x07:
        /* OTYPER, GPIO port output type register */
        ret = s->otyper;
        break;

    case 0x08 ... 0x0B:
        /* OSPEEDR, GPIO port output speed register */
        ret = s->ospeedr;
        break;

    case 0x0C ... 0x0F:
        /* PUPDR, GPIO port pull-up/pull-down register */
        ret = s->pupdr;
        break;

    case 0x10 ... 0x13:
        /* IDR, GPIO port input data register */
        ret = s->idr;
        break;

    case 0x14 ... 0x17:
        /* ODR, GPIO port output data register */
        ret = s->odr;
        break;

    case 0x18 ... 0x1B:
        /* BSRR, GPIO port bit set/reset register */
        ret = s->bsrr;
        break;

    case 0x1C ... 0x1F:
        /* LCKR, GPIO port configuration lock register */
        ret = s->lckr;
        break;

    case 0x20 ... 0x23:
        /* AFRL, GPIO alternate function low register */
        ret = s->afrl;
        break;

    case 0x24 ... 0x27:
        /* AFRH, GPIO alternate function high register */
        ret = s->afrh;
        break;

    case 0x28 ... 0x2B:
        /* BRR, GPIO port bit reset register */
        ret = s->brr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_gpioc_mmio_write(void *opaque, hwaddr offset,
                                     uint64_t value, unsigned size)
{
    STM32G4GPIOCState *s = STM32G4_GPIOC(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* MODER, GPIO port mode register */
        s->moder = value;
        break;

    case 0x04 ... 0x07:
        /* OTYPER, GPIO port output type register */
        s->otyper = value;
        break;

    case 0x08 ... 0x0B:
        /* OSPEEDR, GPIO port output speed register */
        s->ospeedr = value;
        break;

    case 0x0C ... 0x0F:
        /* PUPDR, GPIO port pull-up/pull-down register */
        s->pupdr = value;
        break;

    case 0x10 ... 0x13:
        /* IDR, GPIO port input data register */
        s->idr = value;
        break;

    case 0x14 ... 0x17:
        /* ODR, GPIO port output data register */
        s->odr = value;
        break;

    case 0x18 ... 0x1B:
        /* BSRR, GPIO port bit set/reset register */
        s->bsrr = value;
        break;

    case 0x1C ... 0x1F:
        /* LCKR, GPIO port configuration lock register */
        s->lckr = value;
        break;

    case 0x20 ... 0x23:
        /* AFRL, GPIO alternate function low register */
        s->afrl = value;
        break;

    case 0x24 ... 0x27:
        /* AFRH, GPIO alternate function high register */
        s->afrh = value;
        break;

    case 0x28 ... 0x2B:
        /* BRR, GPIO port bit reset register */
        s->brr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_gpioc_mmio_ops = {
    .read = stm32g4_gpioc_mmio_read,
    .write = stm32g4_gpioc_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_gpioc_instance_init(Object *obj)
{
    STM32G4GPIOCState *s = STM32G4_GPIOC(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_gpioc_mmio_ops, s,
                          STM32G4_GPIOC_MMIO, STM32G4_GPIOC_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_gpioc_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4GPIOCState *s = STM32G4_GPIOC(dev);
}

static void stm32g4_gpioc_reset(DeviceState *dev)
{
    STM32G4GPIOCState *s = STM32G4_GPIOC(dev);

    s->moder = 0xFFFFFFFF;
    s->otyper = 0x00000000;
    s->ospeedr = 0x00000000;
    s->pupdr = 0x00000000;
    s->idr = 0x00000000;
    s->odr = 0x00000000;
    s->bsrr = 0x00000000;
    s->lckr = 0x00000000;
    s->afrl = 0x00000000;
    s->afrh = 0x00000000;
    s->brr = 0x00000000;
}

static void stm32g4_gpioc_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4GPIOCState *s = STM32G4_GPIOC(dev);
}

static Property stm32g4_gpioc_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_gpioc = {
    .name = "stm32g4_gpioc",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(moder, STM32G4GPIOCState),
        VMSTATE_UINT32(otyper, STM32G4GPIOCState),
        VMSTATE_UINT32(ospeedr, STM32G4GPIOCState),
        VMSTATE_UINT32(pupdr, STM32G4GPIOCState),
        VMSTATE_UINT32(idr, STM32G4GPIOCState),
        VMSTATE_UINT32(odr, STM32G4GPIOCState),
        VMSTATE_UINT32(bsrr, STM32G4GPIOCState),
        VMSTATE_UINT32(lckr, STM32G4GPIOCState),
        VMSTATE_UINT32(afrl, STM32G4GPIOCState),
        VMSTATE_UINT32(afrh, STM32G4GPIOCState),
        VMSTATE_UINT32(brr, STM32G4GPIOCState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_gpioc_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_gpioc_realize;
    dc->reset     = stm32g4_gpioc_reset;
    dc->unrealize = stm32g4_gpioc_unrealize;
    dc->vmsd      = &vmstate_stm32g4_gpioc;
    device_class_set_props(dc, stm32g4_gpioc_properties);
}

static TypeInfo stm32g4_gpioc_info = {
    .name          = TYPE_STM32G4_GPIOC,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4GPIOCState),
    .instance_init = stm32g4_gpioc_instance_init,
    .class_init    = stm32g4_gpioc_class_init
};

static void stm32g4_gpioc_register_types(void)
{
    type_register_static(&stm32g4_gpioc_info);
}

type_init(stm32g4_gpioc_register_types)
