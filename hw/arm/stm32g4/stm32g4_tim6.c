/* stm32g4_tim6.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_tim6.h"
#include "migration/vmstate.h"

#define STM32G4_TIM6_MMIO TYPE_STM32G4_TIM6 "_mmio"
#define STM32G4_TIM6_MMIO_SIZE 0x30

static uint64_t stm32g4_tim6_mmio_read(void *opaque, hwaddr offset,
                                       unsigned size)
{
    STM32G4TIM6State *s = STM32G4_TIM6(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* CR1, control register 1 */
        ret = s->cr1;
        break;

    case 0x04 ... 0x07:
        /* CR2, control register 2 */
        ret = s->cr2;
        break;

    case 0x0C ... 0x0F:
        /* DIER, DMA/Interrupt enable register */
        ret = s->dier;
        break;

    case 0x10 ... 0x13:
        /* SR, status register */
        ret = s->sr;
        break;

    case 0x14 ... 0x17:
        /* EGR, event generation register */
        ret = s->egr;
        break;

    case 0x24 ... 0x27:
        /* CNT, counter */
        ret = s->cnt;
        break;

    case 0x28 ... 0x2B:
        /* PSC, prescaler */
        ret = s->psc;
        break;

    case 0x2C ... 0x2F:
        /* ARR, auto-reload register */
        ret = s->arr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_tim6_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                    unsigned size)
{
    STM32G4TIM6State *s = STM32G4_TIM6(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* CR1, control register 1 */
        s->cr1 = value;
        break;

    case 0x04 ... 0x07:
        /* CR2, control register 2 */
        s->cr2 = value;
        break;

    case 0x0C ... 0x0F:
        /* DIER, DMA/Interrupt enable register */
        s->dier = value;
        break;

    case 0x10 ... 0x13:
        /* SR, status register */
        s->sr = value;
        break;

    case 0x14 ... 0x17:
        /* EGR, event generation register */
        s->egr = value;
        break;

    case 0x24 ... 0x27:
        /* CNT, counter */
        s->cnt = value;
        break;

    case 0x28 ... 0x2B:
        /* PSC, prescaler */
        s->psc = value;
        break;

    case 0x2C ... 0x2F:
        /* ARR, auto-reload register */
        s->arr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_tim6_mmio_ops = {
    .read = stm32g4_tim6_mmio_read,
    .write = stm32g4_tim6_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_tim6_instance_init(Object *obj)
{
    STM32G4TIM6State *s = STM32G4_TIM6(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_tim6_mmio_ops, s,
                          STM32G4_TIM6_MMIO, STM32G4_TIM6_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_tim6_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4TIM6State *s = STM32G4_TIM6(dev);
}

static void stm32g4_tim6_reset(DeviceState *dev)
{
    STM32G4TIM6State *s = STM32G4_TIM6(dev);

    s->cr1 = 0x00000000;
    s->cr2 = 0x00000000;
    s->dier = 0x00000000;
    s->sr = 0x00000000;
    s->egr = 0x00000000;
    s->cnt = 0x00000000;
    s->psc = 0x00000000;
    s->arr = 0x0000FFFF;
}

static void stm32g4_tim6_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4TIM6State *s = STM32G4_TIM6(dev);
}

static Property stm32g4_tim6_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_tim6 = {
    .name = "stm32g4_tim6",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cr1, STM32G4TIM6State),
        VMSTATE_UINT32(cr2, STM32G4TIM6State),
        VMSTATE_UINT32(dier, STM32G4TIM6State),
        VMSTATE_UINT32(sr, STM32G4TIM6State),
        VMSTATE_UINT32(egr, STM32G4TIM6State),
        VMSTATE_UINT32(cnt, STM32G4TIM6State),
        VMSTATE_UINT32(psc, STM32G4TIM6State),
        VMSTATE_UINT32(arr, STM32G4TIM6State),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_tim6_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_tim6_realize;
    dc->reset     = stm32g4_tim6_reset;
    dc->unrealize = stm32g4_tim6_unrealize;
    dc->vmsd      = &vmstate_stm32g4_tim6;
    device_class_set_props(dc, stm32g4_tim6_properties);
}

static TypeInfo stm32g4_tim6_info = {
    .name          = TYPE_STM32G4_TIM6,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4TIM6State),
    .instance_init = stm32g4_tim6_instance_init,
    .class_init    = stm32g4_tim6_class_init
};

static void stm32g4_tim6_register_types(void)
{
    type_register_static(&stm32g4_tim6_info);
}

type_init(stm32g4_tim6_register_types)
