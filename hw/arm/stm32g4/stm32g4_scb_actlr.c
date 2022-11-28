/* stm32g4_scb_actlr.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_scb_actlr.h"
#include "migration/vmstate.h"

#define STM32G4_SCB_ACTLR_MMIO TYPE_STM32G4_SCB_ACTLR "_mmio"
#define STM32G4_SCB_ACTLR_MMIO_SIZE 0x4

static uint64_t stm32g4_scb_actlr_mmio_read(void *opaque, hwaddr offset,
                                            unsigned size)
{
    STM32G4SCBACTLRState *s = STM32G4_SCB_ACTLR(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x0 ... 0x3:
        /* ACTRL, Auxiliary control register */
        ret = s->actrl;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_scb_actlr_mmio_write(void *opaque, hwaddr offset,
                                         uint64_t value, unsigned size)
{
    STM32G4SCBACTLRState *s = STM32G4_SCB_ACTLR(opaque);

    switch (offset) {
    case 0x0 ... 0x3:
        /* ACTRL, Auxiliary control register */
        s->actrl = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_scb_actlr_mmio_ops = {
    .read = stm32g4_scb_actlr_mmio_read,
    .write = stm32g4_scb_actlr_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_scb_actlr_instance_init(Object *obj)
{
    STM32G4SCBACTLRState *s = STM32G4_SCB_ACTLR(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_scb_actlr_mmio_ops, s,
                          STM32G4_SCB_ACTLR_MMIO, STM32G4_SCB_ACTLR_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_scb_actlr_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4SCBACTLRState *s = STM32G4_SCB_ACTLR(dev);
}

static void stm32g4_scb_actlr_reset(DeviceState *dev)
{
    STM32G4SCBACTLRState *s = STM32G4_SCB_ACTLR(dev);

    s->actrl = 0x00000000;
}

static void stm32g4_scb_actlr_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4SCBACTLRState *s = STM32G4_SCB_ACTLR(dev);
}

static Property stm32g4_scb_actlr_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_scb_actlr = {
    .name = "stm32g4_scb_actlr",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(actrl, STM32G4SCBACTLRState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_scb_actlr_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_scb_actlr_realize;
    dc->reset     = stm32g4_scb_actlr_reset;
    dc->unrealize = stm32g4_scb_actlr_unrealize;
    dc->vmsd      = &vmstate_stm32g4_scb_actlr;
    device_class_set_props(dc, stm32g4_scb_actlr_properties);
}

static TypeInfo stm32g4_scb_actlr_info = {
    .name          = TYPE_STM32G4_SCB_ACTLR,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4SCBACTLRState),
    .instance_init = stm32g4_scb_actlr_instance_init,
    .class_init    = stm32g4_scb_actlr_class_init
};

static void stm32g4_scb_actlr_register_types(void)
{
    type_register_static(&stm32g4_scb_actlr_info);
}

type_init(stm32g4_scb_actlr_register_types)
