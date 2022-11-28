/* stm32g4_comp.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_comp.h"
#include "migration/vmstate.h"

#define STM32G4_COMP_MMIO TYPE_STM32G4_COMP "_mmio"
#define STM32G4_COMP_MMIO_SIZE 0x1C

static uint64_t stm32g4_comp_mmio_read(void *opaque, hwaddr offset,
                                       unsigned size)
{
    STM32G4COMPState *s = STM32G4_COMP(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* COMP_C1CSR, Comparator control/status register */
        ret = s->comp_c1csr;
        break;

    case 0x04 ... 0x07:
        /* COMP_C2CSR, Comparator control/status register */
        ret = s->comp_c2csr;
        break;

    case 0x08 ... 0x0B:
        /* COMP_C3CSR, Comparator control/status register */
        ret = s->comp_c3csr;
        break;

    case 0x0C ... 0x0F:
        /* COMP_C4CSR, Comparator control/status register */
        ret = s->comp_c4csr;
        break;

    case 0x10 ... 0x13:
        /* COMP_C5CSR, Comparator control/status register */
        ret = s->comp_c5csr;
        break;

    case 0x14 ... 0x17:
        /* COMP_C6CSR, Comparator control/status register */
        ret = s->comp_c6csr;
        break;

    case 0x18 ... 0x1B:
        /* COMP_C7CSR, Comparator control/status register */
        ret = s->comp_c7csr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_comp_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                    unsigned size)
{
    STM32G4COMPState *s = STM32G4_COMP(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* COMP_C1CSR, Comparator control/status register */
        s->comp_c1csr = value;
        break;

    case 0x04 ... 0x07:
        /* COMP_C2CSR, Comparator control/status register */
        s->comp_c2csr = value;
        break;

    case 0x08 ... 0x0B:
        /* COMP_C3CSR, Comparator control/status register */
        s->comp_c3csr = value;
        break;

    case 0x0C ... 0x0F:
        /* COMP_C4CSR, Comparator control/status register */
        s->comp_c4csr = value;
        break;

    case 0x10 ... 0x13:
        /* COMP_C5CSR, Comparator control/status register */
        s->comp_c5csr = value;
        break;

    case 0x14 ... 0x17:
        /* COMP_C6CSR, Comparator control/status register */
        s->comp_c6csr = value;
        break;

    case 0x18 ... 0x1B:
        /* COMP_C7CSR, Comparator control/status register */
        s->comp_c7csr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_comp_mmio_ops = {
    .read = stm32g4_comp_mmio_read,
    .write = stm32g4_comp_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_comp_instance_init(Object *obj)
{
    STM32G4COMPState *s = STM32G4_COMP(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_comp_mmio_ops, s,
                          STM32G4_COMP_MMIO, STM32G4_COMP_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_comp_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4COMPState *s = STM32G4_COMP(dev);
}

static void stm32g4_comp_reset(DeviceState *dev)
{
    STM32G4COMPState *s = STM32G4_COMP(dev);

    s->comp_c1csr = 0x00000000;
    s->comp_c2csr = 0x00000000;
    s->comp_c3csr = 0x00000000;
    s->comp_c4csr = 0x00000000;
    s->comp_c5csr = 0x00000000;
    s->comp_c6csr = 0x00000000;
    s->comp_c7csr = 0x00000000;
}

static void stm32g4_comp_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4COMPState *s = STM32G4_COMP(dev);
}

static Property stm32g4_comp_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_comp = {
    .name = "stm32g4_comp",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(comp_c1csr, STM32G4COMPState),
        VMSTATE_UINT32(comp_c2csr, STM32G4COMPState),
        VMSTATE_UINT32(comp_c3csr, STM32G4COMPState),
        VMSTATE_UINT32(comp_c4csr, STM32G4COMPState),
        VMSTATE_UINT32(comp_c5csr, STM32G4COMPState),
        VMSTATE_UINT32(comp_c6csr, STM32G4COMPState),
        VMSTATE_UINT32(comp_c7csr, STM32G4COMPState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_comp_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_comp_realize;
    dc->reset     = stm32g4_comp_reset;
    dc->unrealize = stm32g4_comp_unrealize;
    dc->vmsd      = &vmstate_stm32g4_comp;
    device_class_set_props(dc, stm32g4_comp_properties);
}

static TypeInfo stm32g4_comp_info = {
    .name          = TYPE_STM32G4_COMP,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4COMPState),
    .instance_init = stm32g4_comp_instance_init,
    .class_init    = stm32g4_comp_class_init
};

static void stm32g4_comp_register_types(void)
{
    type_register_static(&stm32g4_comp_info);
}

type_init(stm32g4_comp_register_types)
