/* stm32g4_fpu_cpacr.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_fpu_cpacr.h"
#include "migration/vmstate.h"

#define STM32G4_FPU_CPACR_MMIO TYPE_STM32G4_FPU_CPACR "_mmio"
#define STM32G4_FPU_CPACR_MMIO_SIZE 0x4

static uint64_t stm32g4_fpu_cpacr_mmio_read(void *opaque, hwaddr offset,
                                            unsigned size)
{
    STM32G4FPUCPACRState *s = STM32G4_FPU_CPACR(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x0 ... 0x3:
        /* CPACR, Coprocessor access control register */
        ret = s->cpacr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_fpu_cpacr_mmio_write(void *opaque, hwaddr offset,
                                         uint64_t value, unsigned size)
{
    STM32G4FPUCPACRState *s = STM32G4_FPU_CPACR(opaque);

    switch (offset) {
    case 0x0 ... 0x3:
        /* CPACR, Coprocessor access control register */
        s->cpacr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_fpu_cpacr_mmio_ops = {
    .read = stm32g4_fpu_cpacr_mmio_read,
    .write = stm32g4_fpu_cpacr_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_fpu_cpacr_instance_init(Object *obj)
{
    STM32G4FPUCPACRState *s = STM32G4_FPU_CPACR(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_fpu_cpacr_mmio_ops, s,
                          STM32G4_FPU_CPACR_MMIO, STM32G4_FPU_CPACR_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_fpu_cpacr_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4FPUCPACRState *s = STM32G4_FPU_CPACR(dev);
}

static void stm32g4_fpu_cpacr_reset(DeviceState *dev)
{
    STM32G4FPUCPACRState *s = STM32G4_FPU_CPACR(dev);

    s->cpacr = 0x0000000;
}

static void stm32g4_fpu_cpacr_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4FPUCPACRState *s = STM32G4_FPU_CPACR(dev);
}

static Property stm32g4_fpu_cpacr_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_fpu_cpacr = {
    .name = "stm32g4_fpu_cpacr",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cpacr, STM32G4FPUCPACRState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_fpu_cpacr_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_fpu_cpacr_realize;
    dc->reset     = stm32g4_fpu_cpacr_reset;
    dc->unrealize = stm32g4_fpu_cpacr_unrealize;
    dc->vmsd      = &vmstate_stm32g4_fpu_cpacr;
    device_class_set_props(dc, stm32g4_fpu_cpacr_properties);
}

static TypeInfo stm32g4_fpu_cpacr_info = {
    .name          = TYPE_STM32G4_FPU_CPACR,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4FPUCPACRState),
    .instance_init = stm32g4_fpu_cpacr_instance_init,
    .class_init    = stm32g4_fpu_cpacr_class_init
};

static void stm32g4_fpu_cpacr_register_types(void)
{
    type_register_static(&stm32g4_fpu_cpacr_info);
}

type_init(stm32g4_fpu_cpacr_register_types)