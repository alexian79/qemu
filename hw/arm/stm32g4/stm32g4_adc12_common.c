/* stm32g4_adc12_common.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_adc12_common.h"
#include "migration/vmstate.h"

#define STM32G4_ADC12_COMMON_MMIO TYPE_STM32G4_ADC12_COMMON "_mmio"
#define STM32G4_ADC12_COMMON_MMIO_SIZE 0x10

static uint64_t stm32g4_adc12_common_mmio_read(void *opaque, hwaddr offset,
                                               unsigned size)
{
    STM32G4ADC12CommonState *s = STM32G4_ADC12_COMMON(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* CSR, ADC Common status register */
        ret = s->csr;
        break;

    case 0x08 ... 0x0B:
        /* CCR, ADC common control register */
        ret = s->ccr;
        break;

    case 0x0C ... 0x0F:
        /* CDR, ADC common regular data register for dual and triple modes */
        ret = s->cdr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_adc12_common_mmio_write(void *opaque, hwaddr offset,
                                            uint64_t value, unsigned size)
{
    STM32G4ADC12CommonState *s = STM32G4_ADC12_COMMON(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* CSR, ADC Common status register */
        s->csr = value;
        break;

    case 0x08 ... 0x0B:
        /* CCR, ADC common control register */
        s->ccr = value;
        break;

    case 0x0C ... 0x0F:
        /* CDR, ADC common regular data register for dual and triple modes */
        s->cdr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_adc12_common_mmio_ops = {
    .read = stm32g4_adc12_common_mmio_read,
    .write = stm32g4_adc12_common_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_adc12_common_instance_init(Object *obj)
{
    STM32G4ADC12CommonState *s = STM32G4_ADC12_COMMON(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_adc12_common_mmio_ops, s,
                          STM32G4_ADC12_COMMON_MMIO,
                          STM32G4_ADC12_COMMON_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_adc12_common_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4ADC12CommonState *s =
        STM32G4_ADC12_COMMON(dev);
}

static void stm32g4_adc12_common_reset(DeviceState *dev)
{
    STM32G4ADC12CommonState *s = STM32G4_ADC12_COMMON(dev);

    s->csr = 0x00000000;
    s->ccr = 0x00000000;
    s->cdr = 0x00000000;
}

static void stm32g4_adc12_common_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4ADC12CommonState *s =
        STM32G4_ADC12_COMMON(dev);
}

static Property stm32g4_adc12_common_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_adc12_common = {
    .name = "stm32g4_adc12_common",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(csr, STM32G4ADC12CommonState),
        VMSTATE_UINT32(ccr, STM32G4ADC12CommonState),
        VMSTATE_UINT32(cdr, STM32G4ADC12CommonState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_adc12_common_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_adc12_common_realize;
    dc->reset     = stm32g4_adc12_common_reset;
    dc->unrealize = stm32g4_adc12_common_unrealize;
    dc->vmsd      = &vmstate_stm32g4_adc12_common;
    device_class_set_props(dc, stm32g4_adc12_common_properties);
}

static TypeInfo stm32g4_adc12_common_info = {
    .name          = TYPE_STM32G4_ADC12_COMMON,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4ADC12CommonState),
    .instance_init = stm32g4_adc12_common_instance_init,
    .class_init    = stm32g4_adc12_common_class_init
};

static void stm32g4_adc12_common_register_types(void)
{
    type_register_static(&stm32g4_adc12_common_info);
}

type_init(stm32g4_adc12_common_register_types)
