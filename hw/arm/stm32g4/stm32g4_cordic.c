/* stm32g4_cordic.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_cordic.h"
#include "migration/vmstate.h"

#define STM32G4_CORDIC_MMIO TYPE_STM32G4_CORDIC "_mmio"
#define STM32G4_CORDIC_MMIO_SIZE 0xC

static uint64_t stm32g4_cordic_mmio_read(void *opaque, hwaddr offset,
                                         unsigned size)
{
    STM32G4CORDICState *s = STM32G4_CORDIC(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x0 ... 0x3:
        /* CSR, CORDIC Control Status register */
        ret = s->csr;
        break;

    case 0x4 ... 0x7:
        /* WDATA, FMAC Write Data register */
        ret = s->wdata;
        break;

    case 0x8 ... 0xB:
        /* RDATA, FMAC Read Data register */
        ret = s->rdata;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_cordic_mmio_write(void *opaque, hwaddr offset,
                                      uint64_t value, unsigned size)
{
    STM32G4CORDICState *s = STM32G4_CORDIC(opaque);

    switch (offset) {
    case 0x0 ... 0x3:
        /* CSR, CORDIC Control Status register */
        s->csr = value;
        break;

    case 0x4 ... 0x7:
        /* WDATA, FMAC Write Data register */
        s->wdata = value;
        break;

    case 0x8 ... 0xB:
        /* RDATA, FMAC Read Data register */
        s->rdata = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_cordic_mmio_ops = {
    .read = stm32g4_cordic_mmio_read,
    .write = stm32g4_cordic_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_cordic_instance_init(Object *obj)
{
    STM32G4CORDICState *s = STM32G4_CORDIC(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_cordic_mmio_ops, s,
                          STM32G4_CORDIC_MMIO, STM32G4_CORDIC_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_cordic_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4CORDICState *s = STM32G4_CORDIC(dev);
}

static void stm32g4_cordic_reset(DeviceState *dev)
{
    STM32G4CORDICState *s = STM32G4_CORDIC(dev);

    s->csr = 0x00000000;
    s->wdata = 0x00000000;
    s->rdata = 0x00000000;
}

static void stm32g4_cordic_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4CORDICState *s = STM32G4_CORDIC(dev);
}

static Property stm32g4_cordic_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_cordic = {
    .name = "stm32g4_cordic",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(csr, STM32G4CORDICState),
        VMSTATE_UINT32(wdata, STM32G4CORDICState),
        VMSTATE_UINT32(rdata, STM32G4CORDICState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_cordic_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_cordic_realize;
    dc->reset     = stm32g4_cordic_reset;
    dc->unrealize = stm32g4_cordic_unrealize;
    dc->vmsd      = &vmstate_stm32g4_cordic;
    device_class_set_props(dc, stm32g4_cordic_properties);
}

static TypeInfo stm32g4_cordic_info = {
    .name          = TYPE_STM32G4_CORDIC,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4CORDICState),
    .instance_init = stm32g4_cordic_instance_init,
    .class_init    = stm32g4_cordic_class_init
};

static void stm32g4_cordic_register_types(void)
{
    type_register_static(&stm32g4_cordic_info);
}

type_init(stm32g4_cordic_register_types)
