/* stm32g4_stk.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_stk.h"
#include "migration/vmstate.h"

#define STM32G4_STK_MMIO TYPE_STM32G4_STK "_mmio"
#define STM32G4_STK_MMIO_SIZE 0x10

static uint64_t stm32g4_stk_mmio_read(void *opaque, hwaddr offset,
                                      unsigned size)
{
    STM32G4STKState *s = STM32G4_STK(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* CTRL, SysTick control and status register */
        ret = s->ctrl;
        break;

    case 0x04 ... 0x07:
        /* LOAD, SysTick reload value register */
        ret = s->load;
        break;

    case 0x08 ... 0x0B:
        /* VAL, SysTick current value register */
        ret = s->val;
        break;

    case 0x0C ... 0x0F:
        /* CALIB, SysTick calibration value register */
        ret = s->calib;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_stk_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                   unsigned size)
{
    STM32G4STKState *s = STM32G4_STK(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* CTRL, SysTick control and status register */
        s->ctrl = value;
        break;

    case 0x04 ... 0x07:
        /* LOAD, SysTick reload value register */
        s->load = value;
        break;

    case 0x08 ... 0x0B:
        /* VAL, SysTick current value register */
        s->val = value;
        break;

    case 0x0C ... 0x0F:
        /* CALIB, SysTick calibration value register */
        s->calib = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_stk_mmio_ops = {
    .read = stm32g4_stk_mmio_read,
    .write = stm32g4_stk_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_stk_instance_init(Object *obj)
{
    STM32G4STKState *s = STM32G4_STK(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_stk_mmio_ops, s,
                          STM32G4_STK_MMIO, STM32G4_STK_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_stk_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4STKState *s = STM32G4_STK(dev);
}

static void stm32g4_stk_reset(DeviceState *dev)
{
    STM32G4STKState *s = STM32G4_STK(dev);

    s->ctrl = 0X00000000;
    s->load = 0X00000000;
    s->val = 0X00000000;
    s->calib = 0X00000000;
}

static void stm32g4_stk_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4STKState *s = STM32G4_STK(dev);
}

static Property stm32g4_stk_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_stk = {
    .name = "stm32g4_stk",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(ctrl, STM32G4STKState),
        VMSTATE_UINT32(load, STM32G4STKState),
        VMSTATE_UINT32(val, STM32G4STKState),
        VMSTATE_UINT32(calib, STM32G4STKState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_stk_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_stk_realize;
    dc->reset     = stm32g4_stk_reset;
    dc->unrealize = stm32g4_stk_unrealize;
    dc->vmsd      = &vmstate_stm32g4_stk;
    device_class_set_props(dc, stm32g4_stk_properties);
}

static TypeInfo stm32g4_stk_info = {
    .name          = TYPE_STM32G4_STK,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4STKState),
    .instance_init = stm32g4_stk_instance_init,
    .class_init    = stm32g4_stk_class_init
};

static void stm32g4_stk_register_types(void)
{
    type_register_static(&stm32g4_stk_info);
}

type_init(stm32g4_stk_register_types)
