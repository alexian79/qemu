/* stm32g4_dbgmcu.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_dbgmcu.h"
#include "migration/vmstate.h"

#define STM32G4_DBGMCU_MMIO TYPE_STM32G4_DBGMCU "_mmio"
#define STM32G4_DBGMCU_MMIO_SIZE 0x14

static uint64_t stm32g4_dbgmcu_mmio_read(void *opaque, hwaddr offset,
                                         unsigned size)
{
    STM32G4DBGMCUState *s = STM32G4_DBGMCU(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* IDCODE, MCU Device ID Code Register */
        ret = s->idcode;
        break;

    case 0x04 ... 0x07:
        /* CR, Debug MCU Configuration Register */
        ret = s->cr;
        break;

    case 0x08 ... 0x0B:
        /* APB1L_FZ, APB Low Freeze Register 1 */
        ret = s->apb1l_fz;
        break;

    case 0x0C ... 0x0F:
        /* APB1H_FZ, APB Low Freeze Register 2 */
        ret = s->apb1h_fz;
        break;

    case 0x10 ... 0x13:
        /* APB2_FZ, APB High Freeze Register */
        ret = s->apb2_fz;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_dbgmcu_mmio_write(void *opaque, hwaddr offset,
                                      uint64_t value, unsigned size)
{
    STM32G4DBGMCUState *s = STM32G4_DBGMCU(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* IDCODE, MCU Device ID Code Register */
        s->idcode = value;
        break;

    case 0x04 ... 0x07:
        /* CR, Debug MCU Configuration Register */
        s->cr = value;
        break;

    case 0x08 ... 0x0B:
        /* APB1L_FZ, APB Low Freeze Register 1 */
        s->apb1l_fz = value;
        break;

    case 0x0C ... 0x0F:
        /* APB1H_FZ, APB Low Freeze Register 2 */
        s->apb1h_fz = value;
        break;

    case 0x10 ... 0x13:
        /* APB2_FZ, APB High Freeze Register */
        s->apb2_fz = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_dbgmcu_mmio_ops = {
    .read = stm32g4_dbgmcu_mmio_read,
    .write = stm32g4_dbgmcu_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_dbgmcu_instance_init(Object *obj)
{
    STM32G4DBGMCUState *s = STM32G4_DBGMCU(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_dbgmcu_mmio_ops, s,
                          STM32G4_DBGMCU_MMIO, STM32G4_DBGMCU_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_dbgmcu_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4DBGMCUState *s = STM32G4_DBGMCU(dev);
}

static void stm32g4_dbgmcu_reset(DeviceState *dev)
{
    STM32G4DBGMCUState *s = STM32G4_DBGMCU(dev);

    s->idcode = 0x0;
    s->cr = 0x0;
    s->apb1l_fz = 0x0;
    s->apb1h_fz = 0x0;
    s->apb2_fz = 0x0;
}

static void stm32g4_dbgmcu_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4DBGMCUState *s = STM32G4_DBGMCU(dev);
}

static Property stm32g4_dbgmcu_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_dbgmcu = {
    .name = "stm32g4_dbgmcu",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(idcode, STM32G4DBGMCUState),
        VMSTATE_UINT32(cr, STM32G4DBGMCUState),
        VMSTATE_UINT32(apb1l_fz, STM32G4DBGMCUState),
        VMSTATE_UINT32(apb1h_fz, STM32G4DBGMCUState),
        VMSTATE_UINT32(apb2_fz, STM32G4DBGMCUState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_dbgmcu_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_dbgmcu_realize;
    dc->reset     = stm32g4_dbgmcu_reset;
    dc->unrealize = stm32g4_dbgmcu_unrealize;
    dc->vmsd      = &vmstate_stm32g4_dbgmcu;
    device_class_set_props(dc, stm32g4_dbgmcu_properties);
}

static TypeInfo stm32g4_dbgmcu_info = {
    .name          = TYPE_STM32G4_DBGMCU,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4DBGMCUState),
    .instance_init = stm32g4_dbgmcu_instance_init,
    .class_init    = stm32g4_dbgmcu_class_init
};

static void stm32g4_dbgmcu_register_types(void)
{
    type_register_static(&stm32g4_dbgmcu_info);
}

type_init(stm32g4_dbgmcu_register_types)
