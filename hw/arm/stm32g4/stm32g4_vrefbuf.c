/* stm32g4_vrefbuf.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_vrefbuf.h"
#include "migration/vmstate.h"

#define STM32G4_VREFBUF_MMIO TYPE_STM32G4_VREFBUF "_mmio"
#define STM32G4_VREFBUF_MMIO_SIZE 0x8

static uint64_t stm32g4_vrefbuf_mmio_read(void *opaque, hwaddr offset,
                                          unsigned size)
{
    STM32G4VREFBUFState *s = STM32G4_VREFBUF(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x0 ... 0x3:
        /* VREFBUF_CSR, VREF_BUF Control and Status Register */
        ret = s->vrefbuf_csr;
        break;

    case 0x4 ... 0x7:
        /* VREFBUF_CCR, VREF_BUF Calibration Control Register */
        ret = s->vrefbuf_ccr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_vrefbuf_mmio_write(void *opaque, hwaddr offset,
                                       uint64_t value, unsigned size)
{
    STM32G4VREFBUFState *s = STM32G4_VREFBUF(opaque);

    switch (offset) {
    case 0x0 ... 0x3:
        /* VREFBUF_CSR, VREF_BUF Control and Status Register */
        s->vrefbuf_csr = value;
        break;

    case 0x4 ... 0x7:
        /* VREFBUF_CCR, VREF_BUF Calibration Control Register */
        s->vrefbuf_ccr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_vrefbuf_mmio_ops = {
    .read = stm32g4_vrefbuf_mmio_read,
    .write = stm32g4_vrefbuf_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_vrefbuf_instance_init(Object *obj)
{
    STM32G4VREFBUFState *s = STM32G4_VREFBUF(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_vrefbuf_mmio_ops, s,
                          STM32G4_VREFBUF_MMIO, STM32G4_VREFBUF_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_vrefbuf_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4VREFBUFState *s = STM32G4_VREFBUF(dev);
}

static void stm32g4_vrefbuf_reset(DeviceState *dev)
{
    STM32G4VREFBUFState *s = STM32G4_VREFBUF(dev);

    s->vrefbuf_csr = 0x00000002;
    s->vrefbuf_ccr = 0x00000000;
}

static void stm32g4_vrefbuf_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4VREFBUFState *s = STM32G4_VREFBUF(dev);
}

static Property stm32g4_vrefbuf_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_vrefbuf = {
    .name = "stm32g4_vrefbuf",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(vrefbuf_csr, STM32G4VREFBUFState),
        VMSTATE_UINT32(vrefbuf_ccr, STM32G4VREFBUFState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_vrefbuf_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_vrefbuf_realize;
    dc->reset     = stm32g4_vrefbuf_reset;
    dc->unrealize = stm32g4_vrefbuf_unrealize;
    dc->vmsd      = &vmstate_stm32g4_vrefbuf;
    device_class_set_props(dc, stm32g4_vrefbuf_properties);
}

static TypeInfo stm32g4_vrefbuf_info = {
    .name          = TYPE_STM32G4_VREFBUF,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4VREFBUFState),
    .instance_init = stm32g4_vrefbuf_instance_init,
    .class_init    = stm32g4_vrefbuf_class_init
};

static void stm32g4_vrefbuf_register_types(void)
{
    type_register_static(&stm32g4_vrefbuf_info);
}

type_init(stm32g4_vrefbuf_register_types)
