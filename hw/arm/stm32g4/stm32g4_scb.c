/* stm32g4_scb.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_scb.h"
#include "migration/vmstate.h"

#define STM32G4_SCB_MMIO TYPE_STM32G4_SCB "_mmio"
#define STM32G4_SCB_MMIO_SIZE 0x40

static uint64_t stm32g4_scb_mmio_read(void *opaque, hwaddr offset,
                                      unsigned size)
{
    STM32G4SCBState *s = STM32G4_SCB(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* CPUID, CPUID base register */
        ret = s->cpuid;
        break;

    case 0x04 ... 0x07:
        /* ICSR, Interrupt control and state register */
        ret = s->icsr;
        break;

    case 0x08 ... 0x0B:
        /* VTOR, Vector table offset register */
        ret = s->vtor;
        break;

    case 0x0C ... 0x0F:
        /* AIRCR, Application interrupt and reset control register */
        ret = s->aircr;
        break;

    case 0x10 ... 0x13:
        /* SCR, System control register */
        ret = s->scr;
        break;

    case 0x14 ... 0x17:
        /* CCR, Configuration and control register */
        ret = s->ccr;
        break;

    case 0x18 ... 0x1B:
        /* SHPR1, System handler priority registers */
        ret = s->shpr1;
        break;

    case 0x1C ... 0x1F:
        /* SHPR2, System handler priority registers */
        ret = s->shpr2;
        break;

    case 0x20 ... 0x23:
        /* SHPR3, System handler priority registers */
        ret = s->shpr3;
        break;

    case 0x24 ... 0x27:
        /* SHCSR, System handler control and state register */
        ret = s->shcsr;
        break;

    case 0x28 ... 0x2B:
        /* CFSR_UFSR_BFSR_MMFSR, Configurable fault status register */
        ret = s->cfsr_ufsr_bfsr_mmfsr;
        break;

    case 0x2C ... 0x2F:
        /* HFSR, Hard fault status register */
        ret = s->hfsr;
        break;

    case 0x34 ... 0x37:
        /* MMFAR, Memory management fault address register */
        ret = s->mmfar;
        break;

    case 0x38 ... 0x3B:
        /* BFAR, Bus fault address register */
        ret = s->bfar;
        break;

    case 0x3C ... 0x3F:
        /* AFSR, Auxiliary fault status register */
        ret = s->afsr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_scb_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                   unsigned size)
{
    STM32G4SCBState *s = STM32G4_SCB(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* CPUID, CPUID base register */
        s->cpuid = value;
        break;

    case 0x04 ... 0x07:
        /* ICSR, Interrupt control and state register */
        s->icsr = value;
        break;

    case 0x08 ... 0x0B:
        /* VTOR, Vector table offset register */
        s->vtor = value;
        break;

    case 0x0C ... 0x0F:
        /* AIRCR, Application interrupt and reset control register */
        s->aircr = value;
        break;

    case 0x10 ... 0x13:
        /* SCR, System control register */
        s->scr = value;
        break;

    case 0x14 ... 0x17:
        /* CCR, Configuration and control register */
        s->ccr = value;
        break;

    case 0x18 ... 0x1B:
        /* SHPR1, System handler priority registers */
        s->shpr1 = value;
        break;

    case 0x1C ... 0x1F:
        /* SHPR2, System handler priority registers */
        s->shpr2 = value;
        break;

    case 0x20 ... 0x23:
        /* SHPR3, System handler priority registers */
        s->shpr3 = value;
        break;

    case 0x24 ... 0x27:
        /* SHCSR, System handler control and state register */
        s->shcsr = value;
        break;

    case 0x28 ... 0x2B:
        /* CFSR_UFSR_BFSR_MMFSR, Configurable fault status register */
        s->cfsr_ufsr_bfsr_mmfsr = value;
        break;

    case 0x2C ... 0x2F:
        /* HFSR, Hard fault status register */
        s->hfsr = value;
        break;

    case 0x34 ... 0x37:
        /* MMFAR, Memory management fault address register */
        s->mmfar = value;
        break;

    case 0x38 ... 0x3B:
        /* BFAR, Bus fault address register */
        s->bfar = value;
        break;

    case 0x3C ... 0x3F:
        /* AFSR, Auxiliary fault status register */
        s->afsr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_scb_mmio_ops = {
    .read = stm32g4_scb_mmio_read,
    .write = stm32g4_scb_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_scb_instance_init(Object *obj)
{
    STM32G4SCBState *s = STM32G4_SCB(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_scb_mmio_ops, s,
                          STM32G4_SCB_MMIO, STM32G4_SCB_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_scb_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4SCBState *s = STM32G4_SCB(dev);
}

static void stm32g4_scb_reset(DeviceState *dev)
{
    STM32G4SCBState *s = STM32G4_SCB(dev);

    s->cpuid = 0x410FC241;
    s->icsr = 0x00000000;
    s->vtor = 0x00000000;
    s->aircr = 0x00000000;
    s->scr = 0x00000000;
    s->ccr = 0x00000000;
    s->shpr1 = 0x00000000;
    s->shpr2 = 0x00000000;
    s->shpr3 = 0x00000000;
    s->shcsr = 0x00000000;
    s->cfsr_ufsr_bfsr_mmfsr = 0x00000000;
    s->hfsr = 0x00000000;
    s->mmfar = 0x00000000;
    s->bfar = 0x00000000;
    s->afsr = 0x00000000;
}

static void stm32g4_scb_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4SCBState *s = STM32G4_SCB(dev);
}

static Property stm32g4_scb_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_scb = {
    .name = "stm32g4_scb",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cpuid, STM32G4SCBState),
        VMSTATE_UINT32(icsr, STM32G4SCBState),
        VMSTATE_UINT32(vtor, STM32G4SCBState),
        VMSTATE_UINT32(aircr, STM32G4SCBState),
        VMSTATE_UINT32(scr, STM32G4SCBState),
        VMSTATE_UINT32(ccr, STM32G4SCBState),
        VMSTATE_UINT32(shpr1, STM32G4SCBState),
        VMSTATE_UINT32(shpr2, STM32G4SCBState),
        VMSTATE_UINT32(shpr3, STM32G4SCBState),
        VMSTATE_UINT32(shcsr, STM32G4SCBState),
        VMSTATE_UINT32(cfsr_ufsr_bfsr_mmfsr, STM32G4SCBState),
        VMSTATE_UINT32(hfsr, STM32G4SCBState),
        VMSTATE_UINT32(mmfar, STM32G4SCBState),
        VMSTATE_UINT32(bfar, STM32G4SCBState),
        VMSTATE_UINT32(afsr, STM32G4SCBState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_scb_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_scb_realize;
    dc->reset     = stm32g4_scb_reset;
    dc->unrealize = stm32g4_scb_unrealize;
    dc->vmsd      = &vmstate_stm32g4_scb;
    device_class_set_props(dc, stm32g4_scb_properties);
}

static TypeInfo stm32g4_scb_info = {
    .name          = TYPE_STM32G4_SCB,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4SCBState),
    .instance_init = stm32g4_scb_instance_init,
    .class_init    = stm32g4_scb_class_init
};

static void stm32g4_scb_register_types(void)
{
    type_register_static(&stm32g4_scb_info);
}

type_init(stm32g4_scb_register_types)
