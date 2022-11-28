/* stm32g4_fpu.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_fpu.h"
#include "migration/vmstate.h"

#define STM32G4_FPU_MMIO TYPE_STM32G4_FPU "_mmio"
#define STM32G4_FPU_MMIO_SIZE 0xC

static uint64_t stm32g4_fpu_mmio_read(void *opaque, hwaddr offset,
                                      unsigned size)
{
    STM32G4FPUState *s = STM32G4_FPU(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x0 ... 0x3:
        /* FPCCR, Floating-point context control register */
        ret = s->fpccr;
        break;

    case 0x4 ... 0x7:
        /* FPCAR, Floating-point context address register */
        ret = s->fpcar;
        break;

    case 0x8 ... 0xB:
        /* FPSCR, Floating-point status control register */
        ret = s->fpscr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_fpu_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                   unsigned size)
{
    STM32G4FPUState *s = STM32G4_FPU(opaque);

    switch (offset) {
    case 0x0 ... 0x3:
        /* FPCCR, Floating-point context control register */
        s->fpccr = value;
        break;

    case 0x4 ... 0x7:
        /* FPCAR, Floating-point context address register */
        s->fpcar = value;
        break;

    case 0x8 ... 0xB:
        /* FPSCR, Floating-point status control register */
        s->fpscr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_fpu_mmio_ops = {
    .read = stm32g4_fpu_mmio_read,
    .write = stm32g4_fpu_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_fpu_instance_init(Object *obj)
{
    STM32G4FPUState *s = STM32G4_FPU(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_fpu_mmio_ops, s,
                          STM32G4_FPU_MMIO, STM32G4_FPU_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_fpu_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4FPUState *s = STM32G4_FPU(dev);
}

static void stm32g4_fpu_reset(DeviceState *dev)
{
    STM32G4FPUState *s = STM32G4_FPU(dev);

    s->fpccr = 0x00000000;
    s->fpcar = 0x00000000;
    s->fpscr = 0x00000000;
}

static void stm32g4_fpu_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4FPUState *s = STM32G4_FPU(dev);
}

static Property stm32g4_fpu_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_fpu = {
    .name = "stm32g4_fpu",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(fpccr, STM32G4FPUState),
        VMSTATE_UINT32(fpcar, STM32G4FPUState),
        VMSTATE_UINT32(fpscr, STM32G4FPUState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_fpu_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_fpu_realize;
    dc->reset     = stm32g4_fpu_reset;
    dc->unrealize = stm32g4_fpu_unrealize;
    dc->vmsd      = &vmstate_stm32g4_fpu;
    device_class_set_props(dc, stm32g4_fpu_properties);
}

static TypeInfo stm32g4_fpu_info = {
    .name          = TYPE_STM32G4_FPU,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4FPUState),
    .instance_init = stm32g4_fpu_instance_init,
    .class_init    = stm32g4_fpu_class_init
};

static void stm32g4_fpu_register_types(void)
{
    type_register_static(&stm32g4_fpu_info);
}

type_init(stm32g4_fpu_register_types)
