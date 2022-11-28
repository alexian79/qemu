/* stm32g4_rng.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_rng.h"
#include "migration/vmstate.h"

#define STM32G4_RNG_MMIO TYPE_STM32G4_RNG "_mmio"
#define STM32G4_RNG_MMIO_SIZE 0xC

static uint64_t stm32g4_rng_mmio_read(void *opaque, hwaddr offset,
                                      unsigned size)
{
    STM32G4RNGState *s = STM32G4_RNG(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x0 ... 0x3:
        /* CR, control register */
        ret = s->cr;
        break;

    case 0x4 ... 0x7:
        /* SR, status register */
        ret = s->sr;
        break;

    case 0x8 ... 0xB:
        /* DR, data register */
        ret = s->dr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_rng_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                   unsigned size)
{
    STM32G4RNGState *s = STM32G4_RNG(opaque);

    switch (offset) {
    case 0x0 ... 0x3:
        /* CR, control register */
        s->cr = value;
        break;

    case 0x4 ... 0x7:
        /* SR, status register */
        s->sr = value;
        break;

    case 0x8 ... 0xB:
        /* DR, data register */
        s->dr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_rng_mmio_ops = {
    .read = stm32g4_rng_mmio_read,
    .write = stm32g4_rng_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_rng_instance_init(Object *obj)
{
    STM32G4RNGState *s = STM32G4_RNG(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_rng_mmio_ops, s,
                          STM32G4_RNG_MMIO, STM32G4_RNG_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_rng_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4RNGState *s = STM32G4_RNG(dev);
}

static void stm32g4_rng_reset(DeviceState *dev)
{
    STM32G4RNGState *s = STM32G4_RNG(dev);

    s->cr = 0x00000000;
    s->sr = 0x00000000;
    s->dr = 0x00000000;
}

static void stm32g4_rng_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4RNGState *s = STM32G4_RNG(dev);
}

static Property stm32g4_rng_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_rng = {
    .name = "stm32g4_rng",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cr, STM32G4RNGState),
        VMSTATE_UINT32(sr, STM32G4RNGState),
        VMSTATE_UINT32(dr, STM32G4RNGState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_rng_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_rng_realize;
    dc->reset     = stm32g4_rng_reset;
    dc->unrealize = stm32g4_rng_unrealize;
    dc->vmsd      = &vmstate_stm32g4_rng;
    device_class_set_props(dc, stm32g4_rng_properties);
}

static TypeInfo stm32g4_rng_info = {
    .name          = TYPE_STM32G4_RNG,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4RNGState),
    .instance_init = stm32g4_rng_instance_init,
    .class_init    = stm32g4_rng_class_init
};

static void stm32g4_rng_register_types(void)
{
    type_register_static(&stm32g4_rng_info);
}

type_init(stm32g4_rng_register_types)
