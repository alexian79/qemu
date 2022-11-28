/* stm32g4_crc.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_crc.h"
#include "migration/vmstate.h"

#define STM32G4_CRC_MMIO TYPE_STM32G4_CRC "_mmio"
#define STM32G4_CRC_MMIO_SIZE 0x18

static uint64_t stm32g4_crc_mmio_read(void *opaque, hwaddr offset,
                                      unsigned size)
{
    STM32G4CRCState *s = STM32G4_CRC(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* DR, Data register */
        ret = s->dr;
        break;

    case 0x04 ... 0x07:
        /* IDR, Independent data register */
        ret = s->idr;
        break;

    case 0x08 ... 0x0B:
        /* CR, Control register */
        ret = s->cr;
        break;

    case 0x10 ... 0x13:
        /* INIT, Initial CRC value */
        ret = s->init;
        break;

    case 0x14 ... 0x17:
        /* POL, polynomial */
        ret = s->pol;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_crc_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                   unsigned size)
{
    STM32G4CRCState *s = STM32G4_CRC(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* DR, Data register */
        s->dr = value;
        break;

    case 0x04 ... 0x07:
        /* IDR, Independent data register */
        s->idr = value;
        break;

    case 0x08 ... 0x0B:
        /* CR, Control register */
        s->cr = value;
        break;

    case 0x10 ... 0x13:
        /* INIT, Initial CRC value */
        s->init = value;
        break;

    case 0x14 ... 0x17:
        /* POL, polynomial */
        s->pol = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_crc_mmio_ops = {
    .read = stm32g4_crc_mmio_read,
    .write = stm32g4_crc_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_crc_instance_init(Object *obj)
{
    STM32G4CRCState *s = STM32G4_CRC(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_crc_mmio_ops, s,
                          STM32G4_CRC_MMIO, STM32G4_CRC_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_crc_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4CRCState *s = STM32G4_CRC(dev);
}

static void stm32g4_crc_reset(DeviceState *dev)
{
    STM32G4CRCState *s = STM32G4_CRC(dev);

    s->dr = 0xFFFFFFFF;
    s->idr = 0x00000000;
    s->cr = 0x00000000;
    s->init = 0xFFFFFFFF;
    s->pol = 0x04C11DB7;
}

static void stm32g4_crc_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4CRCState *s = STM32G4_CRC(dev);
}

static Property stm32g4_crc_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_crc = {
    .name = "stm32g4_crc",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(dr, STM32G4CRCState),
        VMSTATE_UINT32(idr, STM32G4CRCState),
        VMSTATE_UINT32(cr, STM32G4CRCState),
        VMSTATE_UINT32(init, STM32G4CRCState),
        VMSTATE_UINT32(pol, STM32G4CRCState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_crc_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_crc_realize;
    dc->reset     = stm32g4_crc_reset;
    dc->unrealize = stm32g4_crc_unrealize;
    dc->vmsd      = &vmstate_stm32g4_crc;
    device_class_set_props(dc, stm32g4_crc_properties);
}

static TypeInfo stm32g4_crc_info = {
    .name          = TYPE_STM32G4_CRC,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4CRCState),
    .instance_init = stm32g4_crc_instance_init,
    .class_init    = stm32g4_crc_class_init
};

static void stm32g4_crc_register_types(void)
{
    type_register_static(&stm32g4_crc_info);
}

type_init(stm32g4_crc_register_types)
