/* stm32g4_quadspi.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_quadspi.h"
#include "migration/vmstate.h"

#define STM32G4_QUADSPI_MMIO TYPE_STM32G4_QUADSPI "_mmio"
#define STM32G4_QUADSPI_MMIO_SIZE 0x34

static uint64_t stm32g4_quadspi_mmio_read(void *opaque, hwaddr offset,
                                          unsigned size)
{
    STM32G4QUADSPIState *s = STM32G4_QUADSPI(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* CR, control register */
        ret = s->cr;
        break;

    case 0x04 ... 0x07:
        /* DCR, device configuration register */
        ret = s->dcr;
        break;

    case 0x08 ... 0x0B:
        /* SR, status register */
        ret = s->sr;
        break;

    case 0x0C ... 0x0F:
        /* FCR, flag clear register */
        ret = s->fcr;
        break;

    case 0x10 ... 0x13:
        /* DLR, data length register */
        ret = s->dlr;
        break;

    case 0x14 ... 0x17:
        /* CCR, communication configuration register */
        ret = s->ccr;
        break;

    case 0x18 ... 0x1B:
        /* AR, address register */
        ret = s->ar;
        break;

    case 0x1C ... 0x1F:
        /* ABR, ABR */
        ret = s->abr;
        break;

    case 0x20 ... 0x23:
        /* DR, data register */
        ret = s->dr;
        break;

    case 0x24 ... 0x27:
        /* PSMKR, polling status mask register */
        ret = s->psmkr;
        break;

    case 0x28 ... 0x2B:
        /* PSMAR, polling status match register */
        ret = s->psmar;
        break;

    case 0x2C ... 0x2F:
        /* PIR, polling interval register */
        ret = s->pir;
        break;

    case 0x30 ... 0x33:
        /* LPTR, low-power timeout register */
        ret = s->lptr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_quadspi_mmio_write(void *opaque, hwaddr offset,
                                       uint64_t value, unsigned size)
{
    STM32G4QUADSPIState *s = STM32G4_QUADSPI(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* CR, control register */
        s->cr = value;
        break;

    case 0x04 ... 0x07:
        /* DCR, device configuration register */
        s->dcr = value;
        break;

    case 0x08 ... 0x0B:
        /* SR, status register */
        s->sr = value;
        break;

    case 0x0C ... 0x0F:
        /* FCR, flag clear register */
        s->fcr = value;
        break;

    case 0x10 ... 0x13:
        /* DLR, data length register */
        s->dlr = value;
        break;

    case 0x14 ... 0x17:
        /* CCR, communication configuration register */
        s->ccr = value;
        break;

    case 0x18 ... 0x1B:
        /* AR, address register */
        s->ar = value;
        break;

    case 0x1C ... 0x1F:
        /* ABR, ABR */
        s->abr = value;
        break;

    case 0x20 ... 0x23:
        /* DR, data register */
        s->dr = value;
        break;

    case 0x24 ... 0x27:
        /* PSMKR, polling status mask register */
        s->psmkr = value;
        break;

    case 0x28 ... 0x2B:
        /* PSMAR, polling status match register */
        s->psmar = value;
        break;

    case 0x2C ... 0x2F:
        /* PIR, polling interval register */
        s->pir = value;
        break;

    case 0x30 ... 0x33:
        /* LPTR, low-power timeout register */
        s->lptr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_quadspi_mmio_ops = {
    .read = stm32g4_quadspi_mmio_read,
    .write = stm32g4_quadspi_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_quadspi_instance_init(Object *obj)
{
    STM32G4QUADSPIState *s = STM32G4_QUADSPI(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_quadspi_mmio_ops, s,
                          STM32G4_QUADSPI_MMIO, STM32G4_QUADSPI_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_quadspi_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4QUADSPIState *s = STM32G4_QUADSPI(dev);
}

static void stm32g4_quadspi_reset(DeviceState *dev)
{
    STM32G4QUADSPIState *s = STM32G4_QUADSPI(dev);

    s->cr = 0x00000000;
    s->dcr = 0x00000000;
    s->sr = 0x00000000;
    s->fcr = 0x00000000;
    s->dlr = 0x00000000;
    s->ccr = 0x00000000;
    s->ar = 0x00000000;
    s->abr = 0x00000000;
    s->dr = 0x00000000;
    s->psmkr = 0x00000000;
    s->psmar = 0x00000000;
    s->pir = 0x00000000;
    s->lptr = 0x00000000;
}

static void stm32g4_quadspi_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4QUADSPIState *s = STM32G4_QUADSPI(dev);
}

static Property stm32g4_quadspi_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_quadspi = {
    .name = "stm32g4_quadspi",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cr, STM32G4QUADSPIState),
        VMSTATE_UINT32(dcr, STM32G4QUADSPIState),
        VMSTATE_UINT32(sr, STM32G4QUADSPIState),
        VMSTATE_UINT32(fcr, STM32G4QUADSPIState),
        VMSTATE_UINT32(dlr, STM32G4QUADSPIState),
        VMSTATE_UINT32(ccr, STM32G4QUADSPIState),
        VMSTATE_UINT32(ar, STM32G4QUADSPIState),
        VMSTATE_UINT32(abr, STM32G4QUADSPIState),
        VMSTATE_UINT32(dr, STM32G4QUADSPIState),
        VMSTATE_UINT32(psmkr, STM32G4QUADSPIState),
        VMSTATE_UINT32(psmar, STM32G4QUADSPIState),
        VMSTATE_UINT32(pir, STM32G4QUADSPIState),
        VMSTATE_UINT32(lptr, STM32G4QUADSPIState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_quadspi_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_quadspi_realize;
    dc->reset     = stm32g4_quadspi_reset;
    dc->unrealize = stm32g4_quadspi_unrealize;
    dc->vmsd      = &vmstate_stm32g4_quadspi;
    device_class_set_props(dc, stm32g4_quadspi_properties);
}

static TypeInfo stm32g4_quadspi_info = {
    .name          = TYPE_STM32G4_QUADSPI,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4QUADSPIState),
    .instance_init = stm32g4_quadspi_instance_init,
    .class_init    = stm32g4_quadspi_class_init
};

static void stm32g4_quadspi_register_types(void)
{
    type_register_static(&stm32g4_quadspi_info);
}

type_init(stm32g4_quadspi_register_types)
