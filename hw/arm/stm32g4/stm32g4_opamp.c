/* stm32g4_opamp.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_opamp.h"
#include "migration/vmstate.h"

#define STM32G4_OPAMP_MMIO TYPE_STM32G4_OPAMP "_mmio"
#define STM32G4_OPAMP_MMIO_SIZE 0x30

static uint64_t stm32g4_opamp_mmio_read(void *opaque, hwaddr offset,
                                        unsigned size)
{
    STM32G4OPAMPState *s = STM32G4_OPAMP(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* OPAMP1_CSR, OPAMP1 control/status register */
        ret = s->opamp1_csr;
        break;

    case 0x04 ... 0x07:
        /* OPAMP2_CSR, OPAMP2 control/status register */
        ret = s->opamp2_csr;
        break;

    case 0x08 ... 0x0B:
        /* OPAMP3_CSR, OPAMP3 control/status register */
        ret = s->opamp3_csr;
        break;

    case 0x0C ... 0x0F:
        /* OPAMP4_CSR, OPAMP4 control/status register */
        ret = s->opamp4_csr;
        break;

    case 0x10 ... 0x13:
        /* OPAMP5_CSR, OPAMP5 control/status register */
        ret = s->opamp5_csr;
        break;

    case 0x14 ... 0x17:
        /* OPAMP6_CSR, OPAMP6 control/status register */
        ret = s->opamp6_csr;
        break;

    case 0x18 ... 0x1B:
        /* OPAMP1_TCMR, OPAMP1 control/status register */
        ret = s->opamp1_tcmr;
        break;

    case 0x1C ... 0x1F:
        /* OPAMP2_TCMR, OPAMP2 control/status register */
        ret = s->opamp2_tcmr;
        break;

    case 0x20 ... 0x23:
        /* OPAMP3_TCMR, OPAMP3 control/status register */
        ret = s->opamp3_tcmr;
        break;

    case 0x24 ... 0x27:
        /* OPAMP4_TCMR, OPAMP4 control/status register */
        ret = s->opamp4_tcmr;
        break;

    case 0x28 ... 0x2B:
        /* OPAMP5_TCMR, OPAMP5 control/status register */
        ret = s->opamp5_tcmr;
        break;

    case 0x2C ... 0x2F:
        /* OPAMP6_TCMR, OPAMP6 control/status register */
        ret = s->opamp6_tcmr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_opamp_mmio_write(void *opaque, hwaddr offset,
                                     uint64_t value, unsigned size)
{
    STM32G4OPAMPState *s = STM32G4_OPAMP(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* OPAMP1_CSR, OPAMP1 control/status register */
        s->opamp1_csr = value;
        break;

    case 0x04 ... 0x07:
        /* OPAMP2_CSR, OPAMP2 control/status register */
        s->opamp2_csr = value;
        break;

    case 0x08 ... 0x0B:
        /* OPAMP3_CSR, OPAMP3 control/status register */
        s->opamp3_csr = value;
        break;

    case 0x0C ... 0x0F:
        /* OPAMP4_CSR, OPAMP4 control/status register */
        s->opamp4_csr = value;
        break;

    case 0x10 ... 0x13:
        /* OPAMP5_CSR, OPAMP5 control/status register */
        s->opamp5_csr = value;
        break;

    case 0x14 ... 0x17:
        /* OPAMP6_CSR, OPAMP6 control/status register */
        s->opamp6_csr = value;
        break;

    case 0x18 ... 0x1B:
        /* OPAMP1_TCMR, OPAMP1 control/status register */
        s->opamp1_tcmr = value;
        break;

    case 0x1C ... 0x1F:
        /* OPAMP2_TCMR, OPAMP2 control/status register */
        s->opamp2_tcmr = value;
        break;

    case 0x20 ... 0x23:
        /* OPAMP3_TCMR, OPAMP3 control/status register */
        s->opamp3_tcmr = value;
        break;

    case 0x24 ... 0x27:
        /* OPAMP4_TCMR, OPAMP4 control/status register */
        s->opamp4_tcmr = value;
        break;

    case 0x28 ... 0x2B:
        /* OPAMP5_TCMR, OPAMP5 control/status register */
        s->opamp5_tcmr = value;
        break;

    case 0x2C ... 0x2F:
        /* OPAMP6_TCMR, OPAMP6 control/status register */
        s->opamp6_tcmr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_opamp_mmio_ops = {
    .read = stm32g4_opamp_mmio_read,
    .write = stm32g4_opamp_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_opamp_instance_init(Object *obj)
{
    STM32G4OPAMPState *s = STM32G4_OPAMP(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_opamp_mmio_ops, s,
                          STM32G4_OPAMP_MMIO, STM32G4_OPAMP_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_opamp_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4OPAMPState *s = STM32G4_OPAMP(dev);
}

static void stm32g4_opamp_reset(DeviceState *dev)
{
    STM32G4OPAMPState *s = STM32G4_OPAMP(dev);

    s->opamp1_csr = 0x00000000;
    s->opamp2_csr = 0x00000000;
    s->opamp3_csr = 0x00000000;
    s->opamp4_csr = 0x00000000;
    s->opamp5_csr = 0x00000000;
    s->opamp6_csr = 0x00000000;
    s->opamp1_tcmr = 0x00000000;
    s->opamp2_tcmr = 0x00000000;
    s->opamp3_tcmr = 0x00000000;
    s->opamp4_tcmr = 0x00000000;
    s->opamp5_tcmr = 0x00000000;
    s->opamp6_tcmr = 0x00000000;
}

static void stm32g4_opamp_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4OPAMPState *s = STM32G4_OPAMP(dev);
}

static Property stm32g4_opamp_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_opamp = {
    .name = "stm32g4_opamp",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(opamp1_csr, STM32G4OPAMPState),
        VMSTATE_UINT32(opamp2_csr, STM32G4OPAMPState),
        VMSTATE_UINT32(opamp3_csr, STM32G4OPAMPState),
        VMSTATE_UINT32(opamp4_csr, STM32G4OPAMPState),
        VMSTATE_UINT32(opamp5_csr, STM32G4OPAMPState),
        VMSTATE_UINT32(opamp6_csr, STM32G4OPAMPState),
        VMSTATE_UINT32(opamp1_tcmr, STM32G4OPAMPState),
        VMSTATE_UINT32(opamp2_tcmr, STM32G4OPAMPState),
        VMSTATE_UINT32(opamp3_tcmr, STM32G4OPAMPState),
        VMSTATE_UINT32(opamp4_tcmr, STM32G4OPAMPState),
        VMSTATE_UINT32(opamp5_tcmr, STM32G4OPAMPState),
        VMSTATE_UINT32(opamp6_tcmr, STM32G4OPAMPState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_opamp_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_opamp_realize;
    dc->reset     = stm32g4_opamp_reset;
    dc->unrealize = stm32g4_opamp_unrealize;
    dc->vmsd      = &vmstate_stm32g4_opamp;
    device_class_set_props(dc, stm32g4_opamp_properties);
}

static TypeInfo stm32g4_opamp_info = {
    .name          = TYPE_STM32G4_OPAMP,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4OPAMPState),
    .instance_init = stm32g4_opamp_instance_init,
    .class_init    = stm32g4_opamp_class_init
};

static void stm32g4_opamp_register_types(void)
{
    type_register_static(&stm32g4_opamp_info);
}

type_init(stm32g4_opamp_register_types)
