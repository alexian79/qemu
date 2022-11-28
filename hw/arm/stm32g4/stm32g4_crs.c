/* stm32g4_crs.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_crs.h"
#include "migration/vmstate.h"

#define STM32G4_CRS_MMIO TYPE_STM32G4_CRS "_mmio"
#define STM32G4_CRS_MMIO_SIZE 0x10

static uint64_t stm32g4_crs_mmio_read(void *opaque, hwaddr offset,
                                      unsigned size)
{
    STM32G4CRSState *s = STM32G4_CRS(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* CR, CRS control register */
        ret = s->cr;
        break;

    case 0x04 ... 0x07:
        /* CFGR, This register can be written only when the frequency error
            counter is disabled (CEN bit is cleared in CRS_CR). When the counter
            is enabled, this register is write-protected. */
        ret = s->cfgr;
        break;

    case 0x08 ... 0x0B:
        /* ISR, CRS interrupt and status register */
        ret = s->isr;
        break;

    case 0x0C ... 0x0F:
        /* ICR, CRS interrupt flag clear register */
        ret = s->icr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_crs_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                   unsigned size)
{
    STM32G4CRSState *s = STM32G4_CRS(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* CR, CRS control register */
        s->cr = value;
        break;

    case 0x04 ... 0x07:
        /* CFGR, This register can be written only when the frequency error
            counter is disabled (CEN bit is cleared in CRS_CR). When the counter
            is enabled, this register is write-protected. */
        s->cfgr = value;
        break;

    case 0x08 ... 0x0B:
        /* ISR, CRS interrupt and status register */
        s->isr = value;
        break;

    case 0x0C ... 0x0F:
        /* ICR, CRS interrupt flag clear register */
        s->icr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_crs_mmio_ops = {
    .read = stm32g4_crs_mmio_read,
    .write = stm32g4_crs_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_crs_instance_init(Object *obj)
{
    STM32G4CRSState *s = STM32G4_CRS(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_crs_mmio_ops, s,
                          STM32G4_CRS_MMIO, STM32G4_CRS_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_crs_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4CRSState *s = STM32G4_CRS(dev);
}

static void stm32g4_crs_reset(DeviceState *dev)
{
    STM32G4CRSState *s = STM32G4_CRS(dev);

    s->cr = 0x00004000;
    s->cfgr = 0x2022BB7F;
    s->isr = 0x00000000;
    s->icr = 0x00000000;
}

static void stm32g4_crs_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4CRSState *s = STM32G4_CRS(dev);
}

static Property stm32g4_crs_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_crs = {
    .name = "stm32g4_crs",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cr, STM32G4CRSState),
        VMSTATE_UINT32(cfgr, STM32G4CRSState),
        VMSTATE_UINT32(isr, STM32G4CRSState),
        VMSTATE_UINT32(icr, STM32G4CRSState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_crs_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_crs_realize;
    dc->reset     = stm32g4_crs_reset;
    dc->unrealize = stm32g4_crs_unrealize;
    dc->vmsd      = &vmstate_stm32g4_crs;
    device_class_set_props(dc, stm32g4_crs_properties);
}

static TypeInfo stm32g4_crs_info = {
    .name          = TYPE_STM32G4_CRS,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4CRSState),
    .instance_init = stm32g4_crs_instance_init,
    .class_init    = stm32g4_crs_class_init
};

static void stm32g4_crs_register_types(void)
{
    type_register_static(&stm32g4_crs_info);
}

type_init(stm32g4_crs_register_types)
