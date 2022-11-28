/* stm32g4_wwdg.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_wwdg.h"
#include "migration/vmstate.h"

#define STM32G4_WWDG_MMIO TYPE_STM32G4_WWDG "_mmio"
#define STM32G4_WWDG_MMIO_SIZE 0xC

static uint64_t stm32g4_wwdg_mmio_read(void *opaque, hwaddr offset,
                                       unsigned size)
{
    STM32G4WWDGState *s = STM32G4_WWDG(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x0 ... 0x3:
        /* CR, Control register */
        ret = s->cr;
        break;

    case 0x4 ... 0x7:
        /* CFR, Configuration register */
        ret = s->cfr;
        break;

    case 0x8 ... 0xB:
        /* SR, Status register */
        ret = s->sr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_wwdg_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                    unsigned size)
{
    STM32G4WWDGState *s = STM32G4_WWDG(opaque);

    switch (offset) {
    case 0x0 ... 0x3:
        /* CR, Control register */
        s->cr = value;
        break;

    case 0x4 ... 0x7:
        /* CFR, Configuration register */
        s->cfr = value;
        break;

    case 0x8 ... 0xB:
        /* SR, Status register */
        s->sr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_wwdg_mmio_ops = {
    .read = stm32g4_wwdg_mmio_read,
    .write = stm32g4_wwdg_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_wwdg_instance_init(Object *obj)
{
    STM32G4WWDGState *s = STM32G4_WWDG(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_wwdg_mmio_ops, s,
                          STM32G4_WWDG_MMIO, STM32G4_WWDG_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_wwdg_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4WWDGState *s = STM32G4_WWDG(dev);
}

static void stm32g4_wwdg_reset(DeviceState *dev)
{
    STM32G4WWDGState *s = STM32G4_WWDG(dev);

    s->cr = 0x0000007F;
    s->cfr = 0x0000007F;
    s->sr = 0x00000000;
}

static void stm32g4_wwdg_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4WWDGState *s = STM32G4_WWDG(dev);
}

static Property stm32g4_wwdg_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_wwdg = {
    .name = "stm32g4_wwdg",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cr, STM32G4WWDGState),
        VMSTATE_UINT32(cfr, STM32G4WWDGState),
        VMSTATE_UINT32(sr, STM32G4WWDGState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_wwdg_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_wwdg_realize;
    dc->reset     = stm32g4_wwdg_reset;
    dc->unrealize = stm32g4_wwdg_unrealize;
    dc->vmsd      = &vmstate_stm32g4_wwdg;
    device_class_set_props(dc, stm32g4_wwdg_properties);
}

static TypeInfo stm32g4_wwdg_info = {
    .name          = TYPE_STM32G4_WWDG,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4WWDGState),
    .instance_init = stm32g4_wwdg_instance_init,
    .class_init    = stm32g4_wwdg_class_init
};

static void stm32g4_wwdg_register_types(void)
{
    type_register_static(&stm32g4_wwdg_info);
}

type_init(stm32g4_wwdg_register_types)
