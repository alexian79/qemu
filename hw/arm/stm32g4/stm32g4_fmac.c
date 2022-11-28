/* stm32g4_fmac.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_fmac.h"
#include "migration/vmstate.h"

#define STM32G4_FMAC_MMIO TYPE_STM32G4_FMAC "_mmio"
#define STM32G4_FMAC_MMIO_SIZE 0x20

static uint64_t stm32g4_fmac_mmio_read(void *opaque, hwaddr offset,
                                       unsigned size)
{
    STM32G4FMACState *s = STM32G4_FMAC(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* X1BUFCFG, FMAC X1 Buffer Configuration register */
        ret = s->x1bufcfg;
        break;

    case 0x04 ... 0x07:
        /* X2BUFCFG, FMAC X2 Buffer Configuration register */
        ret = s->x2bufcfg;
        break;

    case 0x08 ... 0x0B:
        /* YBUFCFG, FMAC Y Buffer Configuration register */
        ret = s->ybufcfg;
        break;

    case 0x0C ... 0x0F:
        /* PARAM, FMAC Parameter register */
        ret = s->param;
        break;

    case 0x10 ... 0x13:
        /* CR, FMAC Control register */
        ret = s->cr;
        break;

    case 0x14 ... 0x17:
        /* SR, FMAC Status register */
        ret = s->sr;
        break;

    case 0x18 ... 0x1B:
        /* WDATA, FMAC Write Data register */
        ret = s->wdata;
        break;

    case 0x1C ... 0x1F:
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

static void stm32g4_fmac_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                    unsigned size)
{
    STM32G4FMACState *s = STM32G4_FMAC(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* X1BUFCFG, FMAC X1 Buffer Configuration register */
        s->x1bufcfg = value;
        break;

    case 0x04 ... 0x07:
        /* X2BUFCFG, FMAC X2 Buffer Configuration register */
        s->x2bufcfg = value;
        break;

    case 0x08 ... 0x0B:
        /* YBUFCFG, FMAC Y Buffer Configuration register */
        s->ybufcfg = value;
        break;

    case 0x0C ... 0x0F:
        /* PARAM, FMAC Parameter register */
        s->param = value;
        break;

    case 0x10 ... 0x13:
        /* CR, FMAC Control register */
        s->cr = value;
        break;

    case 0x14 ... 0x17:
        /* SR, FMAC Status register */
        s->sr = value;
        break;

    case 0x18 ... 0x1B:
        /* WDATA, FMAC Write Data register */
        s->wdata = value;
        break;

    case 0x1C ... 0x1F:
        /* RDATA, FMAC Read Data register */
        s->rdata = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_fmac_mmio_ops = {
    .read = stm32g4_fmac_mmio_read,
    .write = stm32g4_fmac_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_fmac_instance_init(Object *obj)
{
    STM32G4FMACState *s = STM32G4_FMAC(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_fmac_mmio_ops, s,
                          STM32G4_FMAC_MMIO, STM32G4_FMAC_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_fmac_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4FMACState *s = STM32G4_FMAC(dev);
}

static void stm32g4_fmac_reset(DeviceState *dev)
{
    STM32G4FMACState *s = STM32G4_FMAC(dev);

    s->x1bufcfg = 0x00000000;
    s->x2bufcfg = 0x00000000;
    s->ybufcfg = 0x00000000;
    s->param = 0x00000000;
    s->cr = 0x00000000;
    s->sr = 0x00000000;
    s->wdata = 0x00000000;
    s->rdata = 0x00000000;
}

static void stm32g4_fmac_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4FMACState *s = STM32G4_FMAC(dev);
}

static Property stm32g4_fmac_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_fmac = {
    .name = "stm32g4_fmac",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(x1bufcfg, STM32G4FMACState),
        VMSTATE_UINT32(x2bufcfg, STM32G4FMACState),
        VMSTATE_UINT32(ybufcfg, STM32G4FMACState),
        VMSTATE_UINT32(param, STM32G4FMACState),
        VMSTATE_UINT32(cr, STM32G4FMACState),
        VMSTATE_UINT32(sr, STM32G4FMACState),
        VMSTATE_UINT32(wdata, STM32G4FMACState),
        VMSTATE_UINT32(rdata, STM32G4FMACState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_fmac_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_fmac_realize;
    dc->reset     = stm32g4_fmac_reset;
    dc->unrealize = stm32g4_fmac_unrealize;
    dc->vmsd      = &vmstate_stm32g4_fmac;
    device_class_set_props(dc, stm32g4_fmac_properties);
}

static TypeInfo stm32g4_fmac_info = {
    .name          = TYPE_STM32G4_FMAC,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4FMACState),
    .instance_init = stm32g4_fmac_instance_init,
    .class_init    = stm32g4_fmac_class_init
};

static void stm32g4_fmac_register_types(void)
{
    type_register_static(&stm32g4_fmac_info);
}

type_init(stm32g4_fmac_register_types)
