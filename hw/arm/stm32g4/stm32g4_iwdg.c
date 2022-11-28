/* stm32g4_iwdg.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_iwdg.h"
#include "migration/vmstate.h"

#define STM32G4_IWDG_MMIO TYPE_STM32G4_IWDG "_mmio"
#define STM32G4_IWDG_MMIO_SIZE 0x14

static uint64_t stm32g4_iwdg_mmio_read(void *opaque, hwaddr offset,
                                       unsigned size)
{
    STM32G4IWDGState *s = STM32G4_IWDG(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* KR, Key register */
        ret = s->kr;
        break;

    case 0x04 ... 0x07:
        /* PR, Prescaler register */
        ret = s->pr;
        break;

    case 0x08 ... 0x0B:
        /* RLR, Reload register */
        ret = s->rlr;
        break;

    case 0x0C ... 0x0F:
        /* SR, Status register */
        ret = s->sr;
        break;

    case 0x10 ... 0x13:
        /* WINR, Window register */
        ret = s->winr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_iwdg_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                    unsigned size)
{
    STM32G4IWDGState *s = STM32G4_IWDG(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* KR, Key register */
        s->kr = value;
        break;

    case 0x04 ... 0x07:
        /* PR, Prescaler register */
        s->pr = value;
        break;

    case 0x08 ... 0x0B:
        /* RLR, Reload register */
        s->rlr = value;
        break;

    case 0x0C ... 0x0F:
        /* SR, Status register */
        s->sr = value;
        break;

    case 0x10 ... 0x13:
        /* WINR, Window register */
        s->winr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_iwdg_mmio_ops = {
    .read = stm32g4_iwdg_mmio_read,
    .write = stm32g4_iwdg_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_iwdg_instance_init(Object *obj)
{
    STM32G4IWDGState *s = STM32G4_IWDG(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_iwdg_mmio_ops, s,
                          STM32G4_IWDG_MMIO, STM32G4_IWDG_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_iwdg_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4IWDGState *s = STM32G4_IWDG(dev);
}

static void stm32g4_iwdg_reset(DeviceState *dev)
{
    STM32G4IWDGState *s = STM32G4_IWDG(dev);

    s->kr = 0x00000000;
    s->pr = 0x00000000;
    s->rlr = 0x00000FFF;
    s->sr = 0x00000000;
    s->winr = 0x00000FFF;
}

static void stm32g4_iwdg_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4IWDGState *s = STM32G4_IWDG(dev);
}

static Property stm32g4_iwdg_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_iwdg = {
    .name = "stm32g4_iwdg",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(kr, STM32G4IWDGState),
        VMSTATE_UINT32(pr, STM32G4IWDGState),
        VMSTATE_UINT32(rlr, STM32G4IWDGState),
        VMSTATE_UINT32(sr, STM32G4IWDGState),
        VMSTATE_UINT32(winr, STM32G4IWDGState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_iwdg_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_iwdg_realize;
    dc->reset     = stm32g4_iwdg_reset;
    dc->unrealize = stm32g4_iwdg_unrealize;
    dc->vmsd      = &vmstate_stm32g4_iwdg;
    device_class_set_props(dc, stm32g4_iwdg_properties);
}

static TypeInfo stm32g4_iwdg_info = {
    .name          = TYPE_STM32G4_IWDG,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4IWDGState),
    .instance_init = stm32g4_iwdg_instance_init,
    .class_init    = stm32g4_iwdg_class_init
};

static void stm32g4_iwdg_register_types(void)
{
    type_register_static(&stm32g4_iwdg_info);
}

type_init(stm32g4_iwdg_register_types)
