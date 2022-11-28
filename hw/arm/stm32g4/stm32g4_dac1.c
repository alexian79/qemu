/* stm32g4_dac1.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_dac1.h"
#include "migration/vmstate.h"

#define STM32G4_DAC1_MMIO TYPE_STM32G4_DAC1 "_mmio"
#define STM32G4_DAC1_MMIO_SIZE 0x64

static uint64_t stm32g4_dac1_mmio_read(void *opaque, hwaddr offset,
                                       unsigned size)
{
    STM32G4DAC1State *s = STM32G4_DAC1(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* DAC_CR, DAC control register */
        ret = s->dac_cr;
        break;

    case 0x04 ... 0x07:
        /* DAC_SWTRGR, DAC software trigger register */
        ret = s->dac_swtrgr;
        break;

    case 0x08 ... 0x0B:
        /* DAC_DHR12R1, DAC channel1 12-bit right-aligned data holding register
            */
        ret = s->dac_dhr12r1;
        break;

    case 0x0C ... 0x0F:
        /* DAC_DHR12L1, DAC channel1 12-bit left aligned data holding register
            */
        ret = s->dac_dhr12l1;
        break;

    case 0x10 ... 0x13:
        /* DAC_DHR8R1, DAC channel1 8-bit right aligned data holding register */
        ret = s->dac_dhr8r1;
        break;

    case 0x14 ... 0x17:
        /* DAC_DHR12R2, DAC channel2 12-bit right aligned data holding register
            */
        ret = s->dac_dhr12r2;
        break;

    case 0x18 ... 0x1B:
        /* DAC_DHR12L2, DAC channel2 12-bit left aligned data holding register
            */
        ret = s->dac_dhr12l2;
        break;

    case 0x1C ... 0x1F:
        /* DAC_DHR8R2, DAC channel2 8-bit right-aligned data holding register */
        ret = s->dac_dhr8r2;
        break;

    case 0x20 ... 0x23:
        /* DAC_DHR12RD, Dual DAC 12-bit right-aligned data holding register */
        ret = s->dac_dhr12rd;
        break;

    case 0x24 ... 0x27:
        /* DAC_DHR12LD, DUAL DAC 12-bit left aligned data holding register */
        ret = s->dac_dhr12ld;
        break;

    case 0x28 ... 0x2B:
        /* DAC_DHR8RD, DUAL DAC 8-bit right aligned data holding register */
        ret = s->dac_dhr8rd;
        break;

    case 0x2C ... 0x2F:
        /* DAC_DOR1, DAC channel1 data output register */
        ret = s->dac_dor1;
        break;

    case 0x30 ... 0x33:
        /* DAC_DOR2, DAC channel2 data output register */
        ret = s->dac_dor2;
        break;

    case 0x34 ... 0x37:
        /* DAC_SR, DAC status register */
        ret = s->dac_sr;
        break;

    case 0x38 ... 0x3B:
        /* DAC_CCR, DAC calibration control register */
        ret = s->dac_ccr;
        break;

    case 0x3C ... 0x3F:
        /* DAC_MCR, DAC mode control register */
        ret = s->dac_mcr;
        break;

    case 0x40 ... 0x43:
        /* DAC_SHSR1, DAC Sample and Hold sample time register 1 */
        ret = s->dac_shsr1;
        break;

    case 0x44 ... 0x47:
        /* DAC_SHSR2, DAC Sample and Hold sample time register 2 */
        ret = s->dac_shsr2;
        break;

    case 0x48 ... 0x4B:
        /* DAC_SHHR, DAC Sample and Hold hold time register */
        ret = s->dac_shhr;
        break;

    case 0x4C ... 0x4F:
        /* DAC_SHRR, DAC Sample and Hold refresh time register */
        ret = s->dac_shrr;
        break;

    case 0x58 ... 0x5B:
        /* DAC_STR1, Sawtooth register */
        ret = s->dac_str1;
        break;

    case 0x5C ... 0x5F:
        /* DAC_STR2, Sawtooth register */
        ret = s->dac_str2;
        break;

    case 0x60 ... 0x63:
        /* DAC_STMODR, Sawtooth Mode register */
        ret = s->dac_stmodr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_dac1_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                    unsigned size)
{
    STM32G4DAC1State *s = STM32G4_DAC1(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* DAC_CR, DAC control register */
        s->dac_cr = value;
        break;

    case 0x04 ... 0x07:
        /* DAC_SWTRGR, DAC software trigger register */
        s->dac_swtrgr = value;
        break;

    case 0x08 ... 0x0B:
        /* DAC_DHR12R1, DAC channel1 12-bit right-aligned data holding register
            */
        s->dac_dhr12r1 = value;
        break;

    case 0x0C ... 0x0F:
        /* DAC_DHR12L1, DAC channel1 12-bit left aligned data holding register
            */
        s->dac_dhr12l1 = value;
        break;

    case 0x10 ... 0x13:
        /* DAC_DHR8R1, DAC channel1 8-bit right aligned data holding register */
        s->dac_dhr8r1 = value;
        break;

    case 0x14 ... 0x17:
        /* DAC_DHR12R2, DAC channel2 12-bit right aligned data holding register
            */
        s->dac_dhr12r2 = value;
        break;

    case 0x18 ... 0x1B:
        /* DAC_DHR12L2, DAC channel2 12-bit left aligned data holding register
            */
        s->dac_dhr12l2 = value;
        break;

    case 0x1C ... 0x1F:
        /* DAC_DHR8R2, DAC channel2 8-bit right-aligned data holding register */
        s->dac_dhr8r2 = value;
        break;

    case 0x20 ... 0x23:
        /* DAC_DHR12RD, Dual DAC 12-bit right-aligned data holding register */
        s->dac_dhr12rd = value;
        break;

    case 0x24 ... 0x27:
        /* DAC_DHR12LD, DUAL DAC 12-bit left aligned data holding register */
        s->dac_dhr12ld = value;
        break;

    case 0x28 ... 0x2B:
        /* DAC_DHR8RD, DUAL DAC 8-bit right aligned data holding register */
        s->dac_dhr8rd = value;
        break;

    case 0x2C ... 0x2F:
        /* DAC_DOR1, DAC channel1 data output register */
        s->dac_dor1 = value;
        break;

    case 0x30 ... 0x33:
        /* DAC_DOR2, DAC channel2 data output register */
        s->dac_dor2 = value;
        break;

    case 0x34 ... 0x37:
        /* DAC_SR, DAC status register */
        s->dac_sr = value;
        break;

    case 0x38 ... 0x3B:
        /* DAC_CCR, DAC calibration control register */
        s->dac_ccr = value;
        break;

    case 0x3C ... 0x3F:
        /* DAC_MCR, DAC mode control register */
        s->dac_mcr = value;
        break;

    case 0x40 ... 0x43:
        /* DAC_SHSR1, DAC Sample and Hold sample time register 1 */
        s->dac_shsr1 = value;
        break;

    case 0x44 ... 0x47:
        /* DAC_SHSR2, DAC Sample and Hold sample time register 2 */
        s->dac_shsr2 = value;
        break;

    case 0x48 ... 0x4B:
        /* DAC_SHHR, DAC Sample and Hold hold time register */
        s->dac_shhr = value;
        break;

    case 0x4C ... 0x4F:
        /* DAC_SHRR, DAC Sample and Hold refresh time register */
        s->dac_shrr = value;
        break;

    case 0x58 ... 0x5B:
        /* DAC_STR1, Sawtooth register */
        s->dac_str1 = value;
        break;

    case 0x5C ... 0x5F:
        /* DAC_STR2, Sawtooth register */
        s->dac_str2 = value;
        break;

    case 0x60 ... 0x63:
        /* DAC_STMODR, Sawtooth Mode register */
        s->dac_stmodr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_dac1_mmio_ops = {
    .read = stm32g4_dac1_mmio_read,
    .write = stm32g4_dac1_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_dac1_instance_init(Object *obj)
{
    STM32G4DAC1State *s = STM32G4_DAC1(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_dac1_mmio_ops, s,
                          STM32G4_DAC1_MMIO, STM32G4_DAC1_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_dac1_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4DAC1State *s = STM32G4_DAC1(dev);
}

static void stm32g4_dac1_reset(DeviceState *dev)
{
    STM32G4DAC1State *s = STM32G4_DAC1(dev);

    s->dac_cr = 0x00000000;
    s->dac_swtrgr = 0x00000000;
    s->dac_dhr12r1 = 0x00000000;
    s->dac_dhr12l1 = 0x00000000;
    s->dac_dhr8r1 = 0x00000000;
    s->dac_dhr12r2 = 0x00000000;
    s->dac_dhr12l2 = 0x00000000;
    s->dac_dhr8r2 = 0x00000000;
    s->dac_dhr12rd = 0x00000000;
    s->dac_dhr12ld = 0x00000000;
    s->dac_dhr8rd = 0x00000000;
    s->dac_dor1 = 0x00000000;
    s->dac_dor2 = 0x00000000;
    s->dac_sr = 0x00000000;
    s->dac_ccr = 0x00000000;
    s->dac_mcr = 0x00000000;
    s->dac_shsr1 = 0x00000000;
    s->dac_shsr2 = 0x00000000;
    s->dac_shhr = 0x00010001;
    s->dac_shrr = 0x00010001;
    s->dac_str1 = 0x00000000;
    s->dac_str2 = 0x00000000;
    s->dac_stmodr = 0x00000000;
}

static void stm32g4_dac1_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4DAC1State *s = STM32G4_DAC1(dev);
}

static Property stm32g4_dac1_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_dac1 = {
    .name = "stm32g4_dac1",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(dac_cr, STM32G4DAC1State),
        VMSTATE_UINT32(dac_swtrgr, STM32G4DAC1State),
        VMSTATE_UINT32(dac_dhr12r1, STM32G4DAC1State),
        VMSTATE_UINT32(dac_dhr12l1, STM32G4DAC1State),
        VMSTATE_UINT32(dac_dhr8r1, STM32G4DAC1State),
        VMSTATE_UINT32(dac_dhr12r2, STM32G4DAC1State),
        VMSTATE_UINT32(dac_dhr12l2, STM32G4DAC1State),
        VMSTATE_UINT32(dac_dhr8r2, STM32G4DAC1State),
        VMSTATE_UINT32(dac_dhr12rd, STM32G4DAC1State),
        VMSTATE_UINT32(dac_dhr12ld, STM32G4DAC1State),
        VMSTATE_UINT32(dac_dhr8rd, STM32G4DAC1State),
        VMSTATE_UINT32(dac_dor1, STM32G4DAC1State),
        VMSTATE_UINT32(dac_dor2, STM32G4DAC1State),
        VMSTATE_UINT32(dac_sr, STM32G4DAC1State),
        VMSTATE_UINT32(dac_ccr, STM32G4DAC1State),
        VMSTATE_UINT32(dac_mcr, STM32G4DAC1State),
        VMSTATE_UINT32(dac_shsr1, STM32G4DAC1State),
        VMSTATE_UINT32(dac_shsr2, STM32G4DAC1State),
        VMSTATE_UINT32(dac_shhr, STM32G4DAC1State),
        VMSTATE_UINT32(dac_shrr, STM32G4DAC1State),
        VMSTATE_UINT32(dac_str1, STM32G4DAC1State),
        VMSTATE_UINT32(dac_str2, STM32G4DAC1State),
        VMSTATE_UINT32(dac_stmodr, STM32G4DAC1State),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_dac1_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_dac1_realize;
    dc->reset     = stm32g4_dac1_reset;
    dc->unrealize = stm32g4_dac1_unrealize;
    dc->vmsd      = &vmstate_stm32g4_dac1;
    device_class_set_props(dc, stm32g4_dac1_properties);
}

static TypeInfo stm32g4_dac1_info = {
    .name          = TYPE_STM32G4_DAC1,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4DAC1State),
    .instance_init = stm32g4_dac1_instance_init,
    .class_init    = stm32g4_dac1_class_init
};

static void stm32g4_dac1_register_types(void)
{
    type_register_static(&stm32g4_dac1_info);
}

type_init(stm32g4_dac1_register_types)
