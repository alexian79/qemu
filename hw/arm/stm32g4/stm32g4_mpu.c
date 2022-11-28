/* stm32g4_mpu.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_mpu.h"
#include "migration/vmstate.h"

#define STM32G4_MPU_MMIO TYPE_STM32G4_MPU "_mmio"
#define STM32G4_MPU_MMIO_SIZE 0x14

static uint64_t stm32g4_mpu_mmio_read(void *opaque, hwaddr offset,
                                      unsigned size)
{
    STM32G4MPUState *s = STM32G4_MPU(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* TYPER, MPU type register */
        ret = s->typer;
        break;

    case 0x04 ... 0x07:
        /* CTRL, MPU control register */
        ret = s->ctrl;
        break;

    case 0x08 ... 0x0B:
        /* RNR, MPU region number register */
        ret = s->rnr;
        break;

    case 0x0C ... 0x0F:
        /* RBAR, MPU region base address register */
        ret = s->rbar;
        break;

    case 0x10 ... 0x13:
        /* RASR, MPU region attribute and size register */
        ret = s->rasr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_mpu_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                   unsigned size)
{
    STM32G4MPUState *s = STM32G4_MPU(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* TYPER, MPU type register */
        s->typer = value;
        break;

    case 0x04 ... 0x07:
        /* CTRL, MPU control register */
        s->ctrl = value;
        break;

    case 0x08 ... 0x0B:
        /* RNR, MPU region number register */
        s->rnr = value;
        break;

    case 0x0C ... 0x0F:
        /* RBAR, MPU region base address register */
        s->rbar = value;
        break;

    case 0x10 ... 0x13:
        /* RASR, MPU region attribute and size register */
        s->rasr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_mpu_mmio_ops = {
    .read = stm32g4_mpu_mmio_read,
    .write = stm32g4_mpu_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_mpu_instance_init(Object *obj)
{
    STM32G4MPUState *s = STM32G4_MPU(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_mpu_mmio_ops, s,
                          STM32G4_MPU_MMIO, STM32G4_MPU_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_mpu_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4MPUState *s = STM32G4_MPU(dev);
}

static void stm32g4_mpu_reset(DeviceState *dev)
{
    STM32G4MPUState *s = STM32G4_MPU(dev);

    s->typer = 0X00000800;
    s->ctrl = 0X00000000;
    s->rnr = 0X00000000;
    s->rbar = 0X00000000;
    s->rasr = 0X00000000;
}

static void stm32g4_mpu_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4MPUState *s = STM32G4_MPU(dev);
}

static Property stm32g4_mpu_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_mpu = {
    .name = "stm32g4_mpu",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(typer, STM32G4MPUState),
        VMSTATE_UINT32(ctrl, STM32G4MPUState),
        VMSTATE_UINT32(rnr, STM32G4MPUState),
        VMSTATE_UINT32(rbar, STM32G4MPUState),
        VMSTATE_UINT32(rasr, STM32G4MPUState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_mpu_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_mpu_realize;
    dc->reset     = stm32g4_mpu_reset;
    dc->unrealize = stm32g4_mpu_unrealize;
    dc->vmsd      = &vmstate_stm32g4_mpu;
    device_class_set_props(dc, stm32g4_mpu_properties);
}

static TypeInfo stm32g4_mpu_info = {
    .name          = TYPE_STM32G4_MPU,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4MPUState),
    .instance_init = stm32g4_mpu_instance_init,
    .class_init    = stm32g4_mpu_class_init
};

static void stm32g4_mpu_register_types(void)
{
    type_register_static(&stm32g4_mpu_info);
}

type_init(stm32g4_mpu_register_types)
