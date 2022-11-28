/* stm32g4_nvic.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_nvic.h"
#include "migration/vmstate.h"

#define STM32G4_NVIC_MMIO TYPE_STM32G4_NVIC "_mmio"
#define STM32G4_NVIC_MMIO_SIZE 0x368

static uint64_t stm32g4_nvic_mmio_read(void *opaque, hwaddr offset,
                                       unsigned size)
{
    STM32G4NVICState *s = STM32G4_NVIC(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x000 ... 0x003:
        /* ISER0, Interrupt Set-Enable Register */
        ret = s->iser0;
        break;

    case 0x004 ... 0x007:
        /* ISER1, Interrupt Set-Enable Register */
        ret = s->iser1;
        break;

    case 0x008 ... 0x00B:
        /* ISER2, Interrupt Set-Enable Register */
        ret = s->iser2;
        break;

    case 0x00C ... 0x00F:
        /* ISER3, Interrupt Set-Enable Register */
        ret = s->iser3;
        break;

    case 0x080 ... 0x083:
        /* ICER0, Interrupt Clear-Enable Register */
        ret = s->icer0;
        break;

    case 0x084 ... 0x087:
        /* ICER1, Interrupt Clear-Enable Register */
        ret = s->icer1;
        break;

    case 0x088 ... 0x08B:
        /* ICER2, Interrupt Clear-Enable Register */
        ret = s->icer2;
        break;

    case 0x08C ... 0x08F:
        /* ICER3, Interrupt Clear-Enable Register */
        ret = s->icer3;
        break;

    case 0x100 ... 0x103:
        /* ISPR0, Interrupt Set-Pending Register */
        ret = s->ispr0;
        break;

    case 0x104 ... 0x107:
        /* ISPR1, Interrupt Set-Pending Register */
        ret = s->ispr1;
        break;

    case 0x108 ... 0x10B:
        /* ISPR2, Interrupt Set-Pending Register */
        ret = s->ispr2;
        break;

    case 0x10C ... 0x10F:
        /* ISPR3, Interrupt Set-Pending Register */
        ret = s->ispr3;
        break;

    case 0x180 ... 0x183:
        /* ICPR0, Interrupt Clear-Pending Register */
        ret = s->icpr0;
        break;

    case 0x184 ... 0x187:
        /* ICPR1, Interrupt Clear-Pending Register */
        ret = s->icpr1;
        break;

    case 0x188 ... 0x18B:
        /* ICPR2, Interrupt Clear-Pending Register */
        ret = s->icpr2;
        break;

    case 0x18C ... 0x18F:
        /* ICPR3, Interrupt Clear-Pending Register */
        ret = s->icpr3;
        break;

    case 0x200 ... 0x203:
        /* IABR0, Interrupt Active Bit Register */
        ret = s->iabr0;
        break;

    case 0x204 ... 0x207:
        /* IABR1, Interrupt Active Bit Register */
        ret = s->iabr1;
        break;

    case 0x208 ... 0x20B:
        /* IABR2, Interrupt Active Bit Register */
        ret = s->iabr2;
        break;

    case 0x20C ... 0x20F:
        /* IABR3, Interrupt Active Bit Register */
        ret = s->iabr3;
        break;

    case 0x300 ... 0x303:
        /* IPR0, Interrupt Priority Register */
        ret = s->ipr0;
        break;

    case 0x304 ... 0x307:
        /* IPR1, Interrupt Priority Register */
        ret = s->ipr1;
        break;

    case 0x308 ... 0x30B:
        /* IPR2, Interrupt Priority Register */
        ret = s->ipr2;
        break;

    case 0x30C ... 0x30F:
        /* IPR3, Interrupt Priority Register */
        ret = s->ipr3;
        break;

    case 0x310 ... 0x313:
        /* IPR4, Interrupt Priority Register */
        ret = s->ipr4;
        break;

    case 0x314 ... 0x317:
        /* IPR5, Interrupt Priority Register */
        ret = s->ipr5;
        break;

    case 0x318 ... 0x31B:
        /* IPR6, Interrupt Priority Register */
        ret = s->ipr6;
        break;

    case 0x31C ... 0x31F:
        /* IPR7, Interrupt Priority Register */
        ret = s->ipr7;
        break;

    case 0x320 ... 0x323:
        /* IPR8, Interrupt Priority Register */
        ret = s->ipr8;
        break;

    case 0x324 ... 0x327:
        /* IPR9, Interrupt Priority Register */
        ret = s->ipr9;
        break;

    case 0x328 ... 0x32B:
        /* IPR10, Interrupt Priority Register */
        ret = s->ipr10;
        break;

    case 0x32C ... 0x32F:
        /* IPR11, Interrupt Priority Register */
        ret = s->ipr11;
        break;

    case 0x330 ... 0x333:
        /* IPR12, Interrupt Priority Register */
        ret = s->ipr12;
        break;

    case 0x334 ... 0x337:
        /* IPR13, Interrupt Priority Register */
        ret = s->ipr13;
        break;

    case 0x338 ... 0x33B:
        /* IPR14, Interrupt Priority Register */
        ret = s->ipr14;
        break;

    case 0x33C ... 0x33F:
        /* IPR15, Interrupt Priority Register */
        ret = s->ipr15;
        break;

    case 0x340 ... 0x343:
        /* IPR16, Interrupt Priority Register */
        ret = s->ipr16;
        break;

    case 0x344 ... 0x347:
        /* IPR17, Interrupt Priority Register */
        ret = s->ipr17;
        break;

    case 0x348 ... 0x34B:
        /* IPR18, Interrupt Priority Register */
        ret = s->ipr18;
        break;

    case 0x34C ... 0x34F:
        /* IPR19, Interrupt Priority Register */
        ret = s->ipr19;
        break;

    case 0x350 ... 0x353:
        /* IPR20, Interrupt Priority Register */
        ret = s->ipr20;
        break;

    case 0x354 ... 0x357:
        /* IPR21, Interrupt Priority Register */
        ret = s->ipr21;
        break;

    case 0x358 ... 0x35B:
        /* IPR22, Interrupt Priority Register */
        ret = s->ipr22;
        break;

    case 0x35C ... 0x35F:
        /* IPR23, Interrupt Priority Register */
        ret = s->ipr23;
        break;

    case 0x360 ... 0x363:
        /* IPR24, Interrupt Priority Register */
        ret = s->ipr24;
        break;

    case 0x364 ... 0x367:
        /* IPR25, Interrupt Priority Register */
        ret = s->ipr25;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_nvic_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                    unsigned size)
{
    STM32G4NVICState *s = STM32G4_NVIC(opaque);

    switch (offset) {
    case 0x000 ... 0x003:
        /* ISER0, Interrupt Set-Enable Register */
        s->iser0 = value;
        break;

    case 0x004 ... 0x007:
        /* ISER1, Interrupt Set-Enable Register */
        s->iser1 = value;
        break;

    case 0x008 ... 0x00B:
        /* ISER2, Interrupt Set-Enable Register */
        s->iser2 = value;
        break;

    case 0x00C ... 0x00F:
        /* ISER3, Interrupt Set-Enable Register */
        s->iser3 = value;
        break;

    case 0x080 ... 0x083:
        /* ICER0, Interrupt Clear-Enable Register */
        s->icer0 = value;
        break;

    case 0x084 ... 0x087:
        /* ICER1, Interrupt Clear-Enable Register */
        s->icer1 = value;
        break;

    case 0x088 ... 0x08B:
        /* ICER2, Interrupt Clear-Enable Register */
        s->icer2 = value;
        break;

    case 0x08C ... 0x08F:
        /* ICER3, Interrupt Clear-Enable Register */
        s->icer3 = value;
        break;

    case 0x100 ... 0x103:
        /* ISPR0, Interrupt Set-Pending Register */
        s->ispr0 = value;
        break;

    case 0x104 ... 0x107:
        /* ISPR1, Interrupt Set-Pending Register */
        s->ispr1 = value;
        break;

    case 0x108 ... 0x10B:
        /* ISPR2, Interrupt Set-Pending Register */
        s->ispr2 = value;
        break;

    case 0x10C ... 0x10F:
        /* ISPR3, Interrupt Set-Pending Register */
        s->ispr3 = value;
        break;

    case 0x180 ... 0x183:
        /* ICPR0, Interrupt Clear-Pending Register */
        s->icpr0 = value;
        break;

    case 0x184 ... 0x187:
        /* ICPR1, Interrupt Clear-Pending Register */
        s->icpr1 = value;
        break;

    case 0x188 ... 0x18B:
        /* ICPR2, Interrupt Clear-Pending Register */
        s->icpr2 = value;
        break;

    case 0x18C ... 0x18F:
        /* ICPR3, Interrupt Clear-Pending Register */
        s->icpr3 = value;
        break;

    case 0x200 ... 0x203:
        /* IABR0, Interrupt Active Bit Register */
        s->iabr0 = value;
        break;

    case 0x204 ... 0x207:
        /* IABR1, Interrupt Active Bit Register */
        s->iabr1 = value;
        break;

    case 0x208 ... 0x20B:
        /* IABR2, Interrupt Active Bit Register */
        s->iabr2 = value;
        break;

    case 0x20C ... 0x20F:
        /* IABR3, Interrupt Active Bit Register */
        s->iabr3 = value;
        break;

    case 0x300 ... 0x303:
        /* IPR0, Interrupt Priority Register */
        s->ipr0 = value;
        break;

    case 0x304 ... 0x307:
        /* IPR1, Interrupt Priority Register */
        s->ipr1 = value;
        break;

    case 0x308 ... 0x30B:
        /* IPR2, Interrupt Priority Register */
        s->ipr2 = value;
        break;

    case 0x30C ... 0x30F:
        /* IPR3, Interrupt Priority Register */
        s->ipr3 = value;
        break;

    case 0x310 ... 0x313:
        /* IPR4, Interrupt Priority Register */
        s->ipr4 = value;
        break;

    case 0x314 ... 0x317:
        /* IPR5, Interrupt Priority Register */
        s->ipr5 = value;
        break;

    case 0x318 ... 0x31B:
        /* IPR6, Interrupt Priority Register */
        s->ipr6 = value;
        break;

    case 0x31C ... 0x31F:
        /* IPR7, Interrupt Priority Register */
        s->ipr7 = value;
        break;

    case 0x320 ... 0x323:
        /* IPR8, Interrupt Priority Register */
        s->ipr8 = value;
        break;

    case 0x324 ... 0x327:
        /* IPR9, Interrupt Priority Register */
        s->ipr9 = value;
        break;

    case 0x328 ... 0x32B:
        /* IPR10, Interrupt Priority Register */
        s->ipr10 = value;
        break;

    case 0x32C ... 0x32F:
        /* IPR11, Interrupt Priority Register */
        s->ipr11 = value;
        break;

    case 0x330 ... 0x333:
        /* IPR12, Interrupt Priority Register */
        s->ipr12 = value;
        break;

    case 0x334 ... 0x337:
        /* IPR13, Interrupt Priority Register */
        s->ipr13 = value;
        break;

    case 0x338 ... 0x33B:
        /* IPR14, Interrupt Priority Register */
        s->ipr14 = value;
        break;

    case 0x33C ... 0x33F:
        /* IPR15, Interrupt Priority Register */
        s->ipr15 = value;
        break;

    case 0x340 ... 0x343:
        /* IPR16, Interrupt Priority Register */
        s->ipr16 = value;
        break;

    case 0x344 ... 0x347:
        /* IPR17, Interrupt Priority Register */
        s->ipr17 = value;
        break;

    case 0x348 ... 0x34B:
        /* IPR18, Interrupt Priority Register */
        s->ipr18 = value;
        break;

    case 0x34C ... 0x34F:
        /* IPR19, Interrupt Priority Register */
        s->ipr19 = value;
        break;

    case 0x350 ... 0x353:
        /* IPR20, Interrupt Priority Register */
        s->ipr20 = value;
        break;

    case 0x354 ... 0x357:
        /* IPR21, Interrupt Priority Register */
        s->ipr21 = value;
        break;

    case 0x358 ... 0x35B:
        /* IPR22, Interrupt Priority Register */
        s->ipr22 = value;
        break;

    case 0x35C ... 0x35F:
        /* IPR23, Interrupt Priority Register */
        s->ipr23 = value;
        break;

    case 0x360 ... 0x363:
        /* IPR24, Interrupt Priority Register */
        s->ipr24 = value;
        break;

    case 0x364 ... 0x367:
        /* IPR25, Interrupt Priority Register */
        s->ipr25 = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_nvic_mmio_ops = {
    .read = stm32g4_nvic_mmio_read,
    .write = stm32g4_nvic_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_nvic_instance_init(Object *obj)
{
    STM32G4NVICState *s = STM32G4_NVIC(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_nvic_mmio_ops, s,
                          STM32G4_NVIC_MMIO, STM32G4_NVIC_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_nvic_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4NVICState *s = STM32G4_NVIC(dev);
}

static void stm32g4_nvic_reset(DeviceState *dev)
{
    STM32G4NVICState *s = STM32G4_NVIC(dev);

    s->iser0 = 0x00000000;
    s->iser1 = 0x00000000;
    s->iser2 = 0x00000000;
    s->iser3 = 0x00000000;
    s->icer0 = 0x00000000;
    s->icer1 = 0x00000000;
    s->icer2 = 0x00000000;
    s->icer3 = 0x00000000;
    s->ispr0 = 0x00000000;
    s->ispr1 = 0x00000000;
    s->ispr2 = 0x00000000;
    s->ispr3 = 0x00000000;
    s->icpr0 = 0x00000000;
    s->icpr1 = 0x00000000;
    s->icpr2 = 0x00000000;
    s->icpr3 = 0x00000000;
    s->iabr0 = 0x00000000;
    s->iabr1 = 0x00000000;
    s->iabr2 = 0x00000000;
    s->iabr3 = 0x00000000;
    s->ipr0 = 0x00000000;
    s->ipr1 = 0x00000000;
    s->ipr2 = 0x00000000;
    s->ipr3 = 0x00000000;
    s->ipr4 = 0x00000000;
    s->ipr5 = 0x00000000;
    s->ipr6 = 0x00000000;
    s->ipr7 = 0x00000000;
    s->ipr8 = 0x00000000;
    s->ipr9 = 0x00000000;
    s->ipr10 = 0x00000000;
    s->ipr11 = 0x00000000;
    s->ipr12 = 0x00000000;
    s->ipr13 = 0x00000000;
    s->ipr14 = 0x00000000;
    s->ipr15 = 0x00000000;
    s->ipr16 = 0x00000000;
    s->ipr17 = 0x00000000;
    s->ipr18 = 0x00000000;
    s->ipr19 = 0x00000000;
    s->ipr20 = 0x00000000;
    s->ipr21 = 0x00000000;
    s->ipr22 = 0x00000000;
    s->ipr23 = 0x00000000;
    s->ipr24 = 0x00000000;
    s->ipr25 = 0x00000000;
}

static void stm32g4_nvic_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4NVICState *s = STM32G4_NVIC(dev);
}

static Property stm32g4_nvic_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_nvic = {
    .name = "stm32g4_nvic",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(iser0, STM32G4NVICState),
        VMSTATE_UINT32(iser1, STM32G4NVICState),
        VMSTATE_UINT32(iser2, STM32G4NVICState),
        VMSTATE_UINT32(iser3, STM32G4NVICState),
        VMSTATE_UINT32(icer0, STM32G4NVICState),
        VMSTATE_UINT32(icer1, STM32G4NVICState),
        VMSTATE_UINT32(icer2, STM32G4NVICState),
        VMSTATE_UINT32(icer3, STM32G4NVICState),
        VMSTATE_UINT32(ispr0, STM32G4NVICState),
        VMSTATE_UINT32(ispr1, STM32G4NVICState),
        VMSTATE_UINT32(ispr2, STM32G4NVICState),
        VMSTATE_UINT32(ispr3, STM32G4NVICState),
        VMSTATE_UINT32(icpr0, STM32G4NVICState),
        VMSTATE_UINT32(icpr1, STM32G4NVICState),
        VMSTATE_UINT32(icpr2, STM32G4NVICState),
        VMSTATE_UINT32(icpr3, STM32G4NVICState),
        VMSTATE_UINT32(iabr0, STM32G4NVICState),
        VMSTATE_UINT32(iabr1, STM32G4NVICState),
        VMSTATE_UINT32(iabr2, STM32G4NVICState),
        VMSTATE_UINT32(iabr3, STM32G4NVICState),
        VMSTATE_UINT32(ipr0, STM32G4NVICState),
        VMSTATE_UINT32(ipr1, STM32G4NVICState),
        VMSTATE_UINT32(ipr2, STM32G4NVICState),
        VMSTATE_UINT32(ipr3, STM32G4NVICState),
        VMSTATE_UINT32(ipr4, STM32G4NVICState),
        VMSTATE_UINT32(ipr5, STM32G4NVICState),
        VMSTATE_UINT32(ipr6, STM32G4NVICState),
        VMSTATE_UINT32(ipr7, STM32G4NVICState),
        VMSTATE_UINT32(ipr8, STM32G4NVICState),
        VMSTATE_UINT32(ipr9, STM32G4NVICState),
        VMSTATE_UINT32(ipr10, STM32G4NVICState),
        VMSTATE_UINT32(ipr11, STM32G4NVICState),
        VMSTATE_UINT32(ipr12, STM32G4NVICState),
        VMSTATE_UINT32(ipr13, STM32G4NVICState),
        VMSTATE_UINT32(ipr14, STM32G4NVICState),
        VMSTATE_UINT32(ipr15, STM32G4NVICState),
        VMSTATE_UINT32(ipr16, STM32G4NVICState),
        VMSTATE_UINT32(ipr17, STM32G4NVICState),
        VMSTATE_UINT32(ipr18, STM32G4NVICState),
        VMSTATE_UINT32(ipr19, STM32G4NVICState),
        VMSTATE_UINT32(ipr20, STM32G4NVICState),
        VMSTATE_UINT32(ipr21, STM32G4NVICState),
        VMSTATE_UINT32(ipr22, STM32G4NVICState),
        VMSTATE_UINT32(ipr23, STM32G4NVICState),
        VMSTATE_UINT32(ipr24, STM32G4NVICState),
        VMSTATE_UINT32(ipr25, STM32G4NVICState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_nvic_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_nvic_realize;
    dc->reset     = stm32g4_nvic_reset;
    dc->unrealize = stm32g4_nvic_unrealize;
    dc->vmsd      = &vmstate_stm32g4_nvic;
    device_class_set_props(dc, stm32g4_nvic_properties);
}

static TypeInfo stm32g4_nvic_info = {
    .name          = TYPE_STM32G4_NVIC,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4NVICState),
    .instance_init = stm32g4_nvic_instance_init,
    .class_init    = stm32g4_nvic_class_init
};

static void stm32g4_nvic_register_types(void)
{
    type_register_static(&stm32g4_nvic_info);
}

type_init(stm32g4_nvic_register_types)
